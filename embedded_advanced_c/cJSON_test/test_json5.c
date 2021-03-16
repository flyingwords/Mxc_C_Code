
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
cJSON_GetArraySize		//获取json数组的长度
cJSON_GetArrayItem		//从json数组中获取一个对象
*/


/*
解析字符串;{\"list\":[\"name1\",\"name2\"]}, 即如下cjson结构：

{
	"list":	["name1", "name2"]
}

*/
int main(int argc, char **argv)  
{  
	char *s = "{\"list\":[\"name1\",\"name2\"]}";  
	char *print_str = NULL;
	cJSON *root = cJSON_Parse(s);  
	if(!root) {  
	    printf("get root faild !\n");  
	    return -1;  
	} else{
		print_str = cJSON_Print(root);  
		if(print_str){	
		   printf(" %s \n",print_str);	
			free(print_str);  
		}  
	}
	cJSON *js_list = cJSON_GetObjectItem(root, "list");  
	if(!js_list){  
	    printf("no list!\n"); 
		cJSON_Delete(root); 
	    return -1;  
	}  
	int array_size = cJSON_GetArraySize(js_list);  
	printf("array size is %d\n",array_size);  
	int i = 0;  
	cJSON *item;  
	for(i=0; i< array_size; i++) {  
	    item = cJSON_GetArrayItem(js_list, i);  
	    printf("item type is %d\n",item->type);  
	    printf("%s\n",item->valuestring);  
	}  
	  
    cJSON_Delete(root);  
	return 0;  
} 
