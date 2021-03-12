#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define PORT 8888								/*侦听端口地址*/
void sig_proccess(int signo);
void sig_pipe(int signo);
void process_conn_client(int s);

int main(int argc, char *argv[])
{
	int s;										/*s为socket描述符*/
	struct sockaddr_in server_addr;			/*服务器地址结构*/
	int options,ret;	
	fd_set writefds;
	struct timeval timeout;
	int err = 0;
	socklen_t elen;

	signal(SIGINT, sig_proccess);				/*挂接SIGINT信号，处理函数为		  sig_process()*/
	signal(SIGPIPE, sig_pipe);					/*挂接SIGPIPE信号，处理函数为sig_pipe()*/
	
	s = socket(AF_INET, SOCK_STREAM, 0); 		/*建立一个流式套接字 */
	if(s < 0){									/*出错*/
		printf("socket error\n");
		return -1;
	}	
	
	/*设置服务器地址*/
	bzero(&server_addr, sizeof(server_addr));	/*清零*/
	server_addr.sin_family = AF_INET;					/*协议族*/

	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);	/*本地地址*/
	server_addr.sin_port = htons(PORT);				/*服务器端口*/


#if 1
	/*非阻塞方式连接服务器*/	
    options = fcntl(s, F_GETFL, 0); 
    fcntl(s, F_SETFL, options | O_NONBLOCK);

	ret = connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));	
	if(ret == 0)
    {
      	printf("1:connected.\n");
    }
	else if(ret < 0)
	{
			//perror("connect"); 
      	if(errno == EINPROGRESS)
      	{
      	 	printf("connecting..:%d\n",PORT);
 
            FD_ZERO(&writefds);
            FD_SET(s, &writefds);                 
 
            timeout.tv_sec = 6; 
            timeout.tv_usec = 0;     
 
            ret = select(s + 1, NULL, &writefds, NULL, &timeout );
			if (ret < 0){
				perror("select");
				close(s);
				return -1;
			}
			else
            {	
				if (!FD_ISSET(s, &writefds)){
					printf("err, no events found!\n");
					close(s);
					return -1;
				}else{
					ret = getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &elen);
					if(ret < 0){
						perror("getsockopt");
						close(s);
						return -1;
					}
					if(err != 0){
						printf("connect failed with the error: (%d)%s\n", err, strerror(err));
						close(s);
						return -1;
					}else{
						printf("2:connected.\n");
					}
				}
            
			}
			
      	}
	}

	/*重新设置socket为阻塞*/
	options = fcntl(s, F_GETFL, 0); 
    fcntl(s, F_SETFL, options & ~O_NONBLOCK);
#else
	connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));	
#endif

	process_conn_client(s);						/*客户端处理过程*/

	close(s);									/*关闭连接*/
	return 0;
}

