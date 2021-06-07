#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
解析字符串：{ \"list\":[{\"name\":\"xiao hong\",\"age\":10},{\"name\":\"hua hua\",\"age\":11}]} ，即如下cjson结构：
{
	"list":	[{
			"name":	"xiao hong",
			"age":	10
		}, {
			"name":	"hua hua",
			"age":	11
		}]
}


注意下面示例中函数cJSON_PrintUnformatted的使用
*/

int main(int argc, char **argv)  
{  
	char *s = "{\"list\":[{\"name\":\"xiao hong\",\"age\":10},{\"name\":\"hua hua\",\"age\":11}]}";  
	char *print_str = NULL;
	
	cJSON *root = cJSON_Parse(s);  
	if(!root) {  
	    printf("get root faild !\n");  
	    return -1;  
	}  else{
		print_str = cJSON_Print(root);  
		if(print_str){	
		   printf(" %s \n",print_str);	
			free(print_str);  
		}  
	}
	
	cJSON *js_list = cJSON_GetObjectItem(root, "list");  
	if(!js_list){  
	    printf("no list!\n");  
	    return -1;  
	}  
	int array_size = cJSON_GetArraySize(js_list);  
	printf("array size is %d\n",array_size);  
	int i = 0;  
	cJSON *item,*it, *js_name, *js_age;  
	char *p  = NULL;  
	for(i=0; i< array_size; i++) {  
	    item = cJSON_GetArrayItem(js_list, i);  
	    if(!item) {  
	        //TODO...  
	    }  
	    p = cJSON_PrintUnformatted(item);  
	    it = cJSON_Parse(p);  
	    if(!it)  
	        continue ;  
	    js_name = cJSON_GetObjectItem(it, "name");  
	    printf("name is %s\n",js_name->valuestring);  
	    js_age = cJSON_GetObjectItem(it, "age");  
	    printf("age is %d\n",js_age->valueint);  
	  
	}  
	  
	cJSON_Delete(root);  
	return 0;  
} 
