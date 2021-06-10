#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
函数名：IsNumStr
描述：
	判断当前字符串是不是数字字符串
参数：
	pstr：指定进行判断的字符串
返回值：
	是数字字串返回 1，否则返回0
*/

int IsNumStr(const char *pstr)
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
*  十六进制字符串转十进制
*/
int htoi(char s[]) 
{
        int i = 0; 
        int n = 0; 

        for (i=0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') 
                        || (s[i] >= 'A' && s[i] <= 'Z'); i++) {
                if (s[i] <= '9') {
                        n = 16 * n + (s[i] - '0');
                }    
                else if (s[i] >= 'a') {
                        n = 16 * n + (10 + s[i] - 'a');
                }    
                else if (s[i] >= 'A') {
                        n = 16 * n + (10 + s[i] - 'A');
                }    
        }    

        return n;
}

/* 
*  十进制转十六进制字符串
*/
void itoh(int n, char s[]) 
{
        char base[16] = {'0', '1', '2', '3', 
                         '4', '5', '6', '7', 
                         '8', '9', 'A', 'B', 
                         'C', 'D', 'E', 'F'};
        int a = n; 
        int i = 0; 
        int j = 0; 
        char t = 0; 

        while (a != 0) { 
                s[i++] = base[a%16];
                a /= 16;
        }
        s[i] = '\0';

        /* 倒置 */
        j = strlen(s) - 1;
        i = 0;
        while (i<j) {
                t = s[i];
                s[i] = s[j];
                s[j] = t;

                i++;
                j--;
        }
}

/*求最大公约数
*/
int calc_gcd(int w, int h)
{
    int a = w;
    int b = h;
    int c = 0;
    while (b!=0) {
	c = a%b;
	a = b;
	b = c;
    }     
    return a;
}

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


