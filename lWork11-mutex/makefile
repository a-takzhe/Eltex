lib_dir := ./lib
SRC_LIB_FILES := $(wildcard $(lib_dir)/*.c)
OBJ_LIB_FILES := $(patsubst $(lib_dir)/%.c, $(lib_dir)/%.o, $(SRC_LIB_FILES))


all: main #delo

main: $(OBJ_LIB_FILES) main.o
	gcc main.o $(OBJ_LIB_FILES) -o main -pthread

main.o: main.c
	gcc main.c -c 

# main.s: main.i
# 	gcc main.i -S -O0 -g -masm=intel 

# main.i: main.c
# 	gcc -E main.c -o main.i

$(lib_dir)/%.o: $(lib_dir)/%.c
	gcc -c -o $@ $< -g3


clean:
	rm -rf *.o main $(lib_dir)/*.o  *.s

delo:
	rm -rf *.o $(lib_dir)/*.o
