#include <stdio.h>
#include <stdlib.h>

/*
程序功能描述：编写一个带头结点的链式队列
*/

typedef struct LKNODE
{
    int data;                //保存节点数据
    struct LKNODE *next;    //指向下一个节点
} LKNODE;

typedef struct LINKQUEUE    //队列结构体，采用头尾指针构建链式队列
{
    
    LKNODE *front; //头指针，指向队列头结点
    LKNODE *rear;  //尾指针，指向队列尾节点
}LINKQUEUE;

//初始化链式队列
int InitLinkQueue(LINKQUEUE *lkqueue)
{
    
    LKNODE *head = (LKNODE*) malloc(sizeof(LKNODE)); //创建头结点
    if (NULL == head)
    {
        printf("creat head node failed,init linkqueue failed\n");
        return 1;
    }
    head->next = NULL; //这里要head节点的next设置为NULL，避免头尾指针的next指向未知
    //头尾指针指向头结点
    lkqueue->front = lkqueue->rear = head;
    return 0;
}

//节点入队
int WriteLinkQueue(LINKQUEUE *lkqueue, int value)
{
    //创建新节点
    LKNODE *newnode = (LKNODE *)malloc(sizeof(LKNODE));
    if (NULL == newnode)
    {
        printf("creat newnode failed,write queue failed\n");
        return 1;
    }
    newnode->data = value;
    newnode->next = NULL; //这里要指向空，避免队列为空后，头结点的next指针指向未知
    
    //尾指针连接新节点
    lkqueue->rear->next = newnode;
    
    //尾指针指向新节点
    lkqueue->rear = newnode;
    return 0;
}

//节点出队
int ReadLinkQueue(LINKQUEUE *lkqueue, int *value)
{
    //LKNODE *temp = NULL;
    LKNODE *readnode = NULL;
    //判断队列是否为空队列
    if (lkqueue->front == lkqueue->rear)
    {
        printf("link queue is empty\n");
        return 1;
    }
    //获取读取节点值
    readnode = lkqueue->front->next;
    *value = readnode->data;

    //头结点连接读取节点的下一个节点
    lkqueue->front->next = readnode->next;  //如果readnode是最后一个节点，则头结点的next会指向NULL
    
    //判断读取的节点是不是最后一个节点，防止释放读取节点后尾指针指向未知
    if (readnode == lkqueue->rear)
    {
        lkqueue->rear = lkqueue->front; //队列为空，尾指针指向头结点
        
    }
    //释放读取节点
    free(readnode);
    return 0;
}

//获取队列长度
int GetLinkQueueLen(LINKQUEUE *lkqueue)
{
    int length = NULL;
    LKNODE *temp = NULL; //创建临时节点，因为头尾指针的位置不能动
    temp = lkqueue->front->next; //获取头结点的下一个节点
    if (NULL == temp) //判断队列是否为空
    {
        length = 0;
    }
    else
    {
        while(temp != lkqueue->rear) //判断是不是读到尾节点
        {
            length++;
            temp = temp->next;
        }
        length++; //加上最后一个节点
    }
    return length;
}

//清空队列
void ClearLinkQueue(LINKQUEUE *lkqueue)
{
    int value;
    int ret;
    while(1)
    {
        //读取队列元素，释放动态内存，防止内存泄漏
        ret = ReadLinkQueue(lkqueue, &value);
        if (1 == ret) //判断队列是否读完
        {
            printf("clear the link queue success\n");
            break;
        }
    }
}

//销毁队列
void DestroyLinkQueue(LINKQUEUE *lkqueue)
{
    //先清空队列，释放队列的动态内存
    ClearLinkQueue(lkqueue);
    
    //释放头结点的动态内存
    free(lkqueue->front);
    
    //头尾指针指向空
    lkqueue->front = lkqueue->rear = NULL;
    
    printf("destroy the link queue success\n");
}

//遍历队列
void TraverseLinkQueue(LINKQUEUE *lkqueue)
{
    int value;
    int ret = 0;
    int num = 0;
    LKNODE *temp = lkqueue->front->next;
    while(1)
    {
        if (NULL != temp)  //判断队列是否为空
        {
            num++;
            printf("%d node data is:%d\n", num, temp->data);
            temp = temp->next;
        }
        else
        {
            printf("traverse link queue success\n");
            break;
        }
    }
    
}

int main()
{
    int action = 0;
    int value = 0;
    int ret = 0;
    LINKQUEUE testlkqueue;
    InitLinkQueue(&testlkqueue); //初始化链式队列
    
    while(1)
    {
        printf("**********\n1 write    2 read 3 getlength 4 Traverse 5 Clear link queue 6 destroy link queue\n**********\n");
        printf("enter action:");
        scanf("%d", &action);
        switch(action)
        {
            case 1:
                printf("enter the value:");
                scanf("%d", &value);
                WriteLinkQueue(&testlkqueue, value);
                break;
            case 2:
                ret = ReadLinkQueue(&testlkqueue, &value);
                if (1 != ret)
                {
                    printf("the readnode data is:%d\n", value);
                }
                break;
            case 3:
                ret = GetLinkQueueLen(&testlkqueue);
                printf("the length of link queue is:%d\n", ret);
                break;
            case 4:
                TraverseLinkQueue(&testlkqueue);
                break;
            case 5:
                ClearLinkQueue(&testlkqueue);
                break;
            case 6:
                DestroyLinkQueue(&testlkqueue);
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}

