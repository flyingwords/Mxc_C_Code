/****************************************
* 作者：mxc
* 说明：整理一些系统调用的函数原型
*****************************************/

#define file_attr
int access(const char *pathname, int mode);
/*
功能描述：用来查询进程对文件的访问权限、查询文件是否存在等

参数：
pathname  表示文件的路径名
mode	  用来指定一些flags，常用的如下：
F_OK				测试文件是否存在
R_OK、W_OK、X_OK		测试程序执行者对目标文件是否可读可写可执行

返回值：
文件存在或者具有权限返回0，否则返回-1
*/

int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
/*
功能描述：
用来查询的文件的各种信息，三者的区别如下：
1、stat、lstat参数1是文件路径名，fstat参数1是文件描述符
2、当对象是软连接时，stat、fstat判断的对象时软连接指向的对象，lstat判断的对象是软连接本身

参数：
pathname	文件的路径名
fd			文件的描述符
buf			输出参数，用来保存文件的查询信息
struct stat {
               dev_t     st_dev;         //ID of device containing file 
               ino_t     st_ino;         //inode number 
               mode_t    st_mode;        // protection 
               nlink_t   st_nlink;       // number of hard links 
               uid_t     st_uid;         // user ID of owner 
               gid_t     st_gid;         // group ID of owner 
               dev_t     st_rdev;        // device ID (if special file) 
               off_t     st_size;        // total size, in bytes 
               blksize_t st_blksize;     // blocksize for filesystem I/O 
               blkcnt_t  st_blocks;      // number of 512B blocks allocated 
	struct timespec st_atim;  // time of last access 
	struct timespec st_mtim;  // time of last modification 
	struct timespec st_ctim;  // time of last status change 

#define st_atime st_atim.tv_sec 	 // Backward compatibility 
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
}

返回值：
成功返回0 失败返回-1

一些判断宏定义：
S_ISREG	用来判断文件是否为普通文件
S_ISDIR	用来判断文件是否为目录
S_ISLNK 用来判断文件是否为软连接


一些判断掩码：
S_IRUSR	属主是否具有读权限
S_IWUSR
S_IXUSR

S_IRGRP 用户组是否具有读权限
S_IWGRP
S_IXGRP

S_IROTH	其他用户是否具有读权限
S_IWOTH
S_IXOTH
*/


#define file_io

off_t lseek(int fd, off_t offset, int whence);
/*
描述：以whence基准，将文件位置偏移offset（指针偏移量）个字节的位置
参数：
fd：文件描述符
offset：偏移量，正数表示正向偏移，负数表示负向偏移
whence：设定从文件的哪里开始偏移,可能取值为：SEEK_CUR、SEEK_END、SEEK_SET等
SEEK_SET： 文件开头
SEEK_CUR： 当前位置
SEEK_END： 文件结尾
返回值：
返回结果偏移位置，以从文件开头开始的字节数为单位。 发生错误时，将返回值（off_t）-
1，并设置errno
*/

int open(const char *pathname, int flags, mode_t mode);
/*
描述：用于打开文件并获取文件描述符
参数：
pathname:文件的路径名

flags：以指定方式操作文件
O_CREAT 创建文件，文件存在则不创建，但不报错
O_RDWR：读写 
O_WRONLY：只写 
O_RDONLY：只读
O_TRUNC  清空文件
O_APPEND 续写文件
O_EXCL   如果文件存在则报错
O_SYNC   同步文件到存储设备
O_NONBLOCK  在读取不到数据或是写入缓冲区已满会马上return，而不会阻塞等待。

mode ：指定创建文件的权限， S_IRUSR 表示读 S_IWUSR 表示写，S_IXUSR表示执行，
创建的文件的权限为mode＆~umask，~mask不包括执行权限。
返回值：返回获取的文件描述符，失败返回-1并设置errno
*/

ssize_t read(int fd, void *buf, size_t count);
/*
描述：read用来将文件描述符fd中读取count个字符取到缓冲区buf中
参数：
fd：文件描述符
buf：用来存储读取字节的缓冲区
count：从文件中读取的字节总数
返回值：
返回读取的字节数，并且文件当前的位置会偏移返回的字节数大小。
如果读取的字节数小于指定的字节总数count，并不一定代表错误（可能到达文件尾等原因造
成）。

如果读取错误，则返回-1，并设置对应的errno.
*/

ssize_t write(int fd, const void *buf, size_t count);
/*
描述：write用来将缓冲区buf的count个字节写入到文件描述符fd指定的文件中。
如果使用O_APPEND打开文件，则在写入之前会先将文件偏移到文件的末尾。
参数：
fd：文件描述符
buf：用来写入文件的字符缓冲区
count：指定要写入到文件的字节总数
返回值：
返回写入的字节数，并且文件当前的位置会偏移实际写入的字节数目的大小。
如果写入的字节数小于指定的字节总数count，并不一定代表错误（可能是因为磁盘空间不够
造成）。

如果写入错误，则返回-1，并设置对应的errno。

注意：写入数据的时候，需要写入多少数据就指定多大的数目，如果指定的count大小超过数
组缓冲区的大小，

还是按照指定的大小输入数据，这样数组就会越界，写入的数据是不可知的。
*/

