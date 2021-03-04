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

/*
函数名：Util_Socket_GetIP
描述：
	获取网卡设备eth0的IP	
参数：
	pIPBuf：输出，用来保存获取的ip地址
返回值：
	无
*/
void Util_Socket_GetIP(char* pIPBuf)
{
	int sock_get_ip;  
	
	struct	 sockaddr_in *sin;	
	struct	 ifreq ifr_ip;	   
	
	if ((sock_get_ip=socket(AF_INET, SOCK_STREAM, 0)) == -1) {	
			return;  
	}	 
	
	memset(&ifr_ip, 0, sizeof(ifr_ip)); 	
	strncpy(ifr_ip.ifr_name, "eth0", sizeof(ifr_ip.ifr_name) - 1);	   
	
	if (ioctl(sock_get_ip, SIOCGIFADDR, &ifr_ip) < 0) { 	
			return; 	
	}	  
	sin = (struct sockaddr_in *)&ifr_ip.ifr_addr;	  
	strcpy(pIPBuf, inet_ntoa(sin->sin_addr));	  
	close(sock_get_ip);   

}



/*
函数名：Util_Dev_PrintIP
描述：
	打印设备的所有IP地址(IPv4 IPv6)
参数：
	无
返回值：
	无
*/
void Util_Dev_PrintIP(void) {
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } else if (ifa->ifa_addr->sa_family==AF_INET6) { // check it is IP6
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
        } 
    }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
}

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
int Util_IP_To_Hostname(const char* ip)
{
    int ret = 0;

    if(!ip)
    {
        printf("invalid params\n");
        return -1;
    }

    struct addrinfo hints;
    struct addrinfo *res, *res_p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME | AI_NUMERICHOST;
    hints.ai_protocol = 0;

    ret = getaddrinfo(ip, NULL, &hints, &res);
    if(ret != 0)
    {
        printf("getaddrinfo: %s\n", gai_strerror(ret));
        return -1;
    }

    for(res_p = res; res_p != NULL; res_p = res_p->ai_next)
    {
        char host[1024] = {0};
        ret = getnameinfo(res_p->ai_addr, res_p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NAMEREQD);
        if(ret != 0)
        {
            printf("getnameinfo: %s\n", gai_strerror(ret));
        }
        else
        {
            printf("hostname: %s\n", host);
        }
    }
    freeaddrinfo(res);
    return ret;
}


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
int Util_Hostname_To_IP(const char* hostname)
{
    int ret = 0;

    if(!hostname)
    {
        printf("invalid params\n");
        return -1;
    }
    struct addrinfo hints;
    struct addrinfo *res, *res_p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_protocol = 0;

    ret = getaddrinfo(hostname, NULL, &hints, &res);
    if(ret != 0)
    {
        printf("getaddrinfo: %s\n", gai_strerror(ret));
        return -1;
    }
    for(res_p = res; res_p != NULL; res_p = res_p->ai_next)
    {
        char host[1024] = {0};
        ret = getnameinfo(res_p->ai_addr, res_p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        if(ret != 0)
        {
            printf("getnameinfo: %s\n", gai_strerror(ret));
        }
        else
        {
            printf("ip: %s\n", host);
        }
    }
    freeaddrinfo(res);
    return ret;
}

