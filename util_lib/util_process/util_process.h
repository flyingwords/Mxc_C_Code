#ifndef __UTIL_PROCESS_
#define __UTIL_PROCESS_
/*
函数名：FindPid
描述：
	查询进程的pid
参数：
	pidname：进程的名称
返回值：
	成功返回PID
	失败返回 -1
*/
int FindPid(char pidname[]);

#endif
