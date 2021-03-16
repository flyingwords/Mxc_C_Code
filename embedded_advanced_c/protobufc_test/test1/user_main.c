#include <stdio.h>
#include "user.pb-c.h"
#include <stdlib.h>
#include <string.h>
#define MAGIC 0xfb709394
#define VERSION 0x010000

/*
user__init：	xxx___init，xxx为定义的message结构的名称，使用该结构定义变量之后，需要使用该函数初始化，两种方式：
	1、  User user = USER__INIT;	
	2、 User user;
		user__init(&user);

user__get_packed_size：xxx__get_packed_size	返回message结构序列化之后的大小
user__pack：xxx__pack 用来将message结构序列化，返回值为序列化之后的大小
user__unpack：xxx__unpack	用来将message结构反序列化，返回一个指向message结构 的动态内存的指针
user__free_unpacked：xxx___free_unpacked,用来释放 user__unpack返回值的message结构的动态内存
*/

/*
程序功能描述：protobuf-c 的基本使用
*/
static size_t __do_pack(unsigned char *buffer)
{
        //User user = USER__INIT;	
        User user;
		user__init(&user);

		user.version   = 2;
        //user.name   = "zhangsan";
        user.phone  = "010-1234-5678";
        user.email  = "zhangsan@123.com";
        user.stat   = USER__STATUS__IDLE;		

		
		size_t packed_size = user__get_packed_size(&user);
		printf("user__get_packed_size: %zd\n", packed_size);
        return user__pack(&user, buffer);
}


static int __do_unpack(const unsigned char *buffer, size_t len)
{
        User *pusr = user__unpack(NULL, len, buffer);
        if (!pusr) {
                printf("user__unpack failed\n");
                return 1;
        }
		assert(pusr->magic == MAGIC);
        printf("Unpack:%d %s %s %s %d\n", pusr->version, pusr->name, pusr->phone, pusr->email, pusr->stat);
		
        user__free_unpacked(pusr, NULL);
        return 0;
}


int main(int argc, char *argv[])
{
        unsigned char buffer[1024] = {0}; 
        size_t size = __do_pack(buffer);
        printf("Packet size: %zd\n", size);
        __do_unpack(buffer, size);
 
        exit(0);
}
