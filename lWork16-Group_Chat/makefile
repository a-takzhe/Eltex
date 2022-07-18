C_DIR := ./client
S_DIR := ./server

C_LIB_DIR := $(C_DIR)/lib
S_LIB_DIR := $(C_DIR)/lib

SRC_LIB_FILES := $(wildcard $(C_LIB_DIR)/*.c)
OBJ_LIB_FILES := $(patsubst $(C_LIB_DIR)/%.c, $(C_LIB_DIR)/%.o, $(SRC_LIB_FILES))

#LIB_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.so, $(SRC_PLUG_FILES))

all: client #server

client: $(OBJ_LIB_FILES) client.o 
	gcc $(C_DIR)/client.o $(OBJ_LIB_FILES) -o client.aut -lncurses -lm

# main: $(OBJ_LIB_FILES) main.o
# 	gcc main.o $(OBJ_LIB_FILES) -o main -lncurses

client.o: $(C_DIR)/client.c
	gcc $(C_DIR)/client.c -c -g -o $(C_DIR)/client.o

# # compare.o: compare.c
# # 	gcc compare.c -c -g

$(C_LIB_DIR)/%.o: $(C_LIB_DIR)/%.c
	gcc -c -o $@ $< -g3

clean:
	rm -rf *.o main $(bin_dir)/*.o 

delo:
	rm -rf *.o $(bin_dir)/*.o