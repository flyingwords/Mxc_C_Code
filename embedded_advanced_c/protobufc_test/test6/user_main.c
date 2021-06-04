#include <stdio.h>
#include "user.pb-c.h"
#include <stdlib.h>
#include <string.h>
#define MAGIC 0xfb709394
#define VERSION 0x010000

/*
程序功能描述：处理repeated类型嵌套message结构, 子message结构内部使用repeated
*/
static size_t __do_pack(unsigned char *buffer)
{
        //User user = USER__INIT;	
        User user;
		int i;
		user__init(&user);

		user.version   = 2;
        user.name   = "zhangsan";
        user.phone  = "010-1234-5678";
        user.email  = "zhangsan@123.com";
        user.stat   = USER__STATUS__IDLE;		

		user.n_userjob = 3;	//设定数组元素个数
		user.userjob = malloc(sizeof(Job *) * user.n_userjob); //申请动态内存，userjob是一个Job **类型指针，指向Job *类型的指针数组
		
		for (i=0; i< user.n_userjob; i++) {
			user.userjob[i] = malloc(sizeof(Job));
			job__init(user.userjob[i]); //message结构初始化		

			user.userjob[i]->n_income = 2;
			user.userjob[i]->income = malloc(sizeof(unsigned int) * user.userjob[i]->n_income);
			user.userjob[i]->income[0] = 10000;
			user.userjob[i]->income[1] = 20000;

			user.userjob[i]->n_partner = 2;
			user.userjob[i]->partner = malloc(sizeof(char *) * user.userjob[i]->n_partner);
			user.userjob[i]->partner[0] = "alice";
			user.userjob[i]->partner[1] = "Bob";
		}

		size_t packed_size = user__get_packed_size(&user);
		
		printf("user__get_packed_size: %zd\n", packed_size);

		size_t ret = user__pack(&user, buffer);
		
		for (i=0; i< user.n_userjob; i++) { //从里到外释放
			free(user.userjob[i]->income);		
			free(user.userjob[i]->partner);
			free(user.userjob[i]);
		}
		
		free(user.userjob); //释放
		
        return ret;
}


static int __do_unpack(const unsigned char *buffer, size_t len)
{
        User *pusr = user__unpack(NULL, len, buffer);
		int i;
        if (!pusr) {
                printf("user__unpack failed\n");
                return 1;
        }
		assert(pusr->magic == MAGIC);
        printf("Unpack:%d %s %s %s %d\n", pusr->version, pusr->name, pusr->phone, pusr->email, pusr->stat);

		for (i=0; i<pusr->n_userjob; i++){
			printf("Unpack:%d %s\n", pusr->userjob[i]->income[0], pusr->userjob[i]->partner[0]); //访问子message结构
			printf("Unpack:%d %s\n", pusr->userjob[i]->income[1], pusr->userjob[i]->partner[1]); 
		}
		
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
