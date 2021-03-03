#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
函数名：find_pid
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

/*示例*/
#if 0
int main()
{
	int pid;
	pid = find_pid("a.out");
	printf("pid = %d\n", pid);
	return 0;
}
#endif



