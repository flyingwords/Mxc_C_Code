#ifndef __UTIL_QUEUE_H__
#define __UTIL_QUEUE_H__

#include <netinet/in.h>

#ifndef NOT_OK
#define NOT_OK              0xffffffff                         /* 参数错误     */
#endif

#define QUEUE_FULL          (0xFFFF)                           /* 队列满    */
#define QUEUE_EMPTY         (0xFFFFFFFF)                       /* 无数据    */
#define QUEUE_OK            (0xFF)                             /* 操作成功     */

#define Q_WRITE_MODE        1                           	   /* 操作成功     */
#define Q_WRITE_FRONT_MODE  2

#ifndef QUEUE_DATA_TYPE
#define QUEUE_DATA_TYPE     unsigned char *
#endif

#define QUEUE_LENGTH   		(16)
#define QUEUE_BUF_LENGTH	(512)

typedef struct {
	unsigned char     			*out;                   /* 指向数据输出位置         */
	unsigned char     			*in;                    /* 指向数据输入位置         */
	unsigned char     			*end;                   /* 指向Buf的结束位置        */
	unsigned short              limit_data;             /* 队列中允许数据个数           */
	unsigned short              maxdata;                /* 队列中最大允许存储的数据个数 */

	unsigned char               (* read_empty)();        /* 读空处理函数             */
	unsigned char               (* write_full)();        /* 写满处理函数             */
	
	unsigned char     			buf[QUEUE_LENGTH][QUEUE_BUF_LENGTH];       /* 存储数据的空间 */
	unsigned char   *p_buf[QUEUE_LENGTH];
	unsigned short 				data_length[QUEUE_LENGTH]; 				   /* length   */

	unsigned short				net_fd[QUEUE_LENGTH];
	struct sockaddr_in	net_sockaddr[QUEUE_LENGTH];
	
}data_queue_s;

/* 创建静态循环队列 */
unsigned int queue_create(data_queue_s * queue, unsigned char max_socket, unsigned char limit_data);

unsigned int queue_read(data_queue_s *queue, QUEUE_DATA_TYPE ret);

unsigned int queue_write(data_queue_s *queue, QUEUE_DATA_TYPE data, unsigned short length, int fd, struct sockaddr_in socket_addr);

#endif


