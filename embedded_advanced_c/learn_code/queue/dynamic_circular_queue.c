#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



/*
程序功能描述：实现一个动态循环队列，队列元素采用动态内存分配
*/

#define queue_max_length 5
typedef struct queue_srt
{
    int *front;        //指向队列头
    int *rear;        //指向队列尾
    int *queue_data;  //指向队列动态内存
    int *end;        //指向队列存储空间之后
} queue_srt;


int queue_init(queue_srt *q_srt)
{
    q_srt->queue_data = (int *) (malloc)(sizeof(int) * queue_max_length);
    if (NULL == q_srt)
    {
        printf("malloc mem failed,queue init failed\n");
        return 1;
    }
    q_srt->front = q_srt->rear = q_srt->queue_data; //指向队列首部
    q_srt->end = q_srt->queue_data + queue_max_length; //指向队列存储空间之后
    printf("queue init success\n");
    return 0;
}

int queue_read(queue_srt *q_srt, int *value)
{
    if (q_srt->front == q_srt->rear) //判断队列是否为空
    {    
        printf("the queue is empty\n");
        return 1;
    }
    *value = *(q_srt->front);
    if ((q_srt->front + 1) >= q_srt->end) //判断队头指针是否到队列尾
    {
        q_srt->front = q_srt->queue_data;
    }
    else
    {
        q_srt->front = q_srt->front + 1;
    }
    return 0;
}

int queue_write(queue_srt *q_srt, int value)
{
    //牺牲一个队列元素用来识别队列满
    int *q_tmp = (q_srt->rear + 1 >= q_srt->end)? (q_srt->queue_data) : (q_srt->rear + 1);
    if (q_tmp == q_srt->front)
    {    
        printf("the queue is full\n");
        return 1;
    }
    *(q_srt->rear) = value;
    q_srt->rear = q_tmp;
    return 0;
}

int queue_length(queue_srt *q_srt)
{
    int length = 0;
    length = (q_srt->rear - q_srt->front + queue_max_length) % queue_max_length;return length; //获取队列长度
}

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
    free(testqueue.queue_data);
    return 0;
}

