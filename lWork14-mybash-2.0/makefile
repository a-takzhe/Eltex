lib_dir := ./lib
SRC_LIB_FILES := $(wildcard $(lib_dir)/*.c)
OBJ_LIB_FILES := $(patsubst $(lib_dir)/%.c, $(lib_dir)/%.o, $(SRC_LIB_FILES))


all: mybash #delo

mybash: $(OBJ_LIB_FILES) mybash.o
	gcc mybash.o $(OBJ_LIB_FILES) -o mybash-2.0

mybash.o: mybash.s
	gcc mybash.s -c 

mybash.s: mybash.i
	gcc mybash.i -S -O0 -g -masm=intel 

mybash.i: mybash.c
	gcc -E mybash.c -o mybash.i


$(lib_dir)/%.o: $(lib_dir)/%.c
	gcc -c -o $@ $< -g3



clean:
	rm -rf *.o mybash $(lib_dir)/*.o  *.s *.i 

delo:
	rm -rf *.o $(lib_dir)/*.o
