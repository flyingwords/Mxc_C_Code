#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*示例：Util_Update_Conf
*/
#if 0
int main(void)
{
	system("echo \"I like code\" > ./test.conf");
	Util_Update_Conf("./test.conf", "code", "hello world, man");
	return 0;
}
#endif


/*示例：Util_Str_GetItem
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666;";
	char out_str[128+1] = "";
	int out_str_len = 0;
	out_str_len = Util_Str_GetItem(src_str, "my name = ", out_str, 128, ";my num");
	printf("out_str_len = %d\n", out_str_len);
	printf("out_str = %s\n", out_str);	
	return 0;
}
#endif


/*示例：Util_Str_GetItemToLong
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666666;";
	long out_long = Util_Str_GetItemToLong(src_str, "my num = ", ";");
	printf("out_long = %ld\n", out_long);
	return 0;
}
#endif


/*示例：Util_Str_FindItem
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666;";
	char sub_str[128+1] = "maxucan";
	if (!Util_Str_FindItem(src_str, sub_str))
		printf("y\n");
	else
		printf("n\n");
	return 0;
}
#endif


