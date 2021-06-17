CC := gcc

SRC_ROOT := .
OBJ_ROOT  := .
SRC_DIR   :=  $(SRC_ROOT)
#获取linux命令执行结果时，必须使用 $(shell cmd)格式
SRCS      :=  $(shell find $(SRC_DIR) -name '*.c')
#sort是Makefile函数，用来排序
SRCS      :=  $(sort $(SRCS))
#变量赋值时，如果使用了bash通配符，那么必须使用 $(wildcard ...)格式，否则会解析失败
SRCS_TEST := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/lib_api/*.c)

#######################################################################################################

#将.c文件替换为.o文件，下面几种方式都可以
OBJS      :=  $(SRCS:$(SRC_ROOT)/%.c=$(OBJ_ROOT)/%.o) #不仅将./目录下的.c替换为.o，子目录./lib_api下的目录也会被替换，效果等同于 $(SRCS:%.c=%.o)
#OBJS      :=  $(SRCS:%.c=%.o)
#OBJS      :=  $(SRCS:.c=.o)
#patsubst是Makefile，用来做模式替换，一般配合规则通配符%使用
#OBJS      :=  $(patsubst %.c,%.o,$(SRCS))

#dir是Makefile函数，用来获取目录名
OBJ_DIR   :=  $(sort $(dir $(OBJS)))

#######################################################################################################


#CFLAGS是Makefile内置环境变量，INC_FLAGS不是Makefile内置环境变量
#gcc编译的时候其实后面不会加上$(CFLAGS)，默认会自动套用CFLAGS中选项，但是INC_FLAGS因为不是内置环境变量，因此要加上$(INC_FLAGS)
CFLAGS := -Wall -g -lpthread -lm -ldl
#-Wall会打开一些很有用的警告选项，建议编译时加此选项，默认也是该选项
#-Werror选项会将所有编译的warning 视为error
#-w选项禁止显示所有警告信息
CFLAGS += -Werror
#CFLAGS += -w
#CFLAGS += -Wall
INC_FLAGS := -I$(SRC_ROOT)
INC_FLAGS += -I./lib_api/
#CFLAGS += $(INC_FLAGS) #将INC_FLAGS包含进CFLAGS

#######################################################################################################


EXE := exe_test

all: success

#引入success是为了判断是否编译成功并打印成功信息
success:$(EXE)
		@echo "************************************"
		@echo "  *SUCCESSFUL COMPILE $(EXE)"
		@echo "************************************"
		sync


$(EXE):$(OBJS)
		@echo "* CREATE $(EXE)"
		@#$(CC) $(CFLAGS) -o $@ $(OBJS) 
		$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $(OBJS) #$(CFLAGS)其实可以不加，因为是内置环境变量



#编译OBJS里面的.o文件，其实是Makefile的隐含规则，，因此这个规则可以不写，但是如果没有将INC_FLAGS包含进CFLAGS，因为
#INC_FLAGS是非内置环境变量，因此编译时就可以因为找不到头文件而报错，两种解决方式：
#（1）CFLAGS += $(INC_FLAGS) ，将INC_FLAGS包含进CFLAGS
#（2）编写显式规则，gcc后面带上$(INC_FLAGS)，如下所示。

#依赖规则 将OBJS中的.o替换为.c，下面几种写法都可以，效果是一样的
#gcc的编译选项 -c 表示只编译不链接，这里不能链接，否则会报错，上面的规则才是将所有.o链接成可执行程序
#$@　　表示规则的目标
#$^　　  表示规则的依赖
$(OBJS):%.o:%.c							
#$(OBJS):$(OBJ_ROOT)/%.o:$(SRC_ROOT)/%.c
		@#echo "$^"
		$(CC) $(CFLAGS) $(INC_FLAGS) -c "$<" -o "$@" #$(CFLAGS)其实可以不加，因为是内置环境变量

		
var_print:
		@echo "$(SRCS)"
		@echo "$(OBJS)"
		@echo "$(OBJ_DIR)"
		@echo "$(INC_FLAGS)"
		@echo "$(SRCS_TEST)"
clean:
		rm $(OBJS) -rf
		rm $(EXE) -rf
