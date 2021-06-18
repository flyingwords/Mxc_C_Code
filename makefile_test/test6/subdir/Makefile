#上级Makefile使用export导出变量到全局，下级Makefile才与上级Makefile的变量打印结果一致
#如果下级已经定义了同名变量，则上级export不会覆盖下级Makefile中定义的同名变量。
CC := hellowold
SRCS := hellowold
OBJS := hellowold
OBJ_DIR := hellowold
CFLAGS := hellowold
INC_FLAGS := hellowold
EXE := hellowold

.PHONY:all
all:
		@echo "CC = $(CC)"
		@echo "SRCS = $(SRCS)"
		@echo "OBJS = $(OBJS)"
		@echo "OBJ_DIR = $(OBJ_DIR)"
		@echo "CFLAGS = $(CFLAGS)"
		@echo "INC_FLAGS = $(INC_FLAGS)"
		@echo "EXE = $(EXE)"
