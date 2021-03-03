/*
程序功能描述：演示如何使用这套静态循环队列函数
*/

#include "util_queue.h"
#include <stdio.h>
#include <string.h>

volatile data_queue_s queue = {0};
struct sockaddr_in null_sockaddr= {0};

int main()
{
	unsigned char msg_w[QUEUE_BUF_LENGTH] = "123456789";
	unsigned char msg_r[QUEUE_BUF_LENGTH] = "";
	int i=0, j=0, ret;
	
	queue_create(&queue, 16, 15);      
	//while(1){
	for (j=0; j<20; j++){
		ret = queue_write(&queue, msg_w, strlen(msg_w), 0, null_sockaddr);
		if (ret == QUEUE_FULL){
			printf("queue full\n"); //队列写满会清空队列
			break;
		}else{
			printf("write queue %d times, msg_w = %s\n", ++i, msg_w);
		}
	}

	i = 0;
	while(1){
		memset(msg_r, 0, sizeof(msg_r));
		ret = queue_read(&queue, msg_r);
		if (ret != QUEUE_EMPTY){
			printf("read queue %d times, msg_r = %s\n", ++i, msg_r);	
		}else{
			printf("queue empty\n");
			break;
		}
	}

	return 0;
}
