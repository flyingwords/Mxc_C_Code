#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

/*
程序功能描述：测试inet_lnaof和inet_netof的使用
inet_lnaof：获取二进制地址(网络字节序)的二进制主机号 
inet_netof：获取二进制地址(网络字节序)的二进制网络号
*/

int main()
{
	struct in_addr ip,local,network;
	char addr1[]="192.168.1.1";		/*a.b.c.d类型的网络地址字符串*/

	ip.s_addr = inet_addr(addr1);
	if(ip.s_addr != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr1, ip.s_addr);

	}else{
		printf("inet_addr:string %s  error\n",addr1);
	};
	

	local.s_addr = inet_lnaof(ip);
	printf("inet_lnaof: local:0x%x \n",local.s_addr);
	network.s_addr = inet_netof(ip);
	printf("inet_netof: network:0x%x \n",network.s_addr);	
}


