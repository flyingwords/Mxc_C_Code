#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
创建如下json结构：
	{"body":[{"name":"fengxin","status":100}]}  

元素值是一个json数组，数组里面又含有两个json对象
*/

int create_js(void)  
{  
    cJSON *root, *js_body, *js_list;  
    root = cJSON_CreateObject();  
    cJSON_AddItemToObject(root,"body", js_body = cJSON_CreateArray());  
    cJSON_AddItemToArray(js_body, js_list = cJSON_CreateObject());  
    cJSON_AddStringToObject(js_list,"name","fengxin");  
    cJSON_AddNumberToObject(js_list,"status",100);  
  
    {  
        char *s = cJSON_Print(root);  
        //char *s = cJSON_PrintUnformatted(root);  
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
