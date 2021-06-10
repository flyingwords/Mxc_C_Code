#ifndef __UTIL_PROCESS_
#define __UTIL_PROCESS_
/*
函数名：find_pid
描述：
	查询进程的pid
参数：
	pidname：进程的名称
返回值：
	成功返回PID
	失败返回 -1
*/
int find_pid(char pidname[]);

/* 结束进程, level一般是9 
*/
void kill_pid(char pid_name[], char level[]);


/*
函数名：readCmdResult
描述：
	读取命令的执行结果
参数：
	cmd: 命令
	result: 输出，执行命令返回结果
	size: result buffer的大小
返回值：
	返回结果的长度
	失败返回-1
*/
int readCmdResult(char *cmd, char *result, unsigned int size);
#endif
