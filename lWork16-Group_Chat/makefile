C_DIR := ./client
S_DIR := ./server

C_LIB_DIR := $(C_DIR)/lib
S_LIB_DIR := $(C_DIR)/lib

SRC_LIB_FILES := $(wildcard $(C_LIB_DIR)/*.c)
OBJ_LIB_FILES := $(patsubst $(C_LIB_DIR)/%.c, $(C_LIB_DIR)/%.o, $(SRC_LIB_FILES))

#LIB_PLUG_FILES := $(patsubst $(bin_dir)/%.c, $(bin_dir)/%.so, $(SRC_PLUG_FILES))

all: client server

client: $(OBJ_LIB_FILES) client.o 
	gcc $(C_DIR)/client.o $(OBJ_LIB_FILES) -o client.aut -lncurses -lm -O1 -lrt

server: $(S_DIR)/server.c
	gcc $(S_DIR)/server.c -o server.aut -lrt

client.o: $(C_DIR)/client.c
	gcc $(C_DIR)/client.c -c -g -o $(C_DIR)/client.o -O1

# # compare.o: compare.c
# # 	gcc compare.c -c -g

$(C_LIB_DIR)/%.o: $(C_LIB_DIR)/%.c
	gcc -c -o $@ $< -O1 -g3

clean:
	rm -rf *.o main $(C_LIB_DIR)/*.o $(C_DIR)/*.o 

delo:
	rm -rf *.o $(bin_dir)/*.o