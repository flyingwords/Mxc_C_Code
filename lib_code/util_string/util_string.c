#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
函数名：isnumstr
描述：
	判断当前字符串是不是数字字符串
参数：
	pstr：指定进行判断的字符串
返回值：
	是数字字串返回 1，否则返回0
*/

int isnumstr(const char *pstr)
{
    if (strspn(pstr, "0123456789") == strlen(pstr))
    {   
    	return 1;
    }   
    else
    {   
        return 0;
    }   
}

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
void itoa(int i, char *strbuf)
{
	int power = 0;
	int j = 0;
	
	j = i;
	
	for (power=1; j>=10; j/=10) {
		power *= 10;
	}
	
	for (; power>0; power/=10) {
	   *strbuf++ = '0'+ i/power;
	   i %= power;
	}
	
	*strbuf = '\0';
}


/*
函数名：update_conf
描述：
	根据关键字更新配置行
参数：
	path：文件
	keyword：关键字
	item：新的配置行
返回值：
	成功	0 失败-1
*/
#define FILE_BUFF_SIZE 2048	//文件的大小不能超过2KB
int update_conf(char *path, char *keyword, char *item)
{
	FILE *fp = NULL;
	char *line = NULL;
	char dst_buff[FILE_BUFF_SIZE] = {0};
	char tmp_line[96] = {0};
	char shellcmd[96] = {0};
	size_t line_size = 0;
	int read = 0;

	fp = fopen(path, "r");
	if (fp == NULL) 
	{
		return -1;
	}
	
	// 每次读一行 --- 匹配待修改项 --- 修改 --- 写入新buff  --- 重新写入文件
	while (read = getline(&line, &line_size, fp) != -1) 
	{
		if (line[0] == '\0') 
		{
			continue;
		}
		
		// 匹配修改项目
		if (strstr(line, keyword) != NULL) 
		{
			memcpy(tmp_line, item, strlen(item));
			strcat(tmp_line, "\n");
		} 
		else 
		{
			memcpy(tmp_line, line, strlen(line));
		}

		// 写入到新buff
		strcat(dst_buff, tmp_line);

		memset(tmp_line, 0, sizeof(tmp_line));
	}
	free(line);
	fclose(fp);
	fp = NULL;

	// 删除源文件
	sprintf(shellcmd, "rm %s", path);
	system(shellcmd);

	// 重新写入文件
	fp = fopen(path, "w+");
	if (fp == NULL) {
		return -1;
	}

	fprintf(fp, "%s", dst_buff);
	fclose(fp);
	fp = NULL;
	
	return 0;
}

/*示例*/
#if 0
int main(void)
{
	system("echo \"I like code\" > ./test.conf");
	update_conf("./test.conf", "code", "hello world, man");
	return 0;
}
#endif


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
int Str_GetItem(const char* pSrc, const char* pItemText, char *pBuf, int nBufLen, char *pEnd)
{
	int nReturn = -1;
	if( pSrc == NULL || pBuf == NULL)
	{
		return nReturn;
	}
	if( pItemText == NULL)
	{//first pItemText
		char *pFindEnd = strcasestr( pSrc, pEnd);
		if ( pFindEnd != NULL)
		{
			int nCopy = pFindEnd - pSrc;
			if( nCopy > 0 && nCopy <= nBufLen)
			{
				memcpy( pBuf, pSrc, nCopy);
				nReturn = nCopy;
			}
		}
	}
	else
	{	
		char *pFind = strcasestr( pSrc, pItemText);
		if( pFind != NULL)
		{
			int nItemTextLen = strlen( pItemText);
			int nCopy = 0;
			if( pEnd == NULL)
			{/*剩下的数据*/
				nCopy = pSrc + strlen(pSrc) - pFind - nItemTextLen;
			}
			else		
			{
				char *pFindEnd = strcasestr( pFind, pEnd);
				if ( pFindEnd != NULL)
				{
					nCopy = pFindEnd - pFind - nItemTextLen;
				}				
			}
			if ( nCopy > 0 && nCopy <= nBufLen)
			{			
				memcpy( pBuf, pFind + nItemTextLen, nCopy);
				nReturn = nCopy;
			}
		}
	}
	return nReturn;
}

/*示例*/
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

/*
函数名：Str_GetItemToLong
描述：
	从源串pSrc中，提取关键字串pItemText后面的字符，当遇到
	子串pEnd，结束提取，并将提取字符串转换为long型返回。
	该函数提取的字符串必须是数字字符串。
参数：
	pSrc：源字符串
	pItemText：关键字符串
	pEnd：结束子串
返回值：
	失败返回-1
	成功返回转换后的long整型数
*/
long Str_GetItemToLong( const char* pSrc, const char* pItemText, char *pEnd)
{
	long lReturn = -1;
	if( pSrc == NULL || pItemText == NULL || pEnd == NULL)
	{
		return lReturn;
	}
	
	char cTemp[12] = {0};	
	if( Str_GetItem( pSrc, pItemText, cTemp, 12, pEnd) > 0)
	{
		lReturn = atol(cTemp);
	}
	return lReturn;
}

/*示例*/
#if 0
int main(void)
{
	char src_str[128] = "my name = maxucan;my num = 666666;";
	long out_long = Str_GetItemToLong(src_str, "my num = ", ";");
	printf("out_long = %ld\n", out_long);
	return 0;
}
#endif


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
int Str_FindItem( const char *pSrc, const char* pItemText)
{
	if( pSrc == NULL || pItemText == NULL || strcasestr( pSrc, pItemText) == NULL)
		return -1;
	return 0;
}

/*示例*/
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




