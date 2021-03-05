#ifndef __UTIL_NETWORK_
#define __UTIL_NETWORK_

/*
函数名：Util_Socket_GetIP
描述：
	获取网卡设备eth0的IP	
参数：
	pIPBuf：输出，用来保存获取的ip地址
返回值：
	无
*/
void Util_Socket_GetIP(char* pIPBuf);

/*
函数名：Util_Dev_PrintIP
描述：
	打印设备的所有IP地址
参数：
	无
返回值：
	无
*/
int Util_Dev_PrintIP(void);

/*
函数名：Util_IP_To_Hostname
描述：
	获取IP地址的域名并打印出来
参数：
	ip：ip地址字符串
返回值：
	失败返回-1
	成功返回0
*/
int Util_IP_To_Hostname(const char* ip);


/*
函数名：Util_Hostname_To_IP
描述：
	转换域名为IP地址并打印
参数：
	hostname：域名字符串
返回值：
	失败返回-1
	成功返回0
*/
int Util_Hostname_To_IP(const char* hostname);

/*
函数名：Util_Is_SocketType
描述：
	判断文件描述符是不是socket描述符
参数：
	fd：描述符
返回值：
	1 socket描述符
	0 非socket描述符
*/
int Util_Is_SocketType(int fd);

#endif
