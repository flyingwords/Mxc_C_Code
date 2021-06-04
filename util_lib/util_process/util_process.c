#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
函数名：FindPid
描述：
	查询进程的pid
参数：
	pidname：进程的名称
返回值：
	成功返回PID
	失败返回 -1
*/
#define PS_CMD                  "ps | grep \""
int find_pid(char pidname[])
{
        int i = 0;
        int ret = -1;
        char cmd[128] = PS_CMD;
        char buff[128] = {0};
        FILE *fp = NULL;

        strcat(cmd, pidname);
        strcat(cmd, "\"");


        fp = popen(cmd, "r");
        if (fp == NULL) {
                printf("fopen %s failed\n", cmd);
                return ret;
        }

        if (!fread(buff, sizeof(char), sizeof(buff), fp)) {
                printf("fread %s failed\n", cmd);		
				return ret;
        }


        pclose(fp);
        fp = NULL;

        /* 找第一个数字 */
        while (!((buff[i] >= '0') && (buff[i] <= '9'))) {
                i++;
        }

        /* 读到空格停止 */
        sscanf(buff, "%[^ ]", buff);
        ret = atoi(buff);

        printf("find pid: %s:%d\n", pidname, ret);
        return ret;
}

/*
函数名：itoa
描述：
	将整形转换为字符串函数（只能转换正的整形数）
参数：
	i：输入，整形数
	strbuf：输出，转换后的字符串
返回值：
	无
*/
void itoa(int i, char *strbuf)
{
	int power = 0;
	int j = 0;
	
	j = i;
	
	for (power=1; j>=10; j/=10) {
		power *= 10;
	}
	
	for (; power>0; power/=10) {
	   *strbuf++ = '0'+ i/power;
	   i %= power;
	}
	
	*strbuf = '\0';
}

/* 
 *      结束进程, level一般是9 
*/
#define KILL_PID_CMD            "kill -"
void kill_pid(char pid_name[], char level[])
{
        int retpid = 0; 
        char killpid[128] = {0}; 
        char cmd[128] = KILL_PID_CMD;
        int ret = 0; 
             
        strcat(cmd, level);
        strcat(cmd, " ");

        retpid = find_pid(pid_name);
        if (retpid == 0) { 
                printf( "not found %s pid\n", pid_name);
                return;
        }    

        itoa(retpid, killpid);
        strcat(cmd, killpid);
        printf("cmd:%s\n", cmd);
        ret = system(cmd);
        printf("kill pid: %d ret:%d\n", retpid, ret);
}

/*
函数名：readCmdResult
描述：
	读取命令的执行结果
参数：
	cmd: 命令
	result: 输出，执行命令返回结果
	size: result buffer的大小
返回值：
	返回结果的长度
	失败返回-1
*/
int readCmdResult(char *cmd, char *result, unsigned int size)
{
    FILE *fp = NULL;
    int ret=0;
    fp = popen(cmd, "r");
    if (fp == NULL) {
	printf("popen failed\n");
	return -1;
    } else {
	memset(result, 0, size);  
	ret = fread(result, sizeof(char), size, fp);
	if (ret == 0) { 
	    printf("fread %s failed\n", result);
	    return -1;
	}    
    }    
    pclose(fp);
    fp = NULL;
    return ret;
}

