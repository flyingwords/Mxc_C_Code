#include用来引用其他Makefile，有时候Makefile总体比较复杂，因此分成好几个Makefile来写，
#然后在主Makefile中使用include来引用。引用的效果也是原地展开的，和C语言中的头文件包含非常相似。
include ./Makefile.param

all: success

success:$(EXE)
		@echo "************************************"
		@echo "  *SUCCESSFUL COMPILE $(EXE)"
		@echo "************************************"
		sync


$(EXE):$(OBJS)
		@echo "* CREATE $(EXE)"
		$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $(OBJS)
		@echo "* MAKE SUBDIR MAKEFILE"
		#-C 指定需要执行的Makefile路径
		make -C ./subdir

$(OBJS):%.o:%.c							
		@#echo "$^"
		$(CC) $(CFLAGS) $(INC_FLAGS) -c "$<" -o "$@" 

.PHONY:var_print clean
var_print:
		@echo "CC = $(CC)"
		@echo "SRCS = $(SRCS)"
		@echo "OBJS = $(OBJS)"
		@echo "OBJ_DIR = $(OBJ_DIR)"
		@echo "CFLAGS = $(CFLAGS)"
		@echo "INC_FLAGS = $(INC_FLAGS)"
		@echo "EXE = $(EXE)"

clean:
		rm $(OBJS) -rf
		rm $(EXE) -rf
		
