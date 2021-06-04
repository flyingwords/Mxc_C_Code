#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util_process.h"

/*示例；FindPid
*/
#if 1
int main()
{
	int pid;
	pid = FindPid("ps");
	printf("pid = %d\n", pid);
	return 0;
}
#endif

