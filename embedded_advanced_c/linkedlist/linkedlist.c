#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int data;            //数据
	struct node *pNext;  //指向下一个节点的指针
} Tnode;
struct node * create_node(int data);
int insert_node_tail(struct node *pH,struct node *new);
int insert_node_head(struct node *pH,struct node *new);
int ergodic(struct node *pH);
int delete_node(struct node *pH, int data);
int reverse_linkdelist(struct node *pH);
int rank_linkdelist(struct node *pH);



/*
程序功能描述：实现一个带头节点的单向链表，并实现一些链表的基本操作
链表带有头节点，头节点保存 有效节点个数（不包括头节点）
*/
int main()
{ 	
	struct node *pHeadernode = create_linkdelist_with_headnode();    //头节点
	insert_node_head(pHeadernode,create_node(15));
	insert_node_head(pHeadernode,create_node(12));
	insert_node_head(pHeadernode,create_node(19));
	insert_node_tail(pHeadernode,create_node(38));
	insert_node_tail(pHeadernode,create_node(38));
	insert_node_tail(pHeadernode,create_node(38));

	delete_node(pHeadernode, 38);
	ergodic(pHeadernode);
	reverse_linkdelist(pHeadernode);
	ergodic(pHeadernode);
	rank_linkdelist(pHeadernode);
	ergodic(pHeadernode);
	return 0;
}
/*
函数功能描述：创建一个带头节点的链表
参数：
无
返回值：
创建成功返回链表头节点，创建失败返回NULL
*/
struct node *create_linkdelist_with_headnode(void)
{
	struct node *pHeadernode = (struct node *)malloc(sizeof(struct node)); 
	                            
	if(NULL == pHeadernode)
	{
		printf("create_linkdelist_with_headnode failed, malloc failed\n");
		return NULL;
	}
	pHeadernode->data = 0;     //头节点数据用来记录节点个数
	pHeadernode->pNext = NULL; 
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
	struct node *p1 = (struct node *)malloc(sizeof(struct node));                         
	if(NULL == p1)
	{
		printf("create_node failed, malloc failed\n");
		return NULL;
	}
	p1->data = data;
	p1->pNext = NULL; 
	return p1; 
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
	
	new->pNext = pH->pNext;  //指向原来的第一个的节点的地址
	
	pH->pNext = new;  //头节点指向新的第一个头节点
	pH->data += 1;

	return 0;
}


/*
函数功能描述：链表遍历函数
参数：
pH：头节点指针
返回值：
-1 失败   0成功
*/
int ergodic(struct node *pH)
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
函数功能描述：删除指定节点数据的链表节点
参数：
pH：头节点指针
data：指定节点数据
返回值：
-1 操作失败或者没有找到节点
0  删除成功
*/
int delete_node(struct node *pH, int data)
{
	struct node *ptem = NULL;
	struct node *prev = NULL;
	int current_cnt;

	ptem = pH->pNext;
	prev = pH;
	current_cnt = pH->data; //保留当前有效节点数量


#if 0 //只删除匹配到的第一个点
	while (NULL != ptem)
	{
		if(ptem->data == data)
		{
			prev->pNext = ptem->pNext;
			free(ptem);
			
			pH->data -= 1; //头节点的计数减一
			return 0;
		}
		else
		{
			prev = ptem;
			ptem = ptem->pNext;
		}
	}
	printf("not find the node which data is %d\n", data);
	return 0;
#endif 


#if 1 //删除所有匹配的点
	while(NULL != ptem)
	{
		if(ptem->data == data)
		{
			prev->pNext = ptem->pNext;
			free(ptem);

			pH->data -= 1;		 //头节点的计数减一
			ptem = prev->pNext; //prev维持不变，ptem指向prev节点指向的下一个点
		}
		else
		{
			prev = ptem;
			ptem = ptem->pNext;
		}

	}

	
	if (current_cnt == pH->data) //比较看有没有删除节点
	{
		printf("not find the node which data is %d\n", data);
		return -1;
	}
	
	return 0;
#endif 
}

/*
函数功能描述：将链表逆序
参数：
pH：头节点指针
返回值：
-1 操作失败
0 成功
*/
int reverse_linkdelist(struct node *pH)
{

	struct node *ptem = NULL;
	struct node *pnex = NULL;
	struct node *prev = NULL;
	ptem = pH->pNext;

	while(NULL != ptem)
	{
		pnex = ptem->pNext;
		ptem->pNext = prev;
		prev = ptem;
		ptem = pnex;
	}
	pH->pNext = prev; //头节点指向原链表最后一个节点
	return 0;
	
}

/*
函数功能描述：通过比较节点数据大小，将链表节点从小到大进行排序
参数：
pH：头节点指针
返回值：
-1 操作失败
0 成功
*/
int rank_linkdelist(struct node *pH)
{
	int temp = 0;
	struct node *p, *q;
	
	p = q = pH->pNext;
	
	while (p != NULL)
	{
		while (q != NULL)
		{
			if(p->data <= q->data)
			{
				temp = q->data;
				q->data = p->data;
				p->data = temp;
			}
			q = q->pNext;
		}
		q = pH->pNext;
		p = p->pNext;
	}
	return 0;
}










