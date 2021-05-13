#ifndef __UTIL_TIME_
#define __UTIL_TIME_

typedef struct
{
	int  nYear; 		//年
	int  nMonth; 		//月
	int  nDay; 			//日
	int  nHour;			//时
	int  nMinute; 		//分
	int  nSecond;		//秒
}Util_STU_TIME; //时间结构

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

int Util_SetDataTime(void* inData, void* outData);

#endif
