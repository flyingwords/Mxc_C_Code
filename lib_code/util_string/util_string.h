#ifndef __UTIL_STRING__
#define __UTIL_STRING__

/*
函数名：Util_IsNumStr
描述：
	判断当前字符串是不是数字字符串
参数：
	pstr：指定进行判断的字符串
返回值：
	是数字字串返回 1，否则返回0
*/

int Util_IsNumStr(const char *pstr);

/*
函数名：Util_Itoa
描述：
	将整形转换为字符串函数（只能转换正的整形数）
参数：
	i：输入，整形数
	strbuf：输出，转换后的字符串
返回值：
	无
*/
void Util_Itoa(int i, char *strbuf);

/*
函数名：Util_Update_Conf
描述：
	根据关键字更新配置行
参数：
	path：文件
	keyword：关键字
	item：新的配置行
返回值：
	成功	0 失败-1
*/
int Util_Update_Conf(char *path, char *keyword, char *item);

/*
函数名：Util_Str_GetItem
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
int Util_Str_GetItem(const char* pSrc, const char* pItemText, char *pBuf, int nBufLen, char *pEnd);

/*
函数名：Util_Str_FindItem
描述：
	查询源串pSrc是否含有子串pItemText
参数：
	pSrc：源串
	pItemText：子串
返回值：
	含有子串返回0，否则返回-1
*/
int Util_Str_FindItem( const char *pSrc, const char* pItemText);

#endif