#define standrad_io

FILE * fdopen(int fildes,const char * mode);
/*
描述：fdopen取一个现存的文件描述符，并使一个标准的I / O流与该描述符相结合。
此函数常用于由创建管道和网络通信通道函数获得的描述符。因为这些特殊类型的文件不能用标准I/O fopen函数打开，
首先必须先调用设备专用函数以获得一个文件描述符，然后用fdopen使一个标准I/O流与该描述符相结合。

参数：
fildes：已经打开的文件描述符
mode：指定流的模式，注意以下几点：
1、流的模式("r"、"r+"、"w"、"w+"、"a"、"a+"之一)必须与文件描述符的模式兼容。 
2、fdopen将新的文件位置设置为属于fd的文件位置指示符，并清除错误和文件结束指示符。
3、模式"w"、"w+"不会导致文件被截断。 (例如，若该描述符原来是由open函数打开的，
该文件那时已经存在，则其O_TRUNC标志将决定是否截断该文件）。
4、当关闭由fdopen打开的流时，对应的文件描述符也会被关闭。

返回值：
转换成功时返回指向该流的文件指针。失败则返回NULL，并把错误代码存在errno中。
*/

int feof(FILE *stream);
/*
描述：判断文件流是不是到达文件结尾
参数：
stream：文件流指针
返回值：
如果到达文件尾，那么feof返回值为非零，否则返回值为0
*/

int ferror(FILE *stream);
/*
描述：判断文件流是否发生错误 
参数：
stream：文件流指针
返回值：有错误返回非零，否则返回0
*/

void clearerr(FILE *stream);
/*
描述：用来清除文件流的文件尾标识和错误标识
参数：文件流指针
返回值：无
*/
char *fgets(char *s, int size, FILE *stream);
/*
描述：从文件流中读取最多size-1个字符到s指定的buffer中。当发生下面三种情况时结束读取：
（1）读取到size-1个字符
（2）读取到换行符（保留换行符）
（3）读取到文件尾
	fgets会给读取的字符串添加'\0'。

参数：
s：指向用来保存读取字符串的buffer
size：指定要读取的字符数目，只会读取size-1
stream：文件流指针
返回值：
读取成功时返回指向s的指针；当发生错误、或者在没有读取到任何字符的情况下(直接读取到文件尾)返回NULL。
*/

char *gets(char *s);
/*
描述：从标准输入读取一行到s指定的buffer中，当发生以下情况时结束读取：
（1）当读取到换行符（丢弃换行符）
	gets会给读取的字符串添加'\0'。
参数：
s：指向用来保存读取字符串的buffer
返回值：
读取成功时返回指向s的指针；当发生错误或者没有读取到任何字符的情况下(直接读取到换行符)返回NULL。

注意：gets对读取的字符串的长度没有限制，有可能会导致缓冲区溢出，因此最好用fgets来替代gets
*/

int fseek(FILE *stream, long offset, int whence);
/*
描述：以whence基准，文件流指针偏移offset（指针偏移量）个字节的位置
参数：
stream：文件流指针
offset：偏移量，正数表示正向偏移，负数表示负向偏移
whence：设定从文件的哪里开始偏移,可能取值为：SEEK_CUR、SEEK_END、SEEK_SET
SEEK_SET： 文件开头
SEEK_CUR： 当前位置
SEEK_END： 文件结尾
返回值：
成功，返回0，失败返回非0值，并设置error的值
*/

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
/*
描述：getline用于读取一行字符直到换行符,包括换行符。它会生成一个包含一串从输入流读入的字符的字符串，
直到以下情况发生会导致生成的此字符串结束。1）到文件结束，2）遇到函数的定界符，3）输入达到最大限度。

参数：
lineptr：指向存放该行字符的指针，如果是NULL，则由系统帮助malloc，请在使用完成后free释放。
n：如果是由系统malloc的指针，请填0。
stream：文件描述符
返回值：返回读取的字节数，失败返回-1。
*/

