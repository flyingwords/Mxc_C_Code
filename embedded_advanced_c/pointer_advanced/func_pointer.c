
#include <stdio.h>

/*
程序功能描述：分析基础函数指针
*/
#if 0
typedef int (*pFunc)(int, int); //使用typedef定义一个 int(*) (int, int) 的函数指针类型，*表示这是一个指针

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int multiply(int a, int b)
{
	return a * b;
}

int divide(int a, int b)
{
	return a / b;
}


int main(void)
{
	pFunc p1 = NULL;
	char c = 0;
	int a = 0, b = 0, result = 0;
	
	printf("请输入要操作的2个整数:\n");
	scanf("%d %d", &a, &b);
	
	printf("请输入操作类型：+ | - | * | /\n");
	
	do 
	{
		scanf("%c", &c);
	}while (c == '\n');
	//printf("a = %d, b = %d, c = %d.\n", a, b, c);
	
	switch (c)
	{
	case '+':
		 /*既可以把函数当做一个变量，也可以把函数当做一个指针，如果把函数当做一个变量的话，
		 则使用&add给函数指针p1赋值，如果把函数当做指针的话则使用add给p1赋值*/
		//p1 = &add; break; 
		p1 = add; break;
	case '-':
		p1 = sub; break;
	case '*':
		p1 = multiply; break;
	case '/':
		p1 = divide; break;
	default:
		p1 = NULL;	break;
	}

	/*
	如果把函数当做一个变量的话，则使用(*p1)(a,b)取出函数并调用，如果直接把函数当做指针的
	话则直接使用p1(a,b)调用函数，两种调用方式都是正确的
	*/
	//result = (*p1)(a, b); 
	result = p1(a, b); 
	printf("%d %c %d = %d.\n", a, c, b, result);
	
	return 0;
}


#endif 


/*
程序功能描述：分析函数指针数组，函数指针数组指针，二重函数指针
*/

#if 1
/*
分析形参1，从结合性上分析，首先(*p)表示这是一个指针，接着(*p)[4]表示这是一个数组指针，数组包含四个元素，
最后int(*)(int,int)表示数组中元素是函数指针，因此指针p是一个指向包含四个int(*)(int,int)类型元素的函数指针数组
的数组指针
*/
int Array_pointer_func(int (*(*p)[4])(int,int),int n,int a,int b)
{
	int tem = 0;
	//tem = (p[0][n])(a,b); //效果等同于(*(*(p+0) + n))(a,b),即取出指针p所指向的数组，并取出数组中的第n个函数指针元素，并调用
	tem = (*(*(p+0) + n))(a,b);
	return tem;
}

/*
分析形参1，从结合性上分析，首先，*p表示这是一个指针，其次int(*)(int,int)表示指针p指向类型
为int(*)(int,int)类型的函数指针，因此指针p是一个二重指针
*/
int Double_pointer_func(int (**p)(int,int),int n,int a,int b)	
{
	int tem = 0;
	tem = (p[n])(a,b); //p[n]等同于(*(p+n))(a,b)，即取出指针p所指向的函数指针，并传参调用
	//tem = (*(p+n))(a,b);
	return tem;
}
	
int fun_add(int a,int b)
{
	return a+b;
}
int fun_dec(int a,int b)
{
	return a-b;
}
int fun_mul(int a,int b)
{
	return a*b;
}
int fun_div(int a,int b)
{
	return a/b;
}

int main()
{
	int a = 40;
	int b = 20;
	int c = 0;

	/*从结合性上分析，p[4]表示这是一个包含4个元素的数组，而int(*)(int,int)表示数组的元素是int(*)(int,int)类型的函数指针，
	因此这是一个包含四个int(*)(int,int)类型的函数指针元素的函数指针数组
	*/
	int (*p[4])(int,int) = {fun_add,fun_dec,fun_mul,fun_div};


	c = p[2](a,b);//等同于(*(p+2))(a,b)，即取出数组的第三个函数指针元素并进行调用
	printf("%d\n",c);
	
	c = Array_pointer_func(&p,3,a,b); //从上面的分析已知形参1是一个数组指针，因此需要取数组p的地址&p赋值给形参1
	printf("%d\n",c);
	//从上面的分析已知形参1是一个二重指针，因为p是int(*)(int,int)类型数组元素p[0]的地址，因此可以将p直接赋值给形参1
	c = Double_pointer_func(p,1,a,b); 
	printf("%d\n",c);
	return 0;
}
#endif 


/*
程序功能描述：程序等同于上面例子，只是使用了typedef来定义函数指针，使程序看起来更加简洁
*/
#if 0
typedef int(*pFun)(int,int);

int Array_pointer_func(pFun(*p)[4],int n,int a,int b)
{
	int tem = 0;
	tem = (p[0][n])(a,b);
	return tem;
}
	
int Double_pointer_func(pFun(*p),int n,int a,int b)	
{
	int tem = 0;
	tem = (p[n])(a,b);
	return tem;
}

int fun_add(int a,int b)
{
	return a+b;
}
int fun_dec(int a,int b)
{
	return a-b;
}
int fun_mul(int a,int b)
{
	return a*b;
}
int fun_div(int a,int b)
{
	return a/b;
}

int main()
{
	int a = 40;
	int b = 20;
	int c = 0;
	
	pFun p[4]= {fun_add,fun_dec,fun_mul,fun_div};
	c = p[2](40,20);
	printf("%d\n",c);

	c = Array_pointer_func(&p,3,a,b);
	printf("%d\n",c);
	
	c = Double_pointer_func(p,1,a,b);
	printf("%d\n",c);
	
	
	return 0;
}
#endif 

