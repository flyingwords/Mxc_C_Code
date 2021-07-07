#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>


/*
程序功能描述：使用条件变量做线程同步,主线程从键盘读取字符串，子线程做统计
*/
#define READ_SIZE 50
char sharedbuffer[READ_SIZE] = "\0";
 
pthread_cond_t g_cond;
pthread_mutex_t g_mutex;

void*thread_func(void*arg) 
{

	pthread_mutex_lock(&g_mutex);
    pthread_cond_wait(&g_cond, &g_mutex); //pthread_cond_wait会释放锁并阻塞于条件变量
    pthread_mutex_unlock(&g_mutex);

	while(0 != strncmp(sharedbuffer, "end", 3))
	{
		printf("\nThe str:%s", sharedbuffer);
		printf("The len of str:%d\n", (int)strlen(sharedbuffer));	
		
		pthread_mutex_lock(&g_mutex);
	    pthread_cond_wait(&g_cond, &g_mutex); 
	    pthread_mutex_unlock(&g_mutex);
	}
	
	pthread_exit("thanks for the get the cpu time");
	
}

int main()    
{
	pthread_t pth_id;
	int ret;
	void *retval;

	pthread_cond_init(&g_cond, NULL);
	pthread_mutex_init(&g_mutex, NULL);
	
	ret = pthread_create(&pth_id, NULL, thread_func, NULL);
	if (0 != ret)
	{
		perror("pthread_create");
		exit(1);
	}
	
	/*
	测试：主线程从键盘读取字符串，子线程做统计
	测试结果：效果正常，主线程能及时处理用户输入，子线程也能及时统计。

	问题：这里有一个问题，主线程不会等子线程处理完就继续处理 用户输入
	解决思路：
		1、适当延时
		2、增加一个条件变量
	*/
	while(0 != strncmp(sharedbuffer, "end", 3))
	{
		printf("enter string to count(\"end\" to exit):");
		fgets(sharedbuffer, READ_SIZE, stdin);
		
		pthread_mutex_lock(&g_mutex);
	    pthread_cond_signal(&g_cond);
	    pthread_mutex_unlock(&g_mutex);

	}
	
	printf("waiting for join the thread\n");
	ret = pthread_join(pth_id, &retval); 
	if (0 == ret){
		printf("the retval of thread is:%s\n", (char *)retval);
	}
	else{
		perror("pthread_join");
		exit(1);
	}

	pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_mutex);
	return 0;
}


