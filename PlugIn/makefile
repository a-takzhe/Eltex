bin_dir := ./bin
SRC_PLUG_FILES := $(wildcard $(bin_dir)/*.c)
OBJ_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.o, $(SRC_PLUG_FILES))
LIB_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.so, $(SRC_PLUG_FILES))
all: main

main: main.o plug_worker.o $(LIB_PLUG_FILES) 
	gcc main.o plug_worker.o -o main -ldl

main.o: main.c
	gcc main.c -c -g

plug_worker.o: plug_worker.c
	gcc plug_worker.c -c -g

# lib_add.so: ./bin/add.o
# 	gcc -shared ./bin/add.o -o ./bin/lib_add.so

# lib_subtract.so: ./bin/subtract.o
# 	gcc -shared ./bin/subtract.o -o ./bin/lib_subtract.so

# ./bin/add.o: ./bin/add.c
# 	gcc -fPIC ./bin/add.c -c -o ./bin/add.o

# ./bin/subtract.o: ./bin/subtract.c
# 	gcc -fPIC ./bin/subtract.c -c -o ./bin/subtract.o

$(bin_dir)/%.so: $(OBJ_PLUG_FILES)
	gcc -shared -o $@ $<

$(bin_dir)/%.o: $(bin_dir)/%.c
	gcc -fPIC -c -o $@ $<

clean:
	rm -rf *.o main $(bin_dir)/*.o $(bin_dir)/*.so

