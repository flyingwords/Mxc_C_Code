#include<stdio.h>

/*
程序功能描述：分析 gcc对齐编译参数 __attribute__((aligned(n)))对结构体对齐的影响
 __attribute((aligned (n)))：让所作用的结构体对齐在n字节自然边界上。
 如果结构体中有成员的长度大于n，则按照最大成员的长度来对齐。n必须是2的整数倍。
 
 __attribute__ ((packed))：取消结构体在编译过程中的优化对齐，按照实际占用字节数进行对齐。
*/

struct STRU1{   
	char a;		
	int b;		
	short c;   
}__attribute__((packed));
/*
添加了__attribute__((packed))，取消结构体在编译过程中的优化对齐
a = 1 b = 4 c = 2 总长 7
*/

struct STRU2{ 
	short a;    
	char b;    
	int c;  
}__attribute__((aligned(1)));
/*
指定结构体1字节对齐，但是因为a和c类型长度大于指定1字节，
因此取结构成员最大长度对齐，即4字节对齐。
a = 2 b = 2 c = 4 总长8
*/

struct STRU3{ 
	char a;    
	char b;    
	char c;  
}__attribute__((aligned(1)));
/*
指定结构体1字节对齐
a = 1 b = 1 c = 1 总长 3
*/

typedef struct STRU4{ 
	short a;   
	double b;   
	int c;      
} st4 __attribute__((aligned(16)));
/*
指定结构体成员16字节对齐
a = 8 b = 8 c = 16 总长 32
*/

int main(void)
{
	printf("STRU1 = %ld\n",sizeof(struct STRU1));
	printf("STRU2 = %ld\n",sizeof(struct STRU2));
	printf("STRU3 = %ld\n",sizeof(struct STRU3));
	printf("STRU4 = %ld\n",sizeof(struct STRU4));
	return 0;
}

