/*
程序功能描述：分析预处理会处理哪些内容
*/

#include"stdio.h"	//头文件
#define NUM 54      //宏定义

int main()
{
	#if (NUM == 54) //条件宏
	{
		int c = NUM;
		printf("c = %d\n",c);
	}
	#else 
	printf("error\n");
	#endif
	
	#ifdef NUM 
	{
		printf("the NUM is defined\n");
	}
	#else
		printf("never define the NUM\n");
	#endif


	/*
	
	执行命令得到预处理之后的文件：gcc -E preprocess.c -o preprocess.i
	
	预处理总结：
	1、会将头文件的内容包含到当前文件中
	2、会将注释去除掉
	3、会对文件中的宏定义做替换
	4、会分析条件宏，将结果为真的代码包含进来，将结果为非真的代码去除
	*/
	return 0;
}


