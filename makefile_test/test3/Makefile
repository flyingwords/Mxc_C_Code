
#####################
val_1 = hello
val_2 = $(val_1)  # 使用 = 赋值变量，引用时才会展开
val_3 := $(val_1) # 使用 := 赋值变量，会立即展开

val_4 ?= $(val_1)	# 使用 ?+ 赋值，变量没有赋值时才会赋值，并且只有引用时才会展开
val_4 ?= likecode	# 这里赋值不会成功

val_1 = world

####################




all:
		@#echo "val_1 = $(val_1)"
		@#echo "val_2 = $(val_2)"
		@#echo "val_3 = $(val_3)"
		
		@echo "val_4 = $(val_4)"
