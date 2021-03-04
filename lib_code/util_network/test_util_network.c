#include <stdio.h>
#include <string.h>  
#include <netinet/in.h> 
#include <sys/types.h>  
#include <sys/ioctl.h>  
#include <sys/socket.h>  
#include <net/if.h>  
#include <unistd.h>  
#include <netdb.h>  
#include <fcntl.h>  
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include "util_network.h"

/*
示例：Util_Socket_GetIP
*/
#if 0
int main(void)
{
	int ret = -1;
	char cLocalIP[20] = {0};
	Util_Socket_GetIP(cLocalIP);
	printf("cLocalIP is %s\n", cLocalIP);
	return 0;
}
#endif 


/*
示例：Util_Hostname_To_IP
*/
#if 0
int main(void)
{
	Util_Hostname_To_IP("www.baidu.com");
	return 0;
}
#endif 

/*
示例：Util_IP_To_Hostname
*/
#if 1
int main(void)
{
	Util_IP_To_Hostname("104.193.88.77");
	return 0;
}
#endif 




