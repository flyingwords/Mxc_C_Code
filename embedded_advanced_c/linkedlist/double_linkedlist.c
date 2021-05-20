#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int data;
	struct node *pNext; //双向链表节点内部包含两个指针
	struct node *pPrev;
};
struct node *create_node(int data);
int insert_node_tail(struct node *pH,struct node *new);
int insert_node_head(struct node *pH,struct node *new);
int egodic(struct node *pH);
int forward_egodic(struct node *pH);
int delete_node(struct node *,int data);


/*
程序功能描述：实现一个带有头节点的双向链表，并实现链表的一些基本操作
*/
int main(void)
{
	struct node *pHeadernode = create_double_linkdelist_with_headnode();
	insert_node_head(pHeadernode,create_node(11));
	insert_node_head(pHeadernode,create_node(12));
	insert_node_head(pHeadernode,create_node(13));
	insert_node_tail(pHeadernode,create_node(15));
	insert_node_tail(pHeadernode,create_node(15));
	insert_node_tail(pHeadernode,create_node(15));
	egodic(pHeadernode);
	forward_egodic(pHeadernode);
	delete_node(pHeadernode,15);
	egodic(pHeadernode);
	
	return 0;
}

/*
函数功能描述：创建一个带有头节点的双向链表
参数：
无
返回值：
创建成功返回链表头节点，创建失败返回NULL
*/
struct node * create_double_linkdelist_with_headnode(void)
{
	struct node *pHeadernode = (struct node *)malloc(sizeof(struct node));
	if(NULL == pHeadernode)
	{
		printf("create_double_linkdelist_with_headnode failed, malloc failed\n");
		return NULL;
	}
	pHeadernode->pNext = NULL;
	pHeadernode->pPrev = NULL;
	pHeadernode->data = 0;
	
	return pHeadernode;
}


/*
函数功能描述：创建一个节点
参数：
data：设置节点数据
返回值：
创建成功返回节点，失败返回NULL
*/
struct node * create_node(int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("create_node failed, malloc failed\n");
		return NULL;
	}
	p->pNext = NULL;
	p->pPrev = NULL;
	p->data = data;
	
	return p;
}

/*
函数功能描述：在链表尾部插入一个节点
参数：
pH：头节点指针
new：插入的节点
返回值：
-1 失败 0成功
*/
int insert_node_tail(struct node *pH,struct node *new)
{
	int cnt = 0;
	struct node *ptem = pH;
	
	while(NULL != ptem->pNext)  
	{
		ptem = ptem->pNext;
		cnt++;
	}
	ptem->pNext = new;        	
	new->pPrev = ptem;
	pH->data = cnt + 1;

	return 0;
}



/*
函数功能描述：在链表头部插入节点的函数
参数：
pH：头节点指针
new：插入的节点
返回值：
-1 失败 0成功
*/
int insert_node_head(struct node *pH,struct node *new)
{

	new->pNext = pH->pNext; //新节点连接到原先的第一个节点
	
	if(NULL != pH->pNext)   //原先的第一个节点指向新节点，判断链表是否存在第一个节点
		pH->pNext->pPrev = new;
	
	pH->pNext = new; //头节点连接到新节点
	
	new->pPrev = pH; //新节点指向头节点
	
	pH->data += 1;   //头节点中计数变量加一
	return 0;
}

/*
函数功能描述：链表遍历函数
参数：
pH：头节点指针
返回值：
-1 失败   0成功
*/
int egodic(struct node *pH)
{
	
	struct node *ptem = pH;
	
	while(NULL != ptem)
	{
		printf("->%d",ptem->data);
		ptem = ptem->pNext;
	}
	printf("\n");
	return 0;
}

/*
函数功能描述：向前遍历的 链表遍历函数
参数：
pH：头节点指针
返回值：
-1 失败   0成功
*/
int forward_egodic(struct node *pH)
{
	struct node *ptem = pH;
	
	//先移动到最后一个节点
	while(NULL != ptem->pNext)
	{
		ptem = ptem->pNext;
	}
	
	//从最后一个节点往前面遍历
	while(NULL != ptem)
	{
		printf("->%d",ptem->data);
		ptem = ptem->pPrev;
	}
	printf("\n");
	return 0;
}

/*
函数功能描述：删除指定节点数据的链表节点
参数：
pH：头节点指针
data：指定节点数据
返回值：
-1 操作失败或者没有找到节点
0  删除成功
*/
int delete_node(struct node *pH,int data)
{

	struct node *ptem = NULL;
	struct node *prev = NULL;
	int current_cnt;

	ptem = pH->pNext;
	current_cnt = pH->data; //保留当前有效节点数量
	
	while(NULL != ptem)
	{
		if(ptem->data == data)
		{
			if(ptem->pNext == NULL)//判断是不是尾巴节点
			{
			#if 1
				ptem->pPrev->pNext = NULL; //前一个节点指向空
			#else
				ptem->pPrev->pNext = ptem->pNext; // ptem->pPrev->pNext = NULL
				ptem->pNext->pPrev = ptem->pPrev; //NULL->pPrev = ptem->pPrev  这里会段错误
				printf("---\n");
			#endif 
				
				free(ptem);
				pH->data--;
				break; //尾巴节点，因此结束判断
			}
			else
			{	
				ptem->pPrev->pNext = ptem->pNext; //前一个节点指向后一个节点
				
				ptem->pNext->pPrev = ptem->pPrev; //后一个节点指向前一个节点

				free(ptem);
				ptem = ptem->pPrev->pNext; //指向下一个节点继续判断
				pH->data--;
			}
		}
		else
		{
			ptem = ptem->pNext;
		}
	}

	if (current_cnt == pH->data) //比较看有没有删除节点
	{
		printf("not find the node which data is %d\n", data);
		return -1;
	}
	return 0;
}
