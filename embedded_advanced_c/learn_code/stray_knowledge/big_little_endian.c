/*
程序功能描述：使用gcc分析大小端
*/
#include<stdio.h>

union stu
{
	unsigned int a;
	unsigned char b;
};

int main()
{	

	/*
	采用共用体的方式测试linux gcc大小端
	测试结果：a = 0x13141516 b = 0x16，低字节存放在低地址，说明gcc是小端模式
	*/
	
#if 0
	union stu endian;
	endian.a = 0x13141516;

	//a和b的地址相同,证明共用体成员b和a低地址对齐
	printf("&endian.a = %p\n", &endian.a); 
	printf("&endian.b = %p\n", &endian.b);


	//打印结果
	printf("a = 0x%x\n",endian.a);
	printf("b = 0x%x\n",endian.b);
#endif



	/*
	采用指针的方式测试系统大小端
	测试结果：a = 0x13141516 *p = 0x16,低字节存放在低地址，说明gcc是小端模式
	*/
	
#if 1
	unsigned int a = 0x13141516;
	char *p = (char *)(&a); //指向a的低地址
	printf("a = 0x%x\n",a);
	printf("*p = 0x%x\n",*p);
#endif 	

	return 0;
}






