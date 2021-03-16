#include<stdio.h>

/*
程序功能描述：分析对齐宏 #pragma pack(n) 和 #pragma pack() 对结构体对齐的影响

1.在有#pragma pack(n)宏的情况下
有宏定义的情况下 结构体的自身宽度 就是宏上规定的数值大小，所有内存都按照这个宽度去对齐
#pragma pack 参数只能是 '1', '2', '4', '8', or '16'

2.在没有#pragma pack(n)宏的情况下
没有宏定义的情况下  结构体的自身宽度有最大成员属性的宽度决定  

3.使用#pragma pack()表示从当前位置开始取消#pragma pack(n)的对齐宽度指定
*/

//#pragma pack(1)
#pragma pack(4)

struct STRU1{ 
	char a;		
	int b;		
	short c;    
}; 
/*
pack 1
a = 1 b = 4 c = 2 总长7
pack 4
a = 4 b = 4 c = 4 总长 12

*/

struct STRU2{ 
	short a;    
	char b;    
	int c;      
};		
/*pack 1
a = 2 b = 1 c = 4 总长7
pack 4
a = 2 b = 2 c = 4 总长 8

*/
//#pragma pack() //从当前位置开始取消#pragma pack(n)的对齐宽度指定

struct STRU3{ 
	short a;    
	double b;   
	int c;      
};		
/*pack 1
a = 2 b = 8 c = 4 总长14
pack 4
a = 4 b = 8 c = 4 总长 16
*/
#pragma pack() 

int main(void)
{
	printf("STRU1 = %ld\n",sizeof(struct STRU1));
	printf("STRU2 = %ld\n",sizeof(struct STRU2));
	printf("STRU3 = %ld\n",sizeof(struct STRU3));
	return 0;
}

