#include<stdio.h>
typedef int* PINK;
typedef const int* CPINK;
typedef  int*const CPINK2;



/*
程序功能描述：分析const和typedef在指针上的搭配使用
*/
int main()
{
	
	int a = 5;
	int b = 4;

	/*
	测试：判断const是作用在p上还是作用在a上
	结果：发现const作用在p上而不是在a上，与预期相反，这点要注意
	*/
#if 0
	//const PINK p = &a; //相当于PINK const p = &a;
	PINK const p = &a;
	*p = 50;           
	p = &b;
#endif

	/*
	测试：判断const是作用在p上还是作用在a上
	结果：发现const作用在a上，符合预期
	*/
#if 0
	CPINK p = &a;
	*p = 60;
	p = &b;
#endif 

	/*
	测试：判断const是作用在p上还是作用在a上
	结果：发现const作用在p上，符合预期
	*/
#if 1
		CPINK2 p = &a;
		*p = 60;
		p = &b;
#endif


	return 0;
	
}
