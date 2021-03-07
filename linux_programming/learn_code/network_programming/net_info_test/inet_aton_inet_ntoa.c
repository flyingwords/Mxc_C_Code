#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

/*
程序功能描述：介绍IP地址转换函数inet_aton、inet_ntoa的使用
inet_aton：点分十进制字符串 -> 二进制地址（网络字节序）
inet_ntoa：二进制地址（网络字节序）-> 点分十进制字符串，inet_ntoa不可重入
*/
int main(int argc, char *argv[])
{
	struct in_addr ip,local,network;
	char addr1[]="192.168.1.1";			/*a.b.c.d类型的网络地址字符串*/
	char addr2[]="255.255.255.255";		/*二进制值为全1的IP地址对应的字符串*/
	char *str=NULL,*str2=NULL;
	int err = 0;

	//测试inet_aton
	err = inet_aton(addr1, &ip);
	if(err){
		printf("inet_aton:string %s value is:0x%x\n",addr1, ip.s_addr);
	}else{
		printf("inet_aton:string %s  error\n",addr1);
	}
	printf("----------------------\n");

	//测试inet_ntoa
	str = inet_ntoa(ip);	
	printf("inet_ntoa:string %s ip:0x%x \n",str,ip.s_addr);

	ip.s_addr = 192<<24|168<<16|1<<8|1; //不做字节序转换
	str = inet_ntoa(ip);	
	printf("inet_ntoa:string %s ip:0x%x \n",str,ip.s_addr);
	printf("----------------------\n");


	/*测试inet_ntoa的不可重入性
	 */
	ip.s_addr = 192<<24|168<<16|1<<8|1;
	str = inet_ntoa(ip);
	ip.s_addr = 255<<24|255<<16|255<<8|255;
	str2 = inet_ntoa(ip);	//原先的str指向的内存被覆盖掉
	printf("inet_ntoa:ip:0x%x string1 %s,pre is:%s \n",ip.s_addr,str2, str);
	printf("inet_ntoa:ip:0x%x string1 %s\n",ip.s_addr,str);
	printf("----------------------\n");
	
	
	return 0;
}



