#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
cJSON_Parse				//将字符串转换成json对象

cJSON_GetObjectItem		//从json对象中获取一个元素
*/

/*
解析cjson字符串 {\"list\":{\"name\":\"xiao hong\",\"age\":10},\"other\":{\"name\":\"hua hua\"}}

cjson对象结构为：
{
	"list":	{
		"name":	"xiao hong",
		"age":	10
	},
	"other":	{
		"name":	"hua hua"
	}
}
*/

int main(void)
{
	char *s = "{\"list\":{\"name\":\"xiao hong\",\"age\":10},\"other\":{\"name\":\"hua hua\"}}";  
	char *print_str = NULL;
	
	cJSON *root = cJSON_Parse(s);  
	if(!root) {  
	    printf("get root faild !\n");  
	    return -1;  
	}  
	else{
		print_str = cJSON_Print(root);  
		if(print_str){	
		   printf(" %s \n",print_str);	
			free(print_str);  
		}  
	}
	  
	cJSON *js_list = cJSON_GetObjectItem(root, "list");  
	if(!js_list) {  
	    printf("no list!\n");  
		cJSON_Delete(root); 
	    return -1;  
	}  
	printf("list type is %d\n",js_list->type);  
	  
	cJSON *name = cJSON_GetObjectItem(js_list, "name");  
	if(!name) {  
	    printf("No name !\n");  
		cJSON_Delete(root); 
	    return -1;  
	}  
	printf("name type is %d\n",name->type);  
	printf("name is %s\n",name->valuestring);  
	  
	cJSON *age = cJSON_GetObjectItem(js_list, "age");  
	if(!age) {  
	    printf("no age!\n");
		cJSON_Delete(root); 
	    return -1;  
	}  
	printf("age type is %d\n", age->type);  
	printf("age is %d\n",age->valueint);  
	  
	cJSON *js_other = cJSON_GetObjectItem(root, "other");  
	if(!js_other) {  
	    printf("no list!\n");  
		cJSON_Delete(root); 
	    return -1;  
	}  
	printf("list type is %d\n",js_other->type);  
	  
	cJSON *js_name = cJSON_GetObjectItem(js_other, "name");  
	if(!js_name) {  
	    printf("No name !\n");  
		cJSON_Delete(root); 
	    return -1;  
	}  
	printf("name type is %d\n",js_name->type);  
	printf("name is %s\n",js_name->valuestring);  
	  
	cJSON_Delete(root);  
    return 0;
}


