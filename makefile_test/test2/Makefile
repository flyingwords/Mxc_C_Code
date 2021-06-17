
SRC_ROOT := .
SRC_DIR   :=  $(SRC_ROOT)


#$(shell bash_cmd)
#函数功能：函数“ shell”所实现的功能和shell中的引用（ ``）相同。实现对命令
#的扩展。这就意味着需要一个shell 命令作为此函数的参数，函数的返回结果是
#此命令在shell中的执行结果。make将函数返回结果中的所有换行符（“ \n”）或者一对“ \n\r”替换为单空格；
#去掉末尾的回车符号（“ \n”）或者“ \n\r”。
#返回值： 函数“ shell”的参数（一个 shell 命令）在 shell 环境中的执行结果。

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=%.o)

ALL_FILE := $(SRCS)
ALL_FILE += $(OBJS)

#####################文本处理函数################################

#$(subst FROM,TO,TEXT)
#函数名称：字符串替换函数—subst。
#函数功能：把字串" TEXT"中的"FROM"字符替换为"TO"。
#返回值：替换后的新字符串。
subst_res := $(subst .c,.o,$(SRCS))
#subst_res := $(subst %.c,%.o,$(SRCS)) #subst不能使用% 通配符


#$(patsubst PATTERN,REPLACEMENT,TEXT)
#函数名称：模式替换函数— patsubst。
#函数功能：搜索"TEXT"中以空格分开的单词，将否符合模式"PATTERN"替换为"REPLACEMENT"。
#返回值：替换后的新字符串。
patsubst_res := $(patsubst %.c,%.o,$(SRCS))


#$(strip STRINT)
#函数名称：去空格函数—strip。
#函数功能：去掉字串（若干单词，使用若干空字符分割）"STRINT"开头和结尾的空字符（空字符包括空格、 [Tab]等不可显示字符），并将其中多个连续空字符合并为一个空字符。
#返回值：无前导和结尾空字符、使用单一空格分割的多单词字符串。
without_strip_res := a b c 	
strip_res := $(strip $(without_strip_res))


#$(findstring FIND,IN)
#函数名称：查找字符串函数—findstring。
#函数功能：在字串"IN"查找"FIND"字串。
#返回值：如果在"IN"之中存在"FIND"，则返回"FIND"，否则返回空。
#函数说明：字串"IN"之中可以包含空格、 [Tab]。搜索需要是严格的文本匹配。
findstring_res := $(findstring main.c,$(SRCS))


#$(filter PATTERN…,TEXT)
#函数名称：过滤函数— filter。
#函数功能：过滤掉字串"TEXT"中所有不符合模式"PATTERN"的单词，保留所有符合此模式的单词。可以使用多个模式，
#模式中一般需要包含模式字符"%"，存在多个模式时，模式表达式之间使用空格分割。
#返回值：空格分割的"TEXT"字串中所有符合模式"PATTERN"的字串。
filter_left_o_res := $(filter %.o, $(ALL_FILE))
filter_left_c_res := $(filter %.c, $(ALL_FILE))

#$(sort LIST)
#函数名称：排序函数— sort。
#函数功能：给字串“ LIST”中的单词以首字母为准进行排序（升序），并取掉重复的单词。
#返回值：空格分割的没有重复单词的字串。
#函数说明：两个功能，排序和去字串中的重复单词。可以单独使用其中一个功能。
without_sort_res := $(ALL_FILE)
sort_res := $(sort $(ALL_FILE))


#####################文件名处理函数################################

#$(dir NAMES…)
#函数名称：取目录函数—dir。
#函数功能：从文件名序列"NAMES…"中取出各个文件名的目录部分。
#文件名的目录部分就是包含在文件名中的最后一个斜线（包括斜线）之前的部分。
#如果文件名中没有斜线，认为此文件为当前目录（"./"）下的文件。
#返回值：空格分割的文件名序列"NAMES…"中每一个文件的目录部分。
dir_res := $(dir $(SRCS))

#$(suffix NAMES…)
#函数名称：取后缀函数— suffix。
#函数功能：从文件名序列"NAMES…"中取出各个文件名的后缀。
#后缀是文件名中最后一个以点"."开始的（包含点号）部分，如果文件名中不包含一个点号，则为空。
#"NAMES…"是多个文件名时，返回值是多个以空格分割的单词序列。
#返回值：以空格分割的文件名序列"NAMES…"中每一个文件的后缀序列；如果文件名没有后缀部分，则返回空。
suffix_res := $(suffix $(SRCS))

#$(wildcard PATTERN)
#函数名称：获取匹配模式文件名函数—wildcard
#函数功能：列出当前目录下所有符合模式"PATTERN"格式的文件名。
#返回值：空格分割的、存在当前目录下的所有符合模式" PATTERN"的文件名。
#函数说明："PATTERN"使用shell可识别的通配符，包括"?"（单字符）、"*"（多字符）等。
wildcard_res := $(wildcard *.c ./lib_api/*.c)

####################################################################


all:
		@#echo "$(SRCS)"
		@#echo "$(subst_res)"
		@#echo "$(patsubst_res)"
		@#echo "###$(without_strip_res)###"
		@#echo "###$(strip_res)###"
		@#echo "$(findstring_res)"
		@#echo  $(filter_left_o_res)
		@#echo  $(filter_left_c_res)
		@echo $(without_sort_res)
		@echo $(sort_res)
		@#echo $(dir_res)
		@#echo $(suffix_res)
		@#echo $(wildcard_res)


		
