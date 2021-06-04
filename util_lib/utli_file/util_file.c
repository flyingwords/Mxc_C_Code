#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

/*
函数名：Update_Conf
描述：
	根据关键字更新配置行
参数：
	path：文件
	keyword：关键字
	item：新的配置行
返回值：
	成功	0 失败-1
*/
#define FILE_BUFF_SIZE 2048	//文件的大小不能超过2KB
int Update_Conf(char *path, char *keyword, char *item)
{
	FILE *fp = NULL;
	char *line = NULL;
	char dst_buff[FILE_BUFF_SIZE] = {0};
	char tmp_line[96] = {0};
	char shellcmd[96] = {0};
	size_t line_size = 0;
	int read = 0;

	fp = fopen(path, "r");
	if (fp == NULL) 
	{
		return -1;
	}
	
	// 每次读一行 --- 匹配待修改项 --- 修改 --- 写入新buff  --- 重新写入文件
	while (read = getline(&line, &line_size, fp) != -1) 
	{
		if (line[0] == '\0') 
		{
			continue;
		}
		
		// 匹配修改项目
		if (strstr(line, keyword) != NULL) 
		{
			memcpy(tmp_line, item, strlen(item));
			strcat(tmp_line, "\n");
		} 
		else 
		{
			memcpy(tmp_line, line, strlen(line));
		}

		// 写入到新buff
		strcat(dst_buff, tmp_line);

		memset(tmp_line, 0, sizeof(tmp_line));
	}
	free(line);
	fclose(fp);
	fp = NULL;

	// 删除源文件
	sprintf(shellcmd, "rm %s", path);
	system(shellcmd);

	// 重新写入文件
	fp = fopen(path, "w+");
	if (fp == NULL) {
		return -1;
	}

	fprintf(fp, "%s", dst_buff);
	fclose(fp);
	fp = NULL;
	
	return 0;
}


unsigned long util_Get_File_Size(const char *filepath)
{
        int filesize = 0; 
        struct stat statbuff;
     
        if (stat(filepath, &statbuff) < 0) { 
                return filesize;
        } else {
                filesize = statbuff.st_size;
        }    

        return filesize;
}