FILE *fopen(const char *path, const char *mode);
/*
描述：打开名称为path指向的字符串的文件，并将流与其关联。
参数：
path：指向文件的路径
mode：
r rb 以只读方式打开文件，文件必须存在
w wb 只写方式打开文件，并把文件截短为零，文件不存在则创建
a ab 以写方式打开文件，新内容追加文件尾，文件不存在则创建

r+ rb+ 以更新方式打开（读和写），文件必须存在
w+ wb+ 以更新方式打开文件，并把文件长度截短为零，文件不存在则创建
a+ ab+ 以更新方式打开，新内容追加文件尾，文件不存在则创建
返回值：
调用成功则返回文件指针，失败则返回NULL，并设置errno
*/

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
/*
描述：函数fread从stream指向的流中读取nmemb个长度的size的单元，并将它们存储在ptr给定的位置。
参数：
ptr:指向用来存储读取单元的buf
size:读取的单元的大小
nmemb:读取单元的数目
stream：指向文件流指针
返回值：
返回读取的单元的数目，当size等于1，则表示读取的字节数目。
如果发生或者错误或者到达文件尾部，则返回值可能小于指定值，或者等于0，fread
无法区分这两种情况，需要用feof和ferror来进行判断。
*/

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
/*
描述：函数fwrite从ptr给定的位置获取它们获取nmemb个长度的size的单元，并写入到stream指向的流中
参数：
ptr:指向用来写入到文件的数据buf
size:写入单元的大小
nmemb:写入单元的数目
stream：指向文件流指针
返回值：
返回写入的单元的数目，当size等于1，则表示写入的字节数目。
一般用nmemb大小与返回值做比较，如果不相等就是出错。

注意：写入数据的时候，需要写入多少数据就指定多大的数目，如果指定的count大小超过数组缓冲区的大小，
那么数组就会越界，写入的数据是不可知的。
*/

#define filelock
int fcntl(int fd, int cmd, ... arg);
/*
描述：
fcntl对打开的文件描述符fd执行cmd指定的操作，函数具体原型由cmd决定
参数：
fd:文件描述符
cmd:指定操作
arg:指定操作的参数
返回值：
由cmd操作决定
*/

int fcntl(int fd, int cmd, struct flock *flock_structure);
/*
描述：
做文件区域锁定
参数
fd:文件描述符
cmd:区域锁定操作
F_GETLK	获取打开的文件fd的锁信息
F_SETLK	对fd指向的文件的某个区域加锁或解锁
F_SETLKW	与F_SETLK作用一样，不用的是获取不到锁时会一直等待知道获取成功

flock_structure:区域锁定结构体，结构体成员如下：
short l_type
short l_whence
short l_start
off_t l_len
off_t l_pid

type：指定锁类型，锁类型如下所示：
F_RDLCK 建立共享锁（读锁），区域被一个进程设置共享锁之后，可以被其他进程设置共享锁，但是不能设置独占锁
F_WRLCK 建立独占锁（写锁），区域被一个进程设置独占锁之后，不能被其他进程设置共享锁和独占锁
F_UNLCK 解锁，即清除锁

l_whence：指定区域起始位置，SEEK_CUR、SEEK_END、SEEK_SET中的一个
l_start：指定区域的第一个字节
l_len：指定区域字节数
l_pid：记录持有锁的进程

返回值：
F_GETLK和F_SETLK调用成功返回非-1，失败返回-1。
F_SETLKW等待获取才会返回。
*/


int flock(int fd,int operation);
/*
描述：依参数operation所指定的方式对参数fd所指的文件做各种锁定或解除锁定的动作。
此函数只能锁定整个文件，无法锁定文件的某一区域。
参数：
fd：文件描述符
operation：
LOCK_SH 建立共享锁定。多个进程可同时对同一个文件作共享锁定。
LOCK_EX 建立互斥锁定。一个文件同时只有一个互斥锁定。
LOCK_UN 解除文件锁定状态。
LOCK_NB 无法建立锁定时，此操作可不被阻断，马上返回进程。通常与LOCK_SH或LOCK_EX 做OR(|)组合。
单一文件无法同时建立共享锁定和互斥锁定，而当使用dup()或fork()时文件描述词不会继承此种锁定。
返回值：
返回0表示成功，若有错误则返回-1，错误代码存于errno。
*/

#define time
time_t time(time_t *t);
/*
描述：
time能得到一个当前时间距离标准起点时间1970-01-01 00:00:00 +0000(UTC)过去了多少秒
参数：
t：输入型参数，系统将距离标准起点时间的秒数写入到t中，可以设置为NULL。
返回值：
距离标准起点时间的秒数。
*/
	
char *ctime(const time_t *timep);
/*
描述：ctime可以从time_t出发得到一个容易观察的字符串格式的当前时间
参数：
timep：通过time调用获取time_t类型的指针作为输入型参数
返回值：
一个容易观察的字符串格式的时间,失败返回NULL

struct tm *gmtime(const time_t *timep);
描述：获取以struct tm结构体表示的时间，gmtime获取的时间中年份是以1900为基准的差
值，月份是0表示1月，小时数是以UTC时间的0时区为标准的小时数（英国伦敦）
参数：
timep：通过time调用获取time_t类型的指针作为输入型参数
返回值：
struct tm类型的指针，失败返回NULL
*/

struct tm *localtime(const time_t *timep);
/*
localtime和gmtime的唯一区别就是localtime以当前计算机中设置的时区为小时的时间基准，其余一样。
*/

char *asctime(const struct tm *tm);
/*
描述：从struct tm类型的时间出发想得到字符串格式的时间，与ctime返回的时间一样
参数：
tm：struct tm类型的指针作为输入型参数，通过gmtime或者localtime获取
返回值：
一个容易观察的字符串格式的时间,失败返回NULL
*/

