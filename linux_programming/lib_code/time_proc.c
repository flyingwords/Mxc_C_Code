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

/*
函数名：SetDataTime
描述：
	按照指定结构体格式 设置系统时间
参数：
	inData：输入，指向STU_TIME结构体
	outDate：输出，返回设置后的时间（时间起点：UTC起点时间）
返回值：
	设置成功返回0，失败返回-1.
*/

typedef struct
{
	int  nYear; 		//年
	int  nMonth; 		//月
	int  nDay; 			//日
	int  nHour;			//时
	int  nMinute; 		//分
	int  nSecond;		//秒
}STU_TIME; //时间结构

int SetDataTime(void* inData, void* outData)
{
	int nReturn = -1;
	STU_TIME *pTime = (STU_TIME*)inData;
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

/*示例*/
#if 0
int main(void)
{
	STU_TIME stuTime;
	struct timeval tv = { 0, 0 };
	unsigned long int time_sync_sec = 0;

	//填充时间结构体
	sscanf( "2020-07-18T10:05:26.560", "%d-%d-%dT%d:%d:%d", &stuTime.nYear, &stuTime.nMonth, &stuTime.nDay\
						, &stuTime.nHour, &stuTime.nMinute, &stuTime.nSecond);
		printf("%d-%d-%d %d:%d:%d \n",stuTime.nYear, stuTime.nMonth, stuTime.nDay\
						, stuTime.nHour, stuTime.nMinute, stuTime.nSecond);

	//查询设置前时间			
	gettimeofday(&tv, NULL);
	printf("gettimeofday得到设置前的时间：\n");
	printf("秒数：%lu  微妙：%lu\n", tv.tv_sec, tv.tv_usec);

	SetDataTime(&stuTime, &time_sync_sec);

	//查询设置后时间
	gettimeofday(&tv, NULL);
	printf("gettimeofday得到设置后的时间：\n");
	printf("秒数：%lu  微妙：%lu\n", tv.tv_sec, tv.tv_usec);

	return 0;
}
#endif



