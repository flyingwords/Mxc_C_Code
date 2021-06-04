#include<stdio.h>


/*
程序功能描述:最简单的阶乘和递归函数
*/
#if 1
int factorial(int a);
void recursive(int b);

int main()
{
	
	int a = 5;
	a = factorial(a);
	printf("a! = %d\n",a);
	printf("--------------------\n");
	recursive(10);
	
	
	return 0;
}
//编写阶乘函数
int factorial(int a)
{
	printf("进入时：a = %d\n",a);
	if(a == 1)
	{
		return 1;
	}
	if(a < 1)
	{
		printf("error!\n");
		return -1;
	}
	return a*factorial(a-1);
}


//编写递归观察函数
void recursive(int b)
{
	printf("递归进入时b = %d\n",b);
	if(b > 1)
	{
		observe(b-1);
	}
	printf("递归出来时b = %d\n",b);
}
#endif 
