#include<stdio.h>
int main()
{

//给定一个整形数a，使a的bit9-bit11为零
#if 0
	int a = 0xFFFFFFFF;
	a &= (~(7<<9));
	printf("a = 0x%x\n",a);
#endif 


//给定一个整形数a，使a的bit17-bit21,bit3-bit8置1
#if 0
	int a = 0x0;
	a |= (0x1F<<17)|(0x3F<<3);
	printf("a = 0x%x\n",a);
#endif



	//给定一个整形数a，使a的bit6-bit15取反
#if 0
	int a = 0xFFFFFFFF;
	a ^= 0x3ff << 6;
	printf("a = 0x%x\n",a);
#endif 
	
//给定一个整形数a，取出a的bit3~bit8
#if 0
	unsigned int a = 0xffffffff;
	unsigned int tem = 0;
	tem = a & (0x3f << 3);
	tem >>= 3;
	printf("tem = 0x%x",tem);
#endif 

	

//用C语言给一个寄存器的bit7～bit17赋值937
#if 0

	unsigned int a = 0xffffffff;
	unsigned int tem = 0;
	a &= ~(0x7ff<<7);
	a |= (937<<7);
	printf("a = 0x%x\n",a);
	//验证
	tem =(a&(0x7ff<<7))>>7;
	printf("tem = %d\n",tem);
#endif 
	

//用C语言将一个寄存器的bit7～bit17中的值加17（其余位不受影响）
#if 0
	unsigned int a = 0x11111111;
	unsigned int tem = 0;
	unsigned int b = a;
	tem = (a&(0x7ff<<7))>>7;
	tem += 17;
	a &= ~(0x7ff<<7);
	a |=( tem<<7);
	printf("a = 0x%x\n",a);
	//验证
	b = (a - b)>>7;
	printf("b = %d\n",b);
#endif 	
	
	//用C语言给一个寄存器的bit7～bit17赋值937，同时给bit21～bit25赋值17
#if 0
	unsigned int a = 0x11111111;
	unsigned int b,c;
	b = c = 0;
	a &= ~((0x7ff<<7)|(0x1f<<21));
	a |= ((937<<7)|(17<<21));
	printf("a = 0x%x\n",a);
	//验证
	b = (a&((0x7ff<<7)))>>7;
	c = (a&((0x1f<<21)))>>21;
	printf("b = %d\n",b);
	printf("c = %d\n",c);
#endif 
	return 0;
}