size_t strftime(char *s, size_t max, const char *format,const struct tm *tm);
/*
描述：如果想从struct tm类型的时间出发想得到自定义字符串格式的时间，可以用strftime。
参数：
s：指向字符数组，作为输出型参数保存时间字符串
max：字符数组的大小
format：自定义输出格式
tm：struct tm类型的指针作为输入型参数，通过gmtime或者localtime获取
返回值：
返回时间字符串的长度，不包含'\0',长度超过max返回0
*/

time_t mktime(struct tm *tm);
/*
描述：从OS中读取时间时用不到mktime的，这个mktime是用来向操作系统设置时间时用的。
参数：struct tm类型的指针作为输入型参数，通过gmtime或者localtime获取
返回值：返回设置的时间，单位为秒
*/

int gettimeofday(struct timeval *tv, struct timezone *tz);
/*
描述：有时候我们程序希望得到非常精确的时间（譬如以us为单位），这时候就只能通过gettimeofday来实现了。
参数：
tv：输出型参数，       保存获取的时间，精确到微妙
struct timeval 
	{
       time_t      tv_sec;     //seconds
       suseconds_t tv_usec;    //microseconds 
    };
tz：输出型参数，一般设置为NULL
返回值：
成功返回0，失败返回-1
*/


int clock_gettime(clockid_t clk_id, struct timespec *tp);
/*
描述：可以根据需要，获取不同要求的精确时间
参数：
clk_id : 检索和设置的clk_id指定的时钟时间。
CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,
中间时刻如果系统时间被用户改成其他,则对应的时间相应改变
CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
struct timespec
{
        time_t tv_sec; //秒
        long tv_nsec; //纳秒
};
返回值：
成功返回0，失败返回-1
*/


#define exec
/*exec系列函数 用于执行新的程序作为新的进程替换老的进程，新的进程会继承老进程的进程号和资源。
*/
int execl(const char *path, const char *arg, ...(char  *) NULL );
/*
参数：
path	可执行程序的路径名
arg		任意字串都可以
...		其余参数为可执行程序的传参，并且以NULL结束
返回值：
无
*/

int execv(const char *path, char *const argv[]);
/*
参数：
path	可执行程序的路径名
argv	参数指针数组（将execl的arg和传参存放到该指针数组）
返回值：
无
*/

int execlp(const char *file, const char *arg, ...(char  *) NULL);
int execvp(const char *file, char *const argv[]);
/*
使用说明：
跟execl和execv类似，区别是不需要指明程序路径，函数会去环境变量PATH中查找程序，
因此使用execl和execv必须将要执行的程序的路径设置到PATH中，否则查找不到程序
*/

int execle(const char *path, const char *arg, ..., (char *) NULL, char * const envp[] );
extern char **environ;
/*
使用说明：
与前面的execl和execv类似，最后一个参数为环境变量，用来给执行程序中的main函数传递环境变量
*/

#define fifo
int mkfifo(const char *pathname, mode_t mode);
/*
描述：用来创建一个命名管道用于进程间通信。
管道是单向的，因此使用open打开管道时，只能以O_RDONLY或者 O_WRONLY方式打开。

参数：
pathname: 指定命名管道的路径名
mode:指定创建的命令管道文件的权限，创建的文件的权限为mode＆~umask，~mask不包括执行权限。
返回值：
创建成功返回0，创建失败返回-1.
*/

#define pipe
int pipe(int pipefd[2]);
/*
描述：pipe用于创建一个管道作为单向数据通道，管道包含一个读端和一个写端，
写入管道的写端的数据由内核缓冲，直到从管道的读端读取数据为止。 

参数：
pipefd[2]：输出型参数，pipefd用于返回两个引用管道末端的文件描述符，分别是
	
	pipefd[0]是指管道的读取端。
	pipefd[1]指向管道的写端。
	
返回值：
成功时，返回零。如果出错，则返回-1，并正确设置errno。

pipe跟fork实现进程通信：
pipe创建管道之后，使用fork复制了管道，父子进程都会各自拥有管道的读写端，
因此总共有四个管道端口，这四个端口是共通的，因此父子进程就可以通过管道进行通信了。
*/

#define signal
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
/*
描述：signal用来处理shell和终端处理器产生的错误信号

参数：
signum：表示信号编号，当捕捉到信号时，会传递给捕捉函数，常见的信号如下：
	SIGINT  终端中断，通过CTRL+C、kill -2 pid产生
	SIGKILL 强制终止进程，这个信号不能捕捉和忽略，通过kill -9 pid产生
	SIGHUP 	连接挂断，通过kill -HUP(1) pid产生
	SIGTERM	正常终止进程，与SIGKILL不一样，这个信号可以捕捉和忽略，通过kill pid或者kill -15 pid产生

	SIGALRM 超时警告信号，通过alarm调用产生
	
handler：指定信号的处理方式，有下面三种：
	SIG_IGN 忽略信号
	SIG_DFL 默认处理信号
	
	指定sighandler_t类型的函数用来捕捉处理信号
	
返回值：
返回sighandler_t类型的函数指针，若发生错误返回SIG_ERR
*/

