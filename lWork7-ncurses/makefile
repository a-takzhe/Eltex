bin_dir := ./bin
SRC_LIB_FILES := $(wildcard $(bin_dir)/*.c)
OBJ_LIB_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.o, $(SRC_LIB_FILES))
#LIB_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.so, $(SRC_PLUG_FILES))

all: main

main: $(OBJ_LIB_FILES) main.o
	gcc main.o $(OBJ_LIB_FILES) -o main -lncurses

main.o: main.c
	gcc main.c -c -g

# compare.o: compare.c
# 	gcc compare.c -c -g

$(bin_dir)/%.o: $(bin_dir)/%.c
	gcc -c -o $@ $< -g3

clean:
	rm -rf *.o main $(bin_dir)/*.o 
