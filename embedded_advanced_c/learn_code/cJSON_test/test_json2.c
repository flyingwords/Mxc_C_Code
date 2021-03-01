#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
cJSON_CreateArray();	//创建json对象数组-- [{ : } ,{ : }]
cJSON_CreateString		//创建一个包含指定 字符串值元素的 cjson对象
cJSON_CreateNumber		//创建一个包含指定 整形值 元素的 cjson对象
*/

/*
创建一个json数组:
	["Hello world",10] 
*/
int create_js(void)  
{  
	cJSON *root, *js_body;	
	root = cJSON_CreateArray();  
	cJSON_AddItemToArray(root, cJSON_CreateString("Hello world"));	
	cJSON_AddItemToArray(root, cJSON_CreateNumber(10));   
	{  
//		char *s = cJSON_Print(root);  
		char *s = cJSON_PrintUnformatted(root);  
		if(s){	
		   printf(" %s \n",s);	
			free(s);  
		}  
	}  
	if(root)  
	cJSON_Delete(root);  
  
	return 0; 
}  
  
int main(int argc, char **argv)  
{  
    create_js();  
    return 0;  
}
