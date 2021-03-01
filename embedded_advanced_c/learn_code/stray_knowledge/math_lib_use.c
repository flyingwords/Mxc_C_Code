#include<stdio.h>
#include<math.h>

/*
程序功能描述：分析math lib的使用
*/

//要使用gcc math_use.c -lm,添加一个-lxxx使系统找到需要的库
int main(void)
{
	double a = 25;
	double b = sqrt(a);//开方
	printf("b = %lf\n",b);
	return 0;
}
