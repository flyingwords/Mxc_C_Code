#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "util_queue.h"

unsigned int queue_create(data_queue_s * queue, unsigned char max_socket, unsigned char limit_data)
{
	queue->maxdata = max_socket;
	queue->end = queue->buf[0] + queue->maxdata * QUEUE_BUF_LENGTH;
	memset(queue->buf, 0, sizeof(queue->buf));
	queue->in = queue->buf[0];
	queue->out = queue->buf[0];
	queue->limit_data = limit_data;

	return QUEUE_OK;
}

unsigned int queue_clear(data_queue_s *queue)
{
        memset(queue->buf, 0, sizeof(queue->buf));
        queue->in = queue->buf[0];
        queue->out = queue->buf[0];
        queue->end = queue->buf[0] + queue->maxdata * QUEUE_BUF_LENGTH;
        queue->limit_data = QUEUE_LENGTH - 1; 
}

void queue_flush(data_queue_s *queue)
{
	queue->out = queue->buf[0];
	queue->in = queue->buf[0];
	queue->limit_data = 0;
}

unsigned int queue_read(data_queue_s *queue, QUEUE_DATA_TYPE ret)
{
	unsigned int return_value;
	return_value = NOT_OK;

	if (queue->in != queue->out)
	{
		memcpy(ret, queue->out, QUEUE_BUF_LENGTH);

		return_value = queue->maxdata - (queue->end - queue->out)/QUEUE_BUF_LENGTH; 

		queue->out+=QUEUE_BUF_LENGTH;

		if (queue->out >= queue->end) //循环读队列
		{
			queue->out = queue->buf[0];
		}
	}
	else
	{
		return_value = QUEUE_EMPTY;
	}
	return return_value;
}

unsigned int queue_length(data_queue_s *queue)
{
	unsigned char * p_in = queue->in;	
	unsigned char * p_out = queue->out;
	int i = 0;
	
	if (p_in != p_out) 
	{
		while(p_out != p_in)
		{
			i ++;
			p_out+=QUEUE_BUF_LENGTH;
			if (p_out > queue->end)
			{
				p_out = queue->buf[0];
			}	
		}
		return i;
	}	
	else
	{
		return 0;
	}
}

unsigned int queue_write(data_queue_s *queue, QUEUE_DATA_TYPE data, unsigned short length , int fd, struct sockaddr_in socket_addr)
{

	unsigned int tmp_length = 0;
	unsigned int err = NOT_OK;

	if (data == NULL)
	{
		printf("Data Null!\n");
		return err;
	}
	tmp_length = queue_length(queue);
	if (tmp_length >= queue->limit_data) //牺牲一个队列元素用来判断队列full
	{
	    queue_clear(queue);
	    err = QUEUE_FULL;
	    printf("Data Full!\n");
	    return err;
	}	

	memset(queue->in, 0, QUEUE_BUF_LENGTH);   //Clear 
	memcpy(queue->in, data, length);
	queue->data_length[queue->maxdata - (queue->end - queue->in)/QUEUE_BUF_LENGTH] = length;
	queue->net_fd[queue->maxdata - (queue->end - queue->in)/QUEUE_BUF_LENGTH] = fd;
	queue->net_sockaddr[queue->maxdata - (queue->end - queue->in)/QUEUE_BUF_LENGTH] = socket_addr;
	
	queue->in+=QUEUE_BUF_LENGTH;

	if (queue->in >= queue->end) //循环写队列
	{
		queue->in = queue->buf[0];
	}

	err = QUEUE_OK;
	return err;	
}