int pause(void);
/*
描述：
让当前进程暂停运行，交出CPU给其他进程去执行。当前进程进入pause状态后当前进
程会表现为“卡住、阻塞住”，要退出pause状态当前进程需要被信号唤醒。
返回值：
当信号发生并且信号处理函数执行完毕时，pause才会返回，并且返回-1，errno设置为EINTR

unsigned int alarm(unsigned int seconds);
描述：用来在seconds之后发送一个SIGALRM信号
返回值：
重复调用alarm会重新设置时间并 返回上次alarm设置之后剩余的时间
*/

int kill(pid_t pid, int sig);
/*
描述：kill可以用来包括他本身在内的 其他进程发送一个进程；
发送的进程必须拥有相应的权限，这意味两个进程必须拥有相同的用户ID或者发送信号的进程是超级用户
参数：
pid：指定要发送信号的进程PID
sig：指定要发送的信号。如果sig为0，则不发送信号，但仍执行错误检查，
这可用于检查是否存在pid对应的进程或进程组。
返回值：
调用成功返回0，失败返回-1，失败的原因可能有以下几种：
	EINVAL 给定的信号无效
	EPERM 进程权限不够
	ESRCH 目标进程不存在
*/

#define sigaction
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
/*
描述：跟signal一样用来处理shell和终端处理器产生的错误信号，但比起signal更加健壮
参数：
signum：表示信号编号，当捕捉到信号时，会传递给捕捉函数，常见的信号如下：
	SIGINT 终端中断，通过ctrl + c产生
	SIGKILL 终止进程，这个信号不能捕捉和忽略，通过kill或者killall生成
	SIGALRM  超时警告信号，可以通过alarm调用或者kill调用发起这个信号
	SIGHUP 	连接挂断，这个信号可以通过<kill -HUP pid> 发起
	
act：配置信号的处理方式
struct sigaction
{
    void(*sa_handler)(int);		//信号处理函数，
    void(*sa_sigaction)(int, siginfo_t *, void *); 
    sigset_t sa_mask;
    int sa_flags;
    void(*sa_restorer)(void);
};
结构体参数说明：
	sa_handler：此参数和signal()的参数handler相同，代表新的信号处理函数
	
	sa_sigaction：
		信号处理函数可以采用void (*sa_handler)(int)或void (*sa_sigaction)(int, siginfo_t *, void *)。
		到底采用哪个要看sa_flags中是否设置了SA_SIGINFO位，如果设置了就采用void (*sa_sigaction)(int, siginfo_t *, void *)，
		此时可以向处理函数发送附加信息；默认情况下采用void (*sa_handler)(int)，此时只能向处理函数发送信号的数值。

	sa_mask：用来设置在处理该信号时暂时将sa_mask 指定的信号集屏蔽

	sa_flags：用来设置信号处理的其他相关操作
		SA_RESETHAND：	当调用信号处理函数时，将信号的处理函数重置为缺省值SIG_DFL
		SA_RESTART：		如果信号中断了进程的某个系统调用，那么信号处理函数执行完成后，系统调用将重启而不是被信号中断
		SA_NODEFER ：	一般情况下， 当信号处理函数运行时，内核将阻塞该给定信号。但是如果设置了 SA_NODEFER标记， 
						那么在该信号处理函数运行时，内核将不会阻塞该信号

	sa_restorer：此参数没有使用。    
	
oldact：用来备份旧的信号处理方式，一般设置为NULL

返回值：
成功返回0，失败返回-1。
*/

int sigemptyset(sigset_t *set);
/*
该函数的作用是将信号集初始化为空，成功时返回0，失败时返回-1。
*/

int sigfillset(sigset_t *set);
/*
该函数的作用是把信号集初始化包含所有已定义的信号，成功时返回0，失败时返回-1。
*/

int sigaddset(sigset_t *set, int signo);
/*
该函数的作用是把信号signo添加到信号集set中，成功时返回0，失败时返回-1。
*/

int sigdelset(sigset_t *set, int signo);
/*
该函数的作用是把信号signo从信号集set中删除，成功时返回0，失败时返回-1。
*/

int sigismember(sigset_t *set, int signo);
/*
该函数的作用是判断给定的信号signo是否是信号集中的一个成员，
如果是返回1，如果不是，返回0，如果给定的信号无效，返回-1。
*/

int sigpromask(int how, const sigset_t *set, sigset_t *oset);
/*
功能描述：
该函数可以根据参数how指定的方法修改进程的信号屏蔽字。
新的信号屏蔽字由参数set（非空）指定，而原先的信号屏蔽字将保存在oset（非空）中。
参数：
how：指定信号屏蔽字的配置方法，取值如下：
	SIG_BLOCK	将参数set中的信号添加到现有的信号屏蔽字中
	SIG_SETMASK	把信号屏蔽字设置为set中的信号
	SIG_UNBLOCK 从信号屏蔽字中删除参数set中的信号
set：输入型参数，需要设置的信号屏蔽字集合
oset：输出型参数，保存旧的信号屏蔽字集合
如果set为空，则how没有意义，但此时调用该函数，如果oset不为空，则把当前信号屏蔽字保存到oset中。
返回值：
成功完成返回0，如果how取值无效返回-1，并设置errno为EINVAL。
注意：
调用这个函数才能改变进程的屏蔽字，之前的函数都是为改变一个变量的值而已，并不会真正影响进程的屏蔽字。
*/

