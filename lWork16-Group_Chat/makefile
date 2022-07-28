C_DIR := ./client
S_DIR := ./server

C_LIB_DIR := $(C_DIR)/lib
S_LIB_DIR := $(S_DIR)/module

SRC_LIB_FILES := $(wildcard $(C_LIB_DIR)/*.c)
OBJ_LIB_FILES := $(patsubst $(C_LIB_DIR)/%.c, $(C_LIB_DIR)/%.o, $(SRC_LIB_FILES))

SRC_LIB_FILES_S := $(wildcard $(S_LIB_DIR)/*.c)
OBJ_LIB_FILES_S := $(patsubst $(S_LIB_DIR)/%.c, $(S_LIB_DIR)/%.o, $(SRC_LIB_FILES_S))

all: client server

client: $(OBJ_LIB_FILES) client.o 
	gcc $(C_DIR)/client.o $(OBJ_LIB_FILES) -o client.aut -lncurses -lm -O1 -lrt -pthread

server: $(OBJ_LIB_FILES_S) $(S_DIR)/server.c
	gcc $(S_DIR)/server.c $(OBJ_LIB_FILES_S) -o server.aut -lrt -pthread

client.o: $(C_DIR)/client.c
	gcc $(C_DIR)/client.c -c -g -o $(C_DIR)/client.o -O1

# # compare.o: compare.c
# # 	gcc compare.c -c -g

$(C_LIB_DIR)/%.o: $(C_LIB_DIR)/%.c
	gcc -c -o $@ $< -O1 -g3

$(S_LIB_DIR)/%.o: $(S_LIB_DIR)/%.c
	gcc -c -o $@ $< -O1 -g3

clean:
	rm -rf *.o main $(C_LIB_DIR)/*.o $(C_DIR)/*.o $(S_LIB_DIR)/*.o $(S_DIR)/*.o 

delo:
	rm -rf *.o $(bin_dir)/*.o