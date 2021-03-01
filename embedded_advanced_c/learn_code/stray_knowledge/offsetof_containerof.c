#include<stdio.h>

/*
宏定义名称：offsetof宏
功能描述：求取结构体成员到结构体首地址的长度（单位：byte）
参数：
type：结构体类型
member：结构体成员名
返回值：
结构体成员到结构体首地址的长度（单位：byte）
*/
#define offsetof(type,member) ((int)(&((type *)0)->member))


/*
宏定义名称：containerof
功能描述：基于结构体成员地址，计算出结构体的首地址
参数：
ptr：结构体成员的地址
type：结构体类型
member：结构体成员名
返回值：
结构体的首地址
*/
//写法1：
#define containerof(ptr,type,member) (\
{const typeof(((type *)0)->member)*nptr = ptr;\
 (type*)(((int)nptr)-offsetof(type,member));})
 
//写法2：
#if 0
#define containerof(ptr,type,member) ((type*)(((int)ptr)-offsetof(type,member)))  
#endif

//说明：offsetof宏和containerof宏在链表中用的比较多



struct STRU{
	char a;
	int b;
	short c;
};

/*
程序功能描述：测试offsetof和containerof宏
*/

int main()
{
	struct STRU key = {'h',13,14};
	struct STRU *p = &key;
	struct STRU *ps = NULL;
	//使用指针偏移的方式访问成员变量
	//printf("a = %c\n",*(char *)((int)p + 0));
	printf("a = %c\n",*(char *)((char *)p + 0));
	printf("b = %d\n",*(int *)((char *)p + 4));
	printf("c = %hd\n",*(short *)((char *)p + 8));
	
	//使用指针和offsetof宏结合的方式访问成员变量
	//printf("a = %c\n",*(char *)((int)p + offsetof(struct STRU,a)));
	printf("a = %c\n",*(char *)((char *)p + offsetof(struct STRU,a)));
	printf("b = %d\n",*(int *)((char *)p + offsetof(struct STRU,b)));
	printf("c = %hd\n",*(short *)((char *)p + offsetof(struct STRU,c)));

	//直接打印结构体首地址
	printf("p = %p\n",p);

	//使用containerof宏求取首地址
	ps = containerof(&(key.a),struct STRU,a);
	printf("use containerof: %p\n",ps);
	return 0;
}
