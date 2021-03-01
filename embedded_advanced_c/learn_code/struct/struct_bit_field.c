#include<stdio.h>
/*
程序功能描述：分析位域在内存中的排布规律。
位域在内存中排布的规律：在字节层面上，无论大小端，都会将位域从低地址字节向高地址字节排列。
在字节内部的位的层面上，大端模式位域从高权重bit向低权重bit排列，小端模式反之。
*/


/*
单字节位域分配测试
	大端输出结果：0x91
	小端输出结果：0x13

说明：小端从字节的LSB开始分配，大端从字节的MSB开始分配
*/

#if 0
struct
{
    unsigned char a:1;
    unsigned char b:3;
    unsigned char c:4;
} A;

main()
{
	int i;
    unsigned char *p;
    A.a=1;
    A.b=1;
    A.c=1;
    for(i=0;i<sizeof(A);i++)
    {
        p=((unsigned char *)&A)+i;
        printf("0x%02x ",*p);
    }
    printf("\n");
}
#endif


/*
多字节位域分配测试
	大端输出结果：0x13 0x7f
	小端输出结果：0x31 0xf7

说明：大小端都从低字节开始分配bit
*/
#if 0
struct
{
    unsigned short a:4;
    unsigned short b:4;
    unsigned short c:4;
    unsigned short d:4;
} B;
void main()
{
    int i;
    unsigned char *p;
    B.a=1;
    B.b=3;
    B.c=7;
    B.d=15;
    for(i=0;i<sizeof(B);i++)
    {
        p=((unsigned char *)&B)+i;
        printf("0x%02x ",*p);
    }
    printf("\n");
}
#endif

/*
跨字节位域分配测试：
	大端输出结果：0x20 0x67
	小端输出结果：0x19 0x38

说明：
对于小端：字节可以这样排列 High Byte | Low Byte ，位域从右向左分配
对于大端：字节可以这样排列 Low Byte | High Byte，位域从左向右分配
*/
#if 1
struct
{
    unsigned short a:3;
    unsigned short b:8;
    unsigned short c:5;
} D;
void main()
{
    int i;
    unsigned char *p;
    D.a=1;
    D.b=3;
    D.c=7;
    for(i=0;i<sizeof(D);i++)
    {
        p=((unsigned char *)&D)+i;
        printf("0x%02x ",*p);
    }
    printf("\n");
}
#endif
