
PRODUCT := HIS
#PRODUCT := HITE
#PRODUCT := ZQ

#if 或运算 方式一
#ifeq ($(strip $(PRODUCT)), $(filter $(PRODUCT),HIS HITE))
#		CFLAGS += -D$(PRODUCT)
#endif

#if 或运算 方式二
ifneq (,$(filter $(PRODUCT),HIS HITE))
		CFLAGS += -D$(PRODUCT)
endif

all:
		echo "CFLAGS = $(CFLAGS)"
