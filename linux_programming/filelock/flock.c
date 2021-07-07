/*
程序功能描述：测试flock调用的使用
通过flock给文件加锁，可以避免文件被多个进程读写造成，也可以用来做进程同步
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h> 
#include <unistd.h>
 
int main(int argc, char *argv[])
{
        int fd = open(argv[1], O_RDONLY);
        if (-1 == fd)
        {
                perror("open");
                exit(1);
        }
 
        printf("%d try to get lock\n", getpid());        
        //if (-1 == flock(fd, LOCK_EX))	//独占性加锁
        if (-1 == flock(fd, LOCK_SH))	//进程可以共享加锁
        //if (-1 == flock(fd, LOCK_EX|LOCK_NB)) //抢不到锁则直接返回不阻塞
        {
                perror("flock");
                close(fd);
                exit(1);
        }
 
        printf("%d locked now, enter any key to continue ...\n", getpid());
        getchar();
 
        printf("%d prepare to release lock\n", getpid());
        // 释放锁
        if (-1 == flock(fd, LOCK_UN))
        {
                perror("fulock");
                close(fd);
                exit(1);
        }
 
        printf("lock was released now\n");
        printf("process %d exited now\n", getpid());
        close(fd);
        return 0;
}

