lib_dir := ./lib
SRC_LIB_FILES := $(wildcard $(lib_dir)/*.c)
OBJ_LIB_FILES := $(patsubst $(lib_dir)/%.c, $(lib_dir)/%.o, $(SRC_LIB_FILES))


all: main #delo

main:
	gcc main.c -o main -pthread

clean:
	rm -rf *.o main $(lib_dir)/*.o  *.s

delo:
	rm -rf *.o $(lib_dir)/*.o
