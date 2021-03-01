#include <stdio.h>
#include <string.h>
/*
程序功能描述：使用给main函数传参的方式编写一个计算器
*/

//argc 指的是参数个数，包括程序名
//argv 是一个二重指针，指向参数名字符串数组，其中argv[0] 指的是执行程序名
int main(int argc, char *argv[])
{
	int i, num_one, num_two, temp;
	i = num_one = num_two = temp = 0;
	
	//判断是否有四个参数
	if(!(argc == 4))
	{
		printf("we need 4 param\n");
		return -1;
	}
	//指针指向的参数是字符串，判断字符串是不是数字
	while(argv[1][i]!='\0')
	{
		if(argv[1][i]>='0'&&argv[1][i]<='9')
			i++;
		else
		{
			printf("the argv[1] is not a number\n");
			return -1;
		}
	}
	i = 0;
	while(argv[3][i]!='\0')
	{
		if(argv[3][i]>='0'&&argv[3][i]<='9')
			i++;
		else
		{
			printf("the argv[1] is not a number\n");
			return -1;
		}
	}
	i = 0;
	//判断第三个参数是不是算术运算符
	if(!(strlen(argv[2])==1&&(argv[2][0]=='+'||argv[2][0]=='-'||argv[2][0]=='*'||argv[2][0]=='/')))
	{
		printf("the argv[2] is not a operator\n");
		return -1;
	}
	//将数字字符串转换为数字
	while(argv[1][i]!='\0')
	{
		temp = argv[1][i] - '0';
		num_one = num_one *10 + temp;
		i++;
	}
	i = 0;
	while(argv[3][i]!='\0')
	{
		temp = argv[3][i] - '0';
		num_two = num_two *10 + temp;
		i++;
	}
	i = 0;
	//进行算术运算
	switch(argv[2][0])
	{
		case '+': printf("%d + %d = %d\n", num_one, num_two, num_one+num_two); break;
		case '-': printf("%d - %d = %d\n", num_one, num_two, num_one-num_two); break;
		case '*': printf("%d * %d = %d\n", num_one, num_two, num_one*num_two); break;	
		case '/': printf("%lf / %lf = %lf\n", (double)num_one, (double)num_two, (double)num_one/(double)num_two); break;
	}
	return 0;
}
