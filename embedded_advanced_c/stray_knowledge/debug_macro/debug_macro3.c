#include<stdio.h>


/*
程序功能描述：不仅能打印变量，还能设置打印级别的的DEBUG宏的使用
*/



#ifndef DBG_OUT_H 
#define DBG_OUT_H 

#define DBG_ERR   1
#define DBG_INFO  7
#define DBG_LEVEL 0		//all message


#ifndef dbg_out
#define dbg_out(level, format, args...) \
	{ \
	if(level<=DBG_LEVEL){ \
		if(level==DBG_ERR){ \
			fprintf(stderr,#level":%s %s[%04d] " format, __FILE__, __FUNCTION__, __LINE__, ##args); \
			fflush(stderr); \
		}\
  		else{ \
  			fprintf(stdout,#level":%s %s[%04d] " format, __FILE__, __FUNCTION__, __LINE__, ##args); \
			fflush(stdout); \
		}\
	} \
	}

#endif
#endif


int main(void)
{

	int val=5000;
	char *str = "helloworld";
	dbg_out(DBG_INFO, "INFO MSG, val = %d str = %s\n", val, str);
	dbg_out(DBG_ERR, "ERROR MSG, val = %d str = %s\n", val, str);
	return 0;
}


