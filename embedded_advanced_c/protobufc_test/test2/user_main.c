#include <stdio.h>
#include "user.pb-c.h"
#include <stdlib.h>
#include <string.h>
#define MAGIC 0xfb709394
#define VERSION 0x010000

/*
程序功能描述：处理repeated uint32类型
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

		user.n_worktime = 2;	//设置数组元素个数
		user.worktime = malloc(sizeof(unsigned int) * user.n_worktime);	//给数组分配动态内存(worktime类型 : uint32 *, 元素类型：uint32)
		user.worktime[0] = 4;
		user.worktime[1] = 8;
		
		size_t packed_size = user__get_packed_size(&user);
		
		printf("user__get_packed_size: %zd\n", packed_size);

		size_t ret = user__pack(&user, buffer);
		free(user.worktime);	//序列化之后释放
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
		printf("Unpack:%d %d\n", pusr->worktime[0], pusr->worktime[1]); //访问数组
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
