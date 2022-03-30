bin_dir := ./bin
SRC_PLUG_FILES := $(wildcard $(bin_dir)/*.c)
OBJ_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.o, $(SRC_PLUG_FILES))
LIB_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.so, $(SRC_PLUG_FILES))
all: main
hand_lib: lib_add.so lib_subtract.so

main: main.o plug_worker.o pw_list.o input_validation.o $(LIB_PLUG_FILES) 
	gcc main.o plug_worker.o pw_list.o input_validation.o -o main -ldl

main.o: main.c
	gcc main.c -c -g

plug_worker.o: plug_worker.c
	gcc plug_worker.c -c -g

pw_list.o: pw_list.c
	gcc pw_list.c -c -g

input_validation.o: input_validation.c
	gcc input_validation.c -c -g

$(bin_dir)/%.so: $(bin_dir)/%.o
	gcc -shared -o $@ $^

$(bin_dir)/%.o: $(bin_dir)/%.c
	gcc -fPIC -c -o $@ $<

clean:
	rm -rf *.o main $(bin_dir)/*.o $(bin_dir)/*.so

########################### hand_lib #######################################
lib_add.so: ./bin/add.o
	gcc -shared ./bin/add.o -o ./bin/lib_add.so

lib_subtract.so: ./bin/subtract.o
	gcc -shared ./bin/subtract.o -o ./bin/lib_subtract.so

./bin/add.o: ./bin/add.c
	gcc -fPIC ./bin/add.c -c -o ./bin/add.o

./bin/subtract.o: ./bin/subtract.c
	gcc -fPIC ./bin/subtract.c -c -o ./bin/subtract.o
############################################################################
