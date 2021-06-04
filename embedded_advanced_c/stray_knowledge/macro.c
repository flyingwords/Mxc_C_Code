#include <stdio.h>


/*
程序功能描述：宏定义和内联函数的区别
*/
#if 0

#define p(a,b) (((a)>(b)) ? (a):(b))//宏定义
//inline int fun(int a,int b); //内联函数声明，不用加inline
int fun(int a,int b); 

int main()
{

	int a = 40, b = 20;
	int c = 0;
	/*这里编译时不会出现报错，这是宏定义的缺陷，即不会有类型检查
	宏定义不会占用内存开销，节约资源*/
	p(&a,&b); 


	/*内联函数，类似于有静态类型检查的宏定义，在编译时会
	直接替换为函数定义，而普通函数只是调用而不会替换
	内联函数节省了内存开销*/
	//c = fun(&a,&b);
	c = fun(a,b);
	return 0;
}

inline int fun(int a,int b)//内联函数定义，需要加inline
{
	return (((a)>(b)) ? (a):(b));
}
#endif


/*
程序功能描述：分析C语言的宏定义中的#符号
#  ：用来宏定义中的参数变为字符串 
*/

#define TOSTRING(str) #str

#define LINKDEBUGPARAM(A,B,C) A##B##C
int main(void)
{
	printf("%s\n", TOSTRING(45+96+88));
	
	printf("%s\n", TOSTRING(""""""""));	
	
	return 0;
}

