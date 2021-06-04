#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util_process.h"

/*示例；find_pid
*/
#if 0
int main()
{
	int pid;
	pid = find_pid("ps");
	printf("pid = %d\n", pid);
	return 0;
}
#endif

/*示例：readCmdResult
*/
#if 0
int main()
{
	int ret;

	char cmd[20] = "ps";
	char result_buf[256] = "";
	ret =readCmdResult(cmd, result_buf, 256);
	if (ret != -1){
		printf("result_buf = %s\n", result_buf);
	}
	return 0;
}
#endif
