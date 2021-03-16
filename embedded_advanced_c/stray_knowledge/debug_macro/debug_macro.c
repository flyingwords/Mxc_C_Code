#include<stdio.h>

/*
程序功能描述：最基本DEBUG宏的使用,只能打印字符串
*/


#define DEBUG  
//#undef DEBUG  //取消宏定义DEBUG
#ifdef DEBUG    //使用宏定义打印调试信息
#define debug(x) printf(x)
#else
#define debug(x) 
#endif

int main()
{
	int val=5000;
	char *str = "helloworld";
	//debug("now you want to debug, val = %d str = %s\n", val, str); 
	debug("now you want to debug\n");
	return 0;
}






