#include <sys/ioctl.h>
#include <linux/sockios.h>


void Epoll_DeleteFD( int nEpollFd, int fd)
{
	struct epoll_event event;
	epoll_ctl( nEpollFd, EPOLL_CTL_DEL, fd, &event);
}

void Epoll_AddFD( int nEpollFd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLONESHOT;
	epoll_ctl( nEpollFd, EPOLL_CTL_ADD, fd, &event);
	SetNonblocking(fd);
}

void EPoll_ModifyFD( int nEpollFd, int fd, int nEvent)
{
///	trace_28181("nEpollFd =%d fd=%d\n",nEpollFd,fd);
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLONESHOT | nEvent;
	epoll_ctl( nEpollFd, EPOLL_CTL_MOD, fd, &event);
}

int SetNonblocking( int fd)
{
	int old_option = fcntl( fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl( fd, F_SETFL, new_option);
	return old_option;
}

