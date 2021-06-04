#ifndef __UTIL_EPOLL_
#define __UTIL_EPOLL_
/*
函数名：Epoll_Create
描述：
	创建一个epoll
参数：
	无
返回值：
	成功返回epoll文件描述符
	失败返回-1
*/
int Epoll_Create( void);

/*
函数名：Epoll_SetNonblocking
描述：
	设置描述符为非阻塞
参数：
	fd：描述符
返回值：
	返回描述符旧的属性
*/
int Epoll_SetNonblocking( int fd);

/*
函数名：Epoll_DeleteFD
描述：删除epoll中的描述符
参数：
	nEpollFd：	epoll描述符
	fd		：	要删除的描述符
返回值：
	无
*/
void Epoll_DeleteFD( int nEpollFd, int fd);

/*
函数名：Epoll_DeleteFD
描述：给epoll添加描述符，并配置输入和单次触发事件
参数：
	nEpollFd：	epoll描述符
	fd		：	要添加的描述符
返回值：
	无
*/
void Epoll_DeleteFD( int nEpollFd, int fd);

/*
函数名：EPoll_ModifyFD
描述：配置epoll中描述符的事件
参数：
	nEpollFd：	epoll描述符
	fd		：	要配置的描述符
	nEvent	：	要配置的事件
返回值：
	无
*/
void EPoll_ModifyFD( int nEpollFd, int fd, int nEvent);
#endif
