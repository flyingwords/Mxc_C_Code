/*
程序功能描述：测试getopt的使用
*/

#include <unistd.h>
#include <stdio.h>
int main(int argc, char * argv[])
{
	int ch;
	while ((ch = getopt(argc, argv, "ab:c:de::")) != -1) //不加 -或者 --，返回-1
	{
		printf("optind: %d\n", optind);
		switch (ch) 
		{
			case 'a':	//无需参数
			printf("HAVE option: -a\n\n");   
			break;
			case 'b':	//需要参数
			printf("HAVE option: -b\n"); 
			printf("The argument of -b is %s\n\n", optarg);
			break;
			case 'c':
			printf("HAVE option: -c\n");
			printf("The argument of -c is %s\n\n", optarg);
			break;
			case 'd':	
			printf("HAVE option: -d\n");
			break;
			case 'e':	//可选参数
			printf("HAVE option: -e\n");
			printf("The argument of -e is %s\n\n", optarg);
			break;
			case '?':	////选项有加-，但是找不到该选项，或者选项没加参数值
			printf("Unknown option: %c\n",(char)optopt);
			break;
		}
	}
}

