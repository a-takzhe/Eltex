lib_dir := ./lib
SRC_LIB_FILES := $(wildcard $(lib_dir)/*.c)
OBJ_LIB_FILES := $(patsubst $(lib_dir)/%.c, $(lib_dir)/%.o, $(SRC_LIB_FILES))


all: main #delo

main: main.c
	gcc main.c -o main

clean:
	rm -rf *.o main $(lib_dir)/*.o  *.s

