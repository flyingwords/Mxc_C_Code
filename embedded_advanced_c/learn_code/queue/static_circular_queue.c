#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*
程序功能描述：采用静态循环队列来展示三种队列满和队列空的判断方法
*/

#define queue_max_length 5

#if 1    //牺牲一个队列元素用来识别队列满和队列空
typedef struct queue_srt
{
    int front;
    int rear;
    int queue_data[queue_max_length];
} queue_srt;


int queue_init(queue_srt *q_srt)
{
    q_srt->front = q_srt->rear = 0;
    memset(q_srt->queue_data, 0, sizeof(q_srt->queue_data));
    printf("queue init success\n");
    return 0;
}

int queue_read(queue_srt *q_srt, int *value)
{
    //判断队列是否为空
    if (q_srt->front == q_srt->rear)
    {    
        printf("the queue is empty\n");
        return 1;
    }
    *value = q_srt->queue_data[q_srt->front];
    q_srt->front = (q_srt->front + 1) % queue_max_length;
    return 0;
}

int queue_write(queue_srt *q_srt, int value)
{
    //牺牲一个队列元素用来判断队列满
    if (((q_srt->rear + 1)%queue_max_length) == q_srt->front)
    {    
        printf("the queue is full\n");
        return 1;
    }
    q_srt->queue_data[q_srt->rear] = value;
    q_srt->rear = (q_srt->rear + 1) % queue_max_length;
    return 0;
}

int queue_length(queue_srt *q_srt)
{
    //计算队列长度
    int length = (q_srt->rear - q_srt->front + queue_max_length) % queue_max_length;
    return length;
}
#endif 

#if 0    //通过计数器来判断队列满和队列空
typedef struct queue_srt
{
    int front;
    int rear;
    int queue_data[queue_max_length];
    int cnt;      //计数器，用来记录队列长度
} queue_srt;

int queue_init(queue_srt *q_srt)
{
    q_srt->front = q_srt->rear = 0;
    q_srt->cnt = 0;
    memset(q_srt->queue_data, 0, sizeof(q_srt->queue_data));
    printf("queue init success\n");
    return 0;
}

int queue_read(queue_srt *q_srt, int *value)
{
    //通过判断计数器来识别队列是否已经空
    if (q_srt->cnt == 0)
    {
        printf("the queue is empty\n");
        return 1;
    }
    *value = q_srt->queue_data[q_srt->front];
    q_srt->front = (q_srt->front + 1) % queue_max_length;
    q_srt->cnt--;//读完数据，计数器减1
    return 0;
}

int queue_write(queue_srt *q_srt, int value)
{
    //通过判断计数器来识别队列是否已经满
    if (q_srt->cnt == queue_max_length)
    {
        printf("the queue is full\n");
        return 1;
    }
    q_srt->queue_data[q_srt->rear] = value;
    q_srt->rear = (q_srt->rear + 1) % queue_max_length;
    q_srt->cnt++; //写完数据，计数器加1
    return 0;
}

int queue_length(queue_srt *q_srt)
{
    //通过计数器获取队列长度
    int length = q_srt->cnt;
    return length;
}
#endif

#if 0    //通过一个读写标志来判断队列满和队列空
typedef struct queue_srt
{
    int front;
    int rear;
    int queue_data[queue_max_length];
    char rw_flag; //读写标志  w:表示写完队列  r:表示读完队列
} queue_srt;

int queue_init(queue_srt *q_srt)
{
    q_srt->front = q_srt->rear = 0;
    q_srt->rw_flag = 'r'; //初始为 r ，表示队列为空
    memset(q_srt->queue_data, 0, sizeof(q_srt->queue_data));
    printf("queue init success\n");
    return 0;
}

int queue_read(queue_srt *q_srt, int *value)
{
    //通过读写标志判断队列是否为空
    if ((q_srt->front == q_srt->rear) && (q_srt->rw_flag == 'r'))
    {    
        printf("the queue is empty\n");
        return 1;
    }
    *value = q_srt->queue_data[q_srt->front];
    q_srt->front = (q_srt->front + 1) % queue_max_length;
    q_srt->rw_flag = 'r'; //读完队列，读写标志设置r
    return 0;
}

int queue_write(queue_srt *q_srt, int value)
{
    //通过读写标志判断队列是否为空
    if ((q_srt->front == q_srt->rear) && (q_srt->rw_flag == 'w'))
    {    
        printf("the queue is full\n");
        return 1;
    }
    q_srt->queue_data[q_srt->rear] = value;
    q_srt->rear = (q_srt->rear + 1) % queue_max_length;
    q_srt->rw_flag = 'w'; //写完队列，读写标志设置w
    return 0;
}

int queue_length(queue_srt *q_srt)
{
    int length = 0;       
    if ((q_srt->front == q_srt->rear) && (q_srt->rw_flag == 'w')) //通过读写标志判断是否队满
    {
        length = queue_max_length;
    }
    else 
    {
        length = (q_srt->rear - q_srt->front + queue_max_length) % queue_max_length;
    }
    return length;
}
#endif 

int main(void)
{
    int action = 0;
    int value = 0;
    queue_srt testqueue;
    queue_init(&testqueue);
    while (1)
    {
        printf("1:write 2:read 3:get length\n");
        printf("enter action:");
        scanf("%d", &action);
        switch(action)
        {
            case 1:
                printf("write queue to data:");
                scanf("%d", &value);
                queue_write(&testqueue, value);
                break;
            case 2:
                if (1 == queue_read(&testqueue, &value))
                    continue;
                printf("read data from queue: %d\n", value);
                break;
            case 3:
                value = queue_length(&testqueue);
                printf("the length of queue is: %d\n", value);
                break;
            default:
                printf("no such action\n");
        }
    }
    return 0;
}

