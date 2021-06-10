#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

/*
程序功能描述：介绍IP地址转换函数inet_addr的使用
inet_addr：点分十进制字符串 -> 二进制地址（网络字节序）
注意：inet_addr不能转换255.255.255.255
*/

int main(int argc, char *argv[])
{
	struct in_addr ip;
	char addr1[]="192.168.1.1";			/*a.b.c.d类型的网络地址字符串*/
	char addr2[]="255.255.255.255";		/*二进制值为全1的IP地址对应的字符串*/
	
	ip.s_addr = inet_addr(addr1);
	if(ip.s_addr != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr1, ip.s_addr);

	}else{
		printf("inet_addr:string %s  error\n",addr1);
	};
	ip.s_addr = inet_addr(addr2);
	if(ip.s_addr != -1){
		printf("inet_addr:string %s value is:0x%x\n",addr2, ip.s_addr);	
	}else{
		printf("inet_addr:string %s  error\n",addr2);
	};
	printf("----------------------\n");
}
