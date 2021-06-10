
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util_string.h"

/*示例：Str_GetItem
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666;";
	char out_str[128+1] = "";
	int out_str_len = 0;
	out_str_len = Str_GetItem(src_str, "my name = ", out_str, 128, ";my num");
	printf("out_str_len = %d\n", out_str_len);
	printf("out_str = %s\n", out_str);	
	return 0;
}
#endif


/*示例：htoi
*/
#if 0
int main(void)
{
	char hex_str[5] = "11";
	int dec_num = htoi(hex_str);
	printf("dec_num = %d\n", dec_num);
}
#endif

/*示例：itoh
*/
#if 0
int main(void){
	int dec_num = 20;
	char hex_str[5] = "";
	itoh(dec_num, hex_str);
	printf("hex_str = %s\n", hex_str);
}
#endif

/*示例：calc_gcd
*/
#if 0
int main(void){
	int gcd = calc_gcd(40, 8);
	printf("gcd = %d\n", gcd);
}
#endif

/*示例：Str_GetItemToLong
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666666;";
	long out_long = Str_GetItemToLong(src_str, "my num = ", ";");
	printf("out_long = %ld\n", out_long);
	return 0;
}
#endif


/*示例：Str_FindItem
*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666;";
	char sub_str[128+1] = "maxucan";
	if (!Str_FindItem(src_str, sub_str))
		printf("y\n");
	else
		printf("n\n");
	return 0;
}
#endif


