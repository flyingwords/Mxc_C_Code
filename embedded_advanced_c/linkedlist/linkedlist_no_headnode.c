#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int data;            //数据
	struct node *pNext;  //指向下一个结点的指针
} Tnode;
struct node * create_node(int data);
struct node * insert_node_head(struct node *pH,struct node *new);
struct node * insert_node_tail(struct node *pH,struct node *new);
struct node * insert_node_tail_NeedOneNode(struct node *pH,struct node *new);
struct node* delete_node(struct node *pH,int data);
struct node* reverse_linkdelist(struct node *pH);
void ergodic(struct node *pH);



/*
程序功能描述：实现一个不带头结点（只有头指针）的链表，并实现链表的一些基本操作
*/
int main()
{
	int i;
	struct node *Header = create_linkdelist_without_headnode();
	Header = insert_node_tail(Header,create_node(50)); //空链表尾插结点需要返回首个结点地址
	insert_node_tail(Header,create_node(50));
	insert_node_tail(Header,create_node(50));
	insert_node_tail(Header,create_node(50));
	Header = insert_node_head(Header,create_node(40));
	Header = insert_node_head(Header,create_node(30));
	Header = insert_node_head(Header,create_node(20));
	Header = insert_node_head(Header,create_node(10));
	
	ergodic(Header);
	Header = delete_node(Header, 50);
	ergodic(Header);
	Header = reverse_linkdelist(Header);
	ergodic(Header);
	return 0;
}


/*
函数功能描述：创建一个不带头结点的链表
参数：
无
返回值：
返回NULL
*/
struct node *create_linkdelist_without_headnode(void)
{
	return NULL;
}


/*
函数功能描述：创建一个结点
参数：
data：设置结点数据
返回值：
创建成功返回结点，失败返回NULL
*/
struct node * create_node(int data)
{
	struct node *p1 = (struct node *)malloc(sizeof(struct node)); 
	memset(p1,0,sizeof(struct node));                             
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
函数功能描述：在链表头部插入结点
参数：
pH：头指针，指向首个有效结点,链表可以为空
new：要插入的结点
返回值：
失败返回NULL。
成功返回首个结点指针。
*/
struct node * insert_node_head(struct node *pH,struct node *new)
{
	if (NULL == new)
	{
		printf("insert_node_head failed, new is NULL\n");
		return NULL;
	}
	
	new->pNext = pH;
	pH = new;

	return pH;
}

/*
函数功能描述：在链表尾部插入结点
参数：
pH：头指针，指向首个有效结点，链表可以为空
new：要插入的结点
返回值：
失败返回NULL
如果pH是空链表，则需要获取返回值并赋值给链表头指针否则链表为空。
如果pH不是空链表，则返回值跟形参pH的实参一样。
*/
 struct node * insert_node_tail(struct node *pH,struct node *new)
{
	struct node *prev = NULL; //prev用来保存前一个结点
	struct node *ptem = pH;
	if (NULL == new)
	{
		printf("insert_node_tail failed, new is NULL\n");
		return NULL;
	}
	
	while (NULL != ptem) //遍历到最后一个结点
	{
		prev = ptem;
		ptem = ptem->pNext;
	}
	
	if(NULL == prev) //判断链表是不是一个结点也没有
	{
		pH = new;
		new->pNext = NULL;
		//空链表情况下，形参pH接收的实参是NULL，因此这里需要把pH返回作为头指针，否则链表就是空的
		return pH;
	}
	else
	{
		prev->pNext = new;
		new->pNext = NULL;
		return pH; //链表不为空，返回值等同于形参pH
	}
}
 

/*
函数功能描述：删除指定结点数据的链表结点
参数：
pH：头指针，指向首个有效结点，链表可以为空
data：指定结点数据
返回值：
没有找到指定数据节点 返回NULL。

如果删除了首个节点，则需要获取返回值并赋值给链表头指针。
如果没有删除首个节点，则返回值与形参pH的值一致。
*/
struct node* delete_node(struct node *pH,int data)
{
	struct node *prev = NULL;
	struct node *ptem = pH;
	int origin_cnt, current_cnt;
	origin_cnt = current_cnt = 0;
	
	while(NULL != ptem)
	{
		origin_cnt++;		//统计链表未删除前 的结点数目
		ptem = ptem->pNext;
	}
	
	ptem = pH;
	current_cnt = origin_cnt;
	
	while(ptem != NULL)
	{
		if(ptem->data == data)
		{
			if(ptem == pH)  //第一个结点就带有指定数据
			{
				pH = ptem->pNext; //下个结点作为第一个结点
				free(ptem);
				ptem = pH;
			}
			else
			{
				prev->pNext = ptem->pNext;
				free(ptem);
				ptem = prev->pNext;
			}
			current_cnt--;
		}
		else
		{
			prev = ptem;
			ptem = ptem->pNext;

		}
	}

	if (current_cnt == origin_cnt) //判断有没有删除节点
	{
		printf("not find the node which data is %d\n", data);
		return NULL;
	}
		
	return pH;
}


/*
函数功能描述：删除指定结点数据的链表结点
参数：
pH：头指针，指向首个有效结点，链表可以为空
返回值：
无
*/
void ergodic(struct node *pH)
{
	struct node *ptem = pH;
	while(ptem!=NULL)
	{
		printf("->%d",ptem->data);
		ptem = ptem->pNext;
	}
	printf("\n");
}

/*
函数功能描述：链表逆序函数
参数：
pH：头指针，指向首个有效结点，链表可以为空
返回值：
返回逆序后的头指针
*/
struct node* reverse_linkdelist(struct node *pH)
{
	struct node *prev = NULL;
	struct node *pnex = NULL;
	struct node *ptem = pH;
	while(ptem != NULL)
	{
		pnex = ptem->pNext;
		ptem->pNext = prev;
		prev = ptem;
		ptem = pnex;
	}
	return prev;
}
