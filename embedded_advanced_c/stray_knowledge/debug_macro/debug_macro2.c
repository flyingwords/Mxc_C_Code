#include<stdio.h>

/*
程序功能描述：能打印变量的DEBUG宏的使用
*/


#define __DEBUG__
#ifdef __DEBUG__
	#define TRACE(fmt, ...) \
			fprintf(stdout, "[file \"%s\": line %d]: "fmt, __FILE__, __LINE__, ## __VA_ARGS__)
	
	#define ERROR(fmt, ...) \
			fprintf(stderr, "[file \"%s\": line %d,ERR]: "fmt, __FILE__, __LINE__, ## __VA_ARGS__)
#else
	#define TRACE(fmt, ...) do {} while (0)
	#define ERROR(fmt, ...) do {} while (0)
#endif

#line 200

int main()
{
	int val=5000;
	char *str = "helloworld";
	TRACE("now you want to debug, val = %d str = %s\n", val, str);
	ERROR("now you want to debug, val = %d str = %s\n", val, str);
	return 0;
}


