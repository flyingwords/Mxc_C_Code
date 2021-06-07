#include <stdio.h>


/*
程序功能描述：分析作用使用了const的指针
*/
int main()
{

//分析作用在一重指针上的const
#if 1
	int a = 15;
	int b = 16;
	int *const p = &a;	 //const作用在p上面，所以p不能指向别的地址
	*p = 14;
	p = &b;
	printf("%d\n",*p);
	
	int a = 5;
	int b = 7;
	int const  *p = &a;  //const作用在int变量a上面，所以不能通过指针p更改变量a的值
	*p = 155;
	p = &b;
	printf("%d\n",*p);
#endif 


//分析作用在二重指针上的const
#if 0
	char *ptarray[10] = {"\0"};
	char *ptarray2[10] = {"\0"};
	char ** const mpt = ptarray;	//const作用在二重指针mpt上面，所以不能mpt不能指向别的指针数组
	char *const *mpt = ptarray;     //const作用在指针数组中的char*元素上，所以不能通过指针改变数组元素指针的值
	mpt[0] = "hello world";
	mpt = ptarray2;
#endif
	return 0;
}
	