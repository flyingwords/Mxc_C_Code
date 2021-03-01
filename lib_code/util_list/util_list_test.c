#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "util_list.h"

/*
程序功能描述：这个例子演示 如何用链表进行音视频发送处理
*/

#define SINK_TYPE_MAGIC        	0x13579B00
#define SINK_TYPE_RTPUDP  		(SINK_TYPE_MAGIC+1)
#define SINK_TYPE_RTMPCLIENT  	(SINK_TYPE_MAGIC+4)

//视频链表结构体
typedef struct {
    pthread_mutex_t v_mutex;
    struct list_head vsink_list;
}STREAM;

//视频链表节点结构体
typedef struct {
    struct list_head list;
    pthread_mutex_t * mutex;
    int type;
}STREAM_SINK;

//定义视频链表
STREAM stream; 


//加链表锁的节点增加和删除，避免多线程同时操作链表导致出错
void list_add_tail_mutex(struct list_head *new, struct list_head *head, pthread_mutex_t * mutex )
{
    //printf("Enter\n");
    pthread_mutex_lock(mutex);
    list_add_tail(new, head );
    pthread_mutex_unlock(mutex);
    //printf("Leave\n");
}

void list_del_mutex(struct list_head *p, pthread_mutex_t * mutex)
{
    //printf("Enter\n");
    pthread_mutex_lock(mutex);
    list_del( p );
    pthread_mutex_unlock(mutex);
    //printf("Leave\n");
}


//创建节点并添加到链表
void *create_sink(int type){
    STREAM_SINK * sink;
    sink = calloc(1,sizeof(STREAM_SINK));
	memset(sink, 0, sizeof(sink));
	sink->type = type;
	sink->mutex = &stream.v_mutex; //指向链表锁
	list_add_tail_mutex(&sink->list, &stream.vsink_list, sink->mutex);
	return sink;
}

//从链表移除节点并销毁
int destroy_sink(void * sink_handle){
	STREAM_SINK * sink = ( STREAM_SINK*) sink_handle;
	if (sink == NULL){
		printf("sink NULL\n");
		return -1;
	}
    list_del_mutex( &sink->list, sink->mutex );
	memset(sink, 0, sizeof(sink));
	free(sink);
	return 0;
}

//节点处理函数
int send_h264_frame(void){
	STREAM_SINK * sink;
    struct list_head * sinklist = &stream.vsink_list; //获取链表
    struct list_head * listptr;

    pthread_mutex_lock( &stream.v_mutex ); //操作链表前需要先加锁

	list_for_each( listptr, sinklist ){	   //遍历链表
		sink = container_of( listptr, STREAM_SINK,list ); //使用container_of宏，根据节点元素名获取节点结构体首地址
		switch(sink->type) {//节点处理
			case SINK_TYPE_RTPUDP:
				printf("SINK_TYPE_RTPUDP\n");
				break;
			case SINK_TYPE_RTMPCLIENT:
				printf("SINK_TYPE_RTMPCLIENT\n");
				break;
			default:
				break;
		}
	}
	
}



//保存节点地址，用于节点销毁
void *sink_handle = NULL;  
void *sink_handle2 = NULL;

int main()
{
	//初始化链表和锁
	INIT_LIST_HEAD( &stream.vsink_list );
	pthread_mutex_init(&stream.v_mutex, 0);
	
	//增加节点
	sink_handle = create_sink(SINK_TYPE_RTPUDP);
	sink_handle2 = create_sink(SINK_TYPE_RTMPCLIENT);
	
	//节点遍历处理函数
	send_h264_frame();

	//节点销毁
	destroy_sink(sink_handle);	
	destroy_sink(sink_handle2);
	
	return 0;
}


