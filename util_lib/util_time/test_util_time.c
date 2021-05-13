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

/*示例：Util_SetDataTime
*/
#if 1
int main(void)
{
	Util_STU_TIME stuTime;
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

	Util_SetDataTime(&stuTime, &time_sync_sec);

	//查询设置后时间
	gettimeofday(&tv, NULL);
	printf("gettimeofday得到设置后的时间：\n");
	printf("秒数：%lu  微妙：%lu\n", tv.tv_sec, tv.tv_usec);

	return 0;
}
#endif

