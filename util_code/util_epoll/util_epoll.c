#include <sys/ioctl.h>
#include <linux/sockios.h>

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
int Epoll_Create( void)
{
	int epoll_fd = epoll_create(10); //内核2.6.8起，参数无效
	if (epoll_fd < 0){
		perror("epoll_create");
		return -1;
	}
	return epoll_fd;
}

/*
函数名：Epoll_SetNonblocking
描述：
	设置描述符为非阻塞
参数：
	fd：描述符
返回值：
	返回描述符旧的属性
*/
int Epoll_SetNonblocking( int fd)
{
	int old_option = fcntl( fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option);
	return old_option;
}

/*
函数名：Epoll_DeleteFD
描述：删除epoll中的描述符
参数：
	nEpollFd：	epoll描述符
	fd		：	要删除的描述符
返回值：
	无
*/
void Epoll_DeleteFD( int nEpollFd, int fd)
{
	struct epoll_event event;
	epoll_ctl( nEpollFd, EPOLL_CTL_DEL, fd, &event);
}

/*
函数名：Epoll_AddFD
描述：给epoll添加描述符，并配置输入和单次触发事件
参数：
	nEpollFd：	epoll描述符
	fd		：	要添加的描述符
返回值：
	无
*/
void Epoll_DeleteFD( int nEpollFd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLONESHOT;
	epoll_ctl( nEpollFd, EPOLL_CTL_ADD, fd, &event);
	util_set_non_blocking(fd);
}

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
void EPoll_ModifyFD( int nEpollFd, int fd, int nEvent)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLONESHOT | nEvent;
	epoll_ctl( nEpollFd, EPOLL_CTL_MOD, fd, &event);
}