int sigpending(sigset_t *set);
/*
功能描述：
该函数的作用是将被阻塞的信号中停留在待处理状态的一组信号写到参数set指向的信号集中。
参数：
set：输出型参数，保存阻塞信号中处于待处理的一组信号
返回值：
成功调用返回0，否则返回-1，并设置errno表明错误原因。
*/

int sigsuspend(const sigset_t *sigmask);
/*
功能描述：
该函数通过将进程的屏蔽字替换为由参数sigmask给出的信号集，然后挂起进程的执行。
当产生信号时，sigsuspend调用会在信号处理函数执行完毕后返回。
当进程被终止时，sigsuspend调用则不会返回。

返回值：
sigsuspend总是返回-1,并设置errno
注意：如果一个信号被进程屏蔽时，它就不会传递给进程，但会停留在待处理状态，
当进程解除对待处理信号的屏蔽时，待处理信号就会立刻被处理。
*/


#define thread
int pthread_ceate(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
/*
描述：pthread_create用来创建一个新线程
参数：
thread：输出型参数，指向线程标识符的地址，我们用该标识符来引用新线程
attr：输入型参数，用来设置线程的属性，一般不需要设置，因此一般设置为NULL
start_routine：这个函数指针指向 线程启动函数，线程从该函数开始执行
arg：输入型参数，作为启动函数的函数参数，如果不需要传递则设置为NULL
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_join(pthread_t thread, void **retval);
/*
描述：pthread_join用来阻塞等待回收指定的线程,获取线程的终止状态
参数：
thread：线程标识符
retval：输出型参数，指向线程的返回值(pthread_exit的参数)，一般设置为NULL
返回值：
调用成功则返回0，失败返回错误代码	
*/

void pthread_exit(void *retval);
/*
描述：pthread_exit用来终止调用它的线程，并返回一个指向某个对象的指针
参数：
retval：输入性参数，用来指向线程的返回值，一般设置为NULL。决不能返回一个指向局部变量的指针，因为线程终止退出后，
这个局部变量就不存在了，这样会引起程序漏洞。
*/

#define thread_detach
/*
关于未分离线程和分离线程
在我们使用默认属性创建一个线程的时候，线程是 joinable的。joinable状态的线程，
必须在另一个线程中使用pthread_join() 等待其结束，如果一个 joinable 的线程在结束后，
没有使用 pthread_join() 进行操作，这个线程就会变成"僵尸线程"。每个僵尸线程都会消耗
一些系统资源，当有太多的僵尸线程的时候，可能会导致创建线程失败。
当线程被设置为分离状态后，线程结束时，它的资源会被系统自动的回收，
而不再需要在其它线程中对其进行 pthread_join() 操作。
*/

int pthread_attr_init(pthread_attr_t *attr);
/*
描述：初始化默认线程属性，获取默认线程属性
参数：
attr：输出型参数，指向线程属性的指针
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
/*
描述：设置线程默认分离状态，使用pthread_attr_init初始化后的线程默认是PTHREAD_CREATE_JOINABLE的
参数：
attr：输入型参数，指向线程属性的指针
detachstate：设置线程是否分离
	PTHREAD_CREATE_DETACHED	//分离线程
	PTHREAD_CREATE_JOINABLE //回收线程
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_attr_destroy(pthread_attr_t *attr);
/*
描述：清理回收线程属性
参数：
attr：指向线程属性的指针
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_detach(pthread_t thread);
/*
描述：设置线程分离
参数：
thread：线程标识符
返回值：
调用成功则返回0，失败返回错误代码
*/

pthread_t pthread_self(void);
/*
返回值：
这个函数调用总是成功，返回调用线程的标识符
*/

#define thread_cancel
int pthread_cancel(pthread_t thread);
/*
描述：给指定线程发送取消请求，终止线程
参数：
thread：指定线程标识符
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_setcancelstate(int state, int *oldstate);
/*
描述：用来设置当前线程的取消状态，线程默认取消状态为PTHREAD_CANCEL_ENABLE
参数：
state：设置线程的取消状态
	PTHREAD_CANCEL_ENABLE	表示允许接收取消请求
	PTHREAD_CANCEL_DISABLE  表示忽略接收取消请求
oldstate：输出型参数，保存原先的取消状态
返回值：
调用成功则返回0，失败返回错误代码
*/

int pthread_setcanceltype(int type, int *oldtype);
/*
描述：用来设置线程的取消类型，调用前必须先调用pthread_setcancelstate设置好取消状态，线程默认取消类型为PTHREAD_CANCEL_DEFERRED
参数：
type：设置线程的取消类型
	PTHREAD_CANCEL_ASYNCHRONOUS  表示接收到取消请求后立即采取行动终止线程
	PTHREAD_CANCEL_DEFERRED		 表示接收到取消请求后，需要一直等待直到线程执行了以下函数
	才采取行动(pthread_join\pthread_cont_wait\pthread_cont_timedwait\pthread_testcancel
	\semwait\sigwait),其他阻塞函数也可能成为取消点，比如read、wait。
oldtype：输出型参数，保存原先的取消类型
返回值：
调用成功则返回0，失败返回错误代码
*/

#define thread_mutex
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
/*
描述：初始化互斥锁，初始化成功的互斥锁变量默认是解锁的
参数：
mutex：输出型参数，指向互斥锁变量的指针
attr：输入型参数，用来设置互斥锁变量的属性，一般设定为NULL表示使用默认的参数
返回值：
调用成功返回0
*/

int pthread_mutex_lock(pthread_mutex_t *mutex);
/*
描述：用来将互斥锁加锁，如果互斥锁已经在其他线程调用pthread_mutex_lock函数加锁，则这里就
		会阻塞无法继续执行直到互斥锁已经处于解锁状态这里才能够加锁并继续执行程序
参数：
mutex：指向互斥锁变量的指针
返回值：
调用成功返回0
*/

int pthread_mutex_unlock(pthread_mutex_t *mutex);
/*
描述：用来将互斥锁解锁，这样需要互斥锁的线程就才能够利用互斥锁进行加锁
参数：
mutex：指向互斥锁变量的指针
返回值：
调用成功返回0
*/

int pthread_mutex_destroy(pthread_mutex_t *mutex);
/*
描述：用来销毁互斥锁，销毁前互斥锁必须先解锁，销毁后的互斥锁可以重新使用pthread_mutex_init初始化
参数：
mutex：指向互斥锁变量的指针
返回值：
调用成功返回0
*/

#define thread_sem

int sem_init(sem_t *sem, int pshared, unsigned int value);
/*
描述：sem_init用来初始化信号量
参数：
sem：输出型参数，指向信号量变量的指针
pshared：设置信号量是在线程中还是在进程中共享，0表示在线程中共享，非零则表示在进程中共享
value：用来设置信号量的初始值
返回值：
调用成功返回0，失败返回-1
*/

int sem_post(sem_t *sem);
/*
描述：以原子操作的方式给信号量的值加1。
参数：
sem：指向信号量变量的指针
返回值：
调用成功返回0，失败返回-1
*/

int sem_wait(sem_t *sem);
/*
描述：以原子操作的方式给信号量的值减一，但它会等待直到信号量有个非零值才会进行减法操作
参数：
sem：指向信号量变量的指针
返回值：
调用成功返回0，失败返回-1
*/

int sem_destroy(sem_t *sem);
/*
描述：函数用来销毁信号量
参数：
sem：指向信号量变量的指针
返回值：
调用成功返回0，失败返回-1
*/


#define other_iomodel
int fcntl(int fd, F_GETFL);
int fcntl(int fd, F_SETFL, ... arg);
/*
描述：获取及设置文件描述符flags
参数:
fd:文件描述符
cmd: 
F_GETFL	获取文件描述符flags，忽略参数arg
F_SETFL	通过arg参数设置文件描述符flags
arg:
文件描述符的flags
返回值：
F_GETFL	返回文件描述符flags
F_SETFL	失败返回-1
*/

int fcntl(int fd, F_SETOWN, pid);
/*
描述：获取及设置文件描述符flags
参数:
fd:文件描述符
cmd: 
F_SETOWN	设定文件描述符的属主，即文件描述符上可执行IO时会接收到通知信号的进程或进程组。
arg:
指定进程或进程组的pid。
返回值：
F_SETOWN	失败返回-1
*/

int epoll_create(int size);
/*
描述：用来创建一个新的epoll实例用来检查文件描述符IO
参数：
size：指定要检查的文件描述符的数目，从linux内核版本2.6.8开始，这个参数被忽略，但是必须大于0
返回值：
成功返回一个非负数的epoll实例，失败返回-1
*/

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
/*
描述：用来对epoll_create创建的epoll实例进行配置。
参数：
epfd：epoll实例
op:指定操作类型，主要是以下三种
EPOLL_CTL_ADD
	将文件描述符fd添加到epoll中并指定事件
EPOLL_CTL_MOD
	修改已经添加到epoll实例中的文件描述符的事件
EPOLL_CTL_DEL
	删除添加到epoll实例中的文件描述符，此操作忽略event

fd：指定需要执行操作的文件描述符
event：指向配置文件描述符事件的结构体的指针
struct epoll_event {
	uint32_t	 events;	  // Epoll events 
	epoll_data_t data;		  // User data variable 
};
events：掩码形式指定事件，常用事件如下
	EPOLLIN		输入事件
	EPOLLOUT	输出事件

typedef union epoll_data {
               void        *ptr;
               int          fd;
               uint32_t     u32;
               uint64_t     u64;
           } epoll_data_t;	
data：指定文件描述符就绪时，回传给调用进程的用户数据，其中fd是一定要指定的，
这样才能知道就绪事件是在哪个文件描述符上发生的。

返回值：调用成功返回0，失败返回-1.
*/

int epoll_wait(int epfd, struct epoll_event *events,  int maxevents, int timeout);
/*
描述：返回处于就绪的文件描述符信息
参数：
epfd：epoll实例
events：events指向的结构体数组由用户申请，保存返回的文件描述符就绪
信息（包含就绪事件以及就绪文件描述符）。
maxevents：指定events对应的结构体数组元素个数。
timeout：指定超时时间，单位为milliseconds 毫秒
-1 表示无限等待
0  表示非阻塞
返回值：
返回就绪的文件描述符个数，错误返回-1，超时返回0.
注意：
epoll_wait调用返回后，再次进行epoll_wait时，无需再次对描述符事件进行配置
*/

int poll(struct pollfd *fds, nfds_t nfds, int timeout);
/*
描述：poll实现函数外部阻塞式，内部非阻塞式自动轮询多路阻塞式IO
参数：
fds：指定轮询的文件描述符以及事件，结构体定义如下
struct pollfd {
               int   fd;         
               short events;     
               short revents;     
           };

fd		：文件描述符
events	：指定为文件描述符检查的事件的位掩码，举例如下：
	POLLIN	输入事件
	POLLOUT	输出事件
	POLLERR	发生错误事件	
revents	：poll返回时，设定该文件描述符上发生的事件的位掩码
nfds：指定轮询文件描述符的数目，一般为轮询中的最大的文件描述符+1
timeout：指定超时时间，单位为milliseconds 毫秒
-1 表示无限等待
0  表示非阻塞
返回值：
返回发生的事件的文件描述符的数目，不同于select，即使一个描述符发生多个事件也只会计算一次。
-1 表示发生错误
0  表示超时
注意：
poll就绪返回之后，再次poll时，无需对描述符的事件再次进行配置

如何屏蔽文件描述符的事件？
1、将events设置为0将忽略fd上发生的事件。
2、将fd设定为负数，将导致events上的事件被忽略，revents返回0。
*/

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
/*
描述：select实现外部阻塞，内部非阻塞自动轮询检测多路阻塞IO
参数：
nfds：指定轮询文件描述符的数目，一般为集合中最大的文件描述符+1
readfds：检测输入是否就绪的文件描述符集合
writefds：检测输出是否就绪的文件描述符集合
exceptfds：检测异常是否发生的文件描述符集合
timeout：指定超时时间
当就绪时，timeout返回剩余时间
直接设置timeout为NULL表示无限等待
tv_sec和tv_usec为0表示不阻塞
struct timeval {
	long	tv_sec; 		// seconds 
	long	tv_usec;		// microseconds 
};
返回值：
错误返回-1
超时返回0，并且清空集合
返回正整数表示各个集合中就绪的文件描述符总数

注意：
当select就绪返回后，再次select时，需要重新初始化配置文件描述符集合。
*/
void FD_ZERO(fd_set *set);			//清空
void FD_SET(int fd, fd_set *set);	//添加
void FD_CLR(int fd, fd_set *set);	//移除
int  FD_ISSET(int fd, fd_set *set); //判断哪路IO就绪




#define stray_knowledge
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
/*
描述：mmap将一个文件或者其它对象映射进内存。文件被映射到多个页上，如果文件的大小不是所有页的大
小之和，最后一个页不被使用的空间将会清零。
参数：
addr：映射区的开始地址，设置为0时表示由系统决定映射区的起始地址。
length：映射区的长度，长度单位是 以字节为单位，不足一内存页按一内存页处理。
prot：期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理地组合在一起
PROT_EXEC  页内容可以被执行
PROT_READ  页内容可以被读取
PROT_WRITE 页可以被写入
PROT_NONE  页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。它的值可以是一个或者多个标志的组合体，这里只列举两个常用的
MAP_SHARED  与其它所有映射这个对象的进程共享映射空间。对共享区的写入，相当于输出到文件。直到msync()或者munmap()被调用，文件实际上不会被更新。
MAP_PRIVATE 建立一个写入时拷贝的私有映射。内存区域的写入不会影响到原文件。这个标志和以上标志是互斥的，只能使用其中一个。
fd：有效的文件描述符。一般是由open()函数返回，其值也可以设置为-1，此时需要指定flags参数中的MAP_ANON,表明进行的是匿名映射。
off_toffset：被映射对象内容的起点。
返回值：
成功执行时，mmap()返回被映射区的指针，munmap()返回0。失败时，mmap()返回MAP_FAILED[其值为(void *)-1]，munmap返回-1。
*/


void _exit(int status);
void exit(int status);
/*
return、exit、_exit的主要区别
1、exit主要用来终止进程，正常终止一般使用exit(0)，异常终止使用exit(1),只要调用了exit，程序就会退出；
return只有在main函数中调用才能终止进程，函数调用时return表示调用堆栈的返回
2、_exit和exit功能基本一样，但是exit和return终止进程时能调用atexit注册的回调函数，_exit不会调用回调函数
*/

