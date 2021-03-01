#include<stdio.h>
#include"operation.h"    
/*
程序功能描述：分析动态库、静态库的制作和使用
*/

/*
使用gcc函数库需要用到的编译链接选项:
-I
说明：对于C语言来说，头文件几乎总是位于/usr/include及其子目录中。-I用来包含子目录或者非标准位置的头文件路径。
-L
说明：如果库文件没有存放在标准位置，那么需要通过 -L来为编译器增加库文件的搜索路径。
-l
说明：标准系统库文件一般存储于/lib和/usr/lib目录中，C语言编译器（准确的说是链接程序）需要知道要链接哪些库文件，
仅仅把库文件放在标准目录下是不够的，因为默认情况下它只链接C语言标准库。
可以通过给出完整的库文件的路径或者用 -l+库名 告诉编译器要链接的库文件，如果存在动态库，那么-l会优先使用动态库。
*/


/*
动态库的制作和使用
1、制作动态库
gcc -c operation.c -o operation.o
gcc -o liboperation.so operation.o -shared

说明：
-c选项表示只编译文件但不链接
-shared表示生成共享库，即动态链接库
给库命名时采用 lib+库名 的方式，不能随便起名字

2、编译链接主程序
gcc main.c -o -I. main_dynamic_test

编译报错：/tmp/cchlkfgB.o: In function `main':
main.c:(.text+0x28): undefined reference to `fun_mul'
collect2: error: ld returned 1 exit status
原因：operation.so 不是标准库，C语言编译器默认只会使用标准库，因此需要使用-l指定库名

gcc main.c -o  -loperation -I. main_dynamic_test

链接报错：/usr/bin/ld: cannot find -loperation
collect2: error: ld returned 1 exit status
原因：operation.so 不是标准库，C语言编译器默认只会去标准目录搜索库，因此需要使用-L指定库路径

gcc main.c -o  -loperation -I. -L. main_dynamic_test 

3、指定运行时的动态库路径
直接运行报错：
./main_dynamic_test: error while loading shared libraries: liboperation.so: 
cannot open shared object file: No such file or directory

原因：-L只是指定编译链接时动态库的路径，运行时系统只会去标准目录查找库路径，


解决方法一：
将liboperation.so放到标准目录下就可以了，这个标准目录一般是/usr/lib目录。
cp liboperation.so /usr/lib 即可。

解决方法二：使用环境变量LD_LIBRARY_PATH。操作系统在加载固定目录/usr/lib之前，
会先去LD_LIBRARY_PATH这个环境变量所指定的目录下去寻找，如果找到就不用去/usr/lib下面找了，如果没找到再去/usr/lib下面找。
所以解决方案就是将liboperation.so所在的目录导出到环境变量LD_LIBRARY_PATH中即可。
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/mxc/winshare/my_github/embedded_advanced_c/dynamic_static_lib_test

解决方法三：
在ld.so.conf中保存非标准库的路径并且执行ldconfig。
举例如下：
在ubuntu1604下，进入/etc/ld.so.conf.d目录创建一个user_lib.conf文件

vi打开写入动态库路径如下
/home/mxc/winshare/my_github/embedded_advanced_c/dynamic_static_lib_test

最后执行以下ldconfig将动态库刷新到/etc/ld.so.cache 即可
*/


/*
静态库的制作及使用
1、制作静态库
gcc -c operation.c -o operation.o
ar -rc liboperation.a operation.o

说明：
-c表示只编译不链接，生成目标文件
ar工具用来制作归档文件，生成静态链接库
给库命名时采用 lib+库名 的方式，不能随便起名字
 
2、编译链接主程序
gcc main.c -loperation -L. -I. -o main_static_test

注意：
当主程序使用静态库时，并不会将整个静态库编译进主程序，只会编译链接调用的函数。
但使用-l指定库之后，如果目录下存在同名动态库的话，会优先链接动态库，这时候就需要指定运行时的动态库路径，
具体查看下面的动态库制作和使用
*/

int main()
{
    int a,b,c;
    a = 100;
    b = 20;
    c = 0;
    c = fun_mul(a,b);
    printf("c = %d\n",c);
    return 0;
}

