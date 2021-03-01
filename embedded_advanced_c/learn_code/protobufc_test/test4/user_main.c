#include <stdio.h>
#include "user.pb-c.h"
#include <stdlib.h>
#include <string.h>
#define MAGIC 0xfb709394
#define VERSION 0x010000

/*
程序功能描述：处理required 类型嵌套message结构
*/
static size_t __do_pack(unsigned char *buffer)
{
        //User user = USER__INIT;	
        User user;
		user__init(&user);

		user.version   = 2;
        user.name   = "zhangsan";
        user.phone  = "010-1234-5678";
        user.email  = "zhangsan@123.com";
        user.stat   = USER__STATUS__IDLE;		

		user.userjob = malloc(sizeof(Job)); //申请动态内存，userjob是一个Job *类型指针
		job__init(user.userjob); //message结构初始化
		user.userjob->income = 20000;
		user.userjob->partner = "Bob";

		size_t packed_size = user__get_packed_size(&user);
		
		printf("user__get_packed_size: %zd\n", packed_size);

		size_t ret = user__pack(&user, buffer);
		free(user.userjob); //释放
        return ret;
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
		printf("Unpack:%d %s\n", pusr->userjob->income, pusr->userjob->partner); //访问子message结构
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
