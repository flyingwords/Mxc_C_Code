#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include"cJSON/cJSON.h"  

/*
cJSON_CreateObject		//创建一个json对象-- {对象}
cJSON_AddStringToObject	//向json对象中添加一个元素，元素的值是字符串-- {"type":""}
cJSON_AddNumberToObject	//向json对象中添加一个元素，元素的值是整形-- {"type":int}
cJSON_Delete			//释放内存
cJSON_PrintUnformatted(root)  cJSON_Print(root) //将json对象转换成字符串，然后将字符串打印，第二个是含有换行符等格式的			
*/


/*
创建如下cjson结构:
	{
		"name":	"fengxin",
		"passwd":	"123",
		"num":	1
	}
*/

int main()  
{  
    cJSON * usr = NULL;  
    cJSON *arry = NULL;  

    usr=cJSON_CreateObject();   //创建根数据对象  
    cJSON_AddStringToObject(usr,"name","fengxin");  //加入键值，加字符串  
    cJSON_AddStringToObject(usr,"passwd","123");  
    cJSON_AddNumberToObject(usr,"num",1);  //加整数  
      
    char *out = cJSON_Print(usr);   //将json形式打印成正常字符串形式  
    printf("%s\n",out);  
     
    // 释放内存    
    cJSON_Delete(usr);    
    free(out);          
}

