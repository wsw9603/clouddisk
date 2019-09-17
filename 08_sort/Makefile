ROOT_DIR := $(abspath .)
OBJ_DIR := $(ROOT_DIR)
INC_DIR := $(ROOT_DIR)/include
CFLAG := -I$(INC_DIR)
CC := gcc $(CFLAG)

CUR_SOURCE := $(wildcard *.c)
CUR_OBJS := $(patsubst %.c, %.o, $(CUR_SOURCE))
SUB_DIRS := $(ROOT_DIR)/src

OUT_BIN := main

all : $(OUT_BIN)
$(OUT_BIN) : $(CUR_OBJS) $(SUB_DIRS)
	$(CC) -o $(OUT_BIN) $(OBJ_DIR)/*.o

export CC OBJ_DIR
$(SUB_DIRS) : ECHO
	make -C $@

$(CUR_OBJS) : %.o : %.c
	$(CC) -c $^ -o $(OBJ_DIR)/$@

.PHONY:
clean :
	rm -rf *.o $(OUT_BIN)

ECHO :
	@echo `pwd`
