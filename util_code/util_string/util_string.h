#ifndef __UTIL_STRING__
#define __UTIL_STRING__

/*
函数名：IsNumStr
描述：
	判断当前字符串是不是数字字符串
参数：
	pstr：指定进行判断的字符串
返回值：
	是数字字串返回 1，否则返回0
*/

int IsNumStr(const char *pstr);

/*
函数名：itoa
描述：
	将整形转换为字符串函数（只能转换正的整形数）
参数：
	i：输入，整形数
	strbuf：输出，转换后的字符串
返回值：
	无
*/
void itoa(int i, char *strbuf);

/* 
*  十六进制字符串转十进制
*/
int htoi(char s[]);

/* 
*  十进制转十六进制字符串
*/
void itoh(int n, char s[]);

/*求最大公约数
*/
int calc_gcd(int w, int h);

/*
函数名：Str_GetItem
描述：
	从源串pSrc中，提取关键字串pItemText后面的字符，当遇到
	子串pEnd，结束提取，将提取字符串保存到pBuf中
参数：
	pSrc：源字符串
	pItemText：关键字符串
	pBuf：保存提取字符串的内存
	nBufLen：pBuf所指内存大小
	pEnd：结束子串
返回值：
	失败返回-1
	成功返回提取字符长度
*/
int Str_GetItem(const char* pSrc, const char* pItemText, char *pBuf, int nBufLen, char *pEnd);

/*
函数名：Str_FindItem
描述：
	查询源串pSrc是否含有子串pItemText
参数：
	pSrc：源串
	pItemText：子串
返回值：
	含有子串返回0，否则返回-1
*/
int Str_FindItem( const char *pSrc, const char* pItemText);

#endif
