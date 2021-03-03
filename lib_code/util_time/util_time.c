#include <sys/prctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <termios.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <linux/tcp.h>
#include <sys/prctl.h>
#include "util_time.h"

/*
函数名：Util_SetDataTime
描述：
	按照指定结构体格式 设置系统时间
参数：
	inData：输入，指向Util_SetDataTime结构体
	outDate：输出，返回设置后的时间（时间起点：UTC起点时间）
返回值：
	设置成功返回0，失败返回-1.
*/

int Util_SetDataTime(void* inData, void* outData)
{
	int nReturn = -1;
	Util_STU_TIME *pTime = (Util_STU_TIME*)inData;
	if( pTime != NULL)
	{
		//printf("%d-%d-%d %d:%d:%d\n", pTime->nYear, pTime->nMonth, pTime->nDay, pTime->nHour, pTime->nMinute, pTime->nSecond);
		struct tm tm;
		struct timeval tv = { 0, 0 };
		
		memset ( &tm, 0, sizeof( struct tm ));
		tm.tm_year = pTime->nYear-1900;
		tm.tm_mon = pTime->nMonth-1;
		tm.tm_mday = pTime->nDay;
		tm.tm_hour = pTime->nHour;
		tm.tm_min = pTime->nMinute;
		tm.tm_sec = pTime->nSecond;				
		
		tv.tv_sec = mktime ( &tm );
		//printf("mktime设置的时间为：%ld秒\n", tv.tv_sec);
		
		if( settimeofday ( &tv, NULL )<0 )
		{
			perror("settimeofday");
			nReturn = -1;
		}

		*((unsigned long int *)outData) = tv.tv_sec;
		nReturn = 0;
	}
	return nReturn;
}

