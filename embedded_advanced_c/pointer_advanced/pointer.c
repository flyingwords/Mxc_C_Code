#include <stdio.h>

int main(void)
{
//分析一重指针
#if 0
	int a;
	int *p = NULL;		//从结合性上分析，*p表示这是一个指针，int表示这个指针指向一个int类型的变量
	p = &a;     //指针指向int类型变量a的地址
#endif 

#if 0
	int a[5] = {0,1,2,3,4};	
	int *p =NULL;		
	//指针指向int类型变量的地址，因为a表示数组首元素a[0]的地址，因此可以直接使用a赋值给p，等同于p=&a[0]
	p = a;  
	printf("p = %p *p = %d\n", p, *p); //*p表示从p指向的内存空间读取数据，即读取变量a[0]的值
	//p+1时表示偏移一个int类型变量的内存空间的距离，赋值之后p指向变量a[1]的地址
	p = p+1;
	printf("p = %p *p = %d\n", p, *p);//偏移之后p的值增加了4个字节,*p表示读取变量a[1]的值
	*p = 100; //*p在=左边表示向p指向的内存空间写入数据，即向a[1]的内存空间写入数据
	printf("a[1] = %d *p = %d\n", a[1], *p);
#endif

//分析数组指针
#if 0
	int a[5];
	int (*p)[5] = NULL; //从结合性上分析*p表示这是一个指针，int[5]表示表示这个指针指向一个包含5个int型变量的数组，这是一个数组指针
	p = &a;	    //指针指向一个int[5]类型的数组，因此要取a的地址（表示整个数组的地址）赋值给p
#endif 

#if 0
	int a[2][5] = {{0,1,2,3,4},{5,6,7,8,9}};//二重数组
	int (*p)[5] = NULL; 
	//指针指向int[5]类型的数组，因为a表示数组a[0]的地址，因此直接将a赋值给p，等同于p=&a[0];
	p = a;
	printf("p = %p (*p)[0] = %d\n", p, (*p)[0]); //(*p)表示从指向的地址中取出数组a[0],(*p)[0]则表示取出数组中第一个元素即a[0][0]
	//p+1时表示偏移一个int[5]类型的数组的内存空间，赋值之后p指向数组a[1]的地址
	p = p+1;
	printf("p = %p (*p)[0] = %d\n", p, (*p)[0]); //偏移之后p的值增加了20个字节, (*p)[0]表示取出变量a[1][0]的值，即5
	(*p)[2] = 100; //(*p)[2]表示向数组a[1]的第三个元素的内存空间写入数据
	printf("a[1][2] = %d (*p)[2] = %d\n", a[1][2], (*p)[2]);
#endif 


//分析二重指针
#if 0
	char *a = NULL;
	char **p =NULL;    //从结合性上分析，*p表示这是一个指针，p指针所指向的变量为char*类型的指针变量
	p = &a;		//指针指向char*类型的指针变量的地址
#endif

#if 0
	char *a[5] = {"aa","bb","cc","dd","ee"};//从结合性上分析，a先与[]结合，因此a是一个有5个元素的数组，char *表示a数组的成员都是char*类型的指针变量
	char **p = NULL;	
	p = a;     //因为a表示指针变量a[0]的地址，因此可以直接将a赋值给p
	printf("p = %p *p = %s\n", p, *p); //*p表示取出指针p所指向的指针变量p[0]的值，而p[0]的值是一个字符串常亮的地址
	//p+1时表示偏移一个char*类型的指针变量的内存空间的距离，因此赋值之后p指向指针变量a[1]
	p = p+1;
	printf("p = %p *p = %s\n", p, *p); //偏移之后p的值增加了8个字节，说明一个指针变量占用了八个字节的内存大小(当然这跟系统位数有关)
	p[1] = "hello"; //p[1]等同于*(p+1)，这里是向数组的第三个元素a[2]的内存空间写入字符串常量的地址
	printf("a[2] = %s p[1] = %s\n", a[2], p[1]);
#endif 


//分析二重数组指针
#if 0
	char *a[5] = {NULL};
	char *(*p)[5] = NULL; //从结合性上分析，(*p)表示这是一个指针，char*[5]表示指针p指向一个包含5个char*类型指针变量的指针数组
	p = &a; //指向char*[5]类型的指针数组的地址
#endif

#if 1
	char *a[2][5] = {{"aa","bb","cc","dd","ee"},{"ff","gg","hh","ii","jj"}};
	char *(*p)[5] = NULL; 
	p = a; //指针指向char*[5]类型的指针数组，因为a表示char*[5]数组a[0]的地址，因此直接将a赋值给p，等同于p=&a[0];
	printf("p = %p (*p)[0] = %s\n", p, (*p)[0]); //(*p)表示从指向的地址中取出数组a[0],(*p)[0]则表示取出数组中第一个元素即a[0][0]
	p = p+1;
	printf("p = %p (*p)[0] = %s\n", p, (*p)[0]); //偏移之后p的值增加了40个字节, (*p)[0]表示取出变量a[1][0]的值，即"ff"
	(*p)[2] = "hello"; //(*p)[2]表示向数组a[1]的第三个元素的内存空间写入数据
	printf("a[1][2] = %s (*p)[2] = %s\n", a[1][2], (*p)[2]);
#endif
	return 0;
}




