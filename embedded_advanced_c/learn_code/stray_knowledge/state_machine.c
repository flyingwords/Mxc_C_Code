#include<stdio.h>
enum {state1,state2,state3,state4,state5,state6,state7}state;

/*

程序功能描述：编译一个简单的状态机，用来模拟密码锁
*/
int main(void)
{
	int num = 0;
	state = state1;
	printf("please input the num:\n");
	while(1)
	{
		scanf("%d",&num);
		printf("num = %d\n",num);
		switch(state)
		{
			case state1:if(num == 1)
							state = state2;
						else state = state1;
							break;
			case state2:if(num == 2)
							state = state3;
						else state = state1;
							break;
			case state3:if(num == 2)
							state = state4;
						else state = state1;
							break;
			case state4:if(num == 2)
							state = state5;
						else state = state1;
							break;
			case state5:if(num == 2)
							state = state6;
						else state = state1;
							break;
			case state6:if(num == 2)
							state = state7;
						else state = state1;
							break;
			default:	state = state1;
						break;
		}
		if(state == state7)
		{
			printf("the lock is unlock!!\n");
			state = state1;
		}
	}
	
	return 0;
}