C_DIR := ./client
S_DIR := ./server

C_LIB_DIR := $(C_DIR)/lib
S_LIB_DIR := $(S_DIR)/module

SRC_CLIENT_LIB_F := $(wildcard $(C_LIB_DIR)/*/*.c)
OBJ_CLIENT_LIB_F := $(SRC_CLIENT_LIB_F:.c=.o)

SRC_SERVER_LIB_F := $(wildcard $(S_LIB_DIR)/*.c)
OBJ_SERVER_LIB_F := $(SRC_SERVER_LIB_F:.c=.o)

PARAMS := -lncurses -lrt -pthread -lm

all: client server

#------------------CLIENT------------------
client: $(OBJ_CLIENT_LIB_F) client.o 
	gcc $(C_DIR)/client.o $(OBJ_CLIENT_LIB_F) -o client.out $(PARAMS)

client.o: $(C_DIR)/client.c
	gcc $(C_DIR)/client.c -c -g -o $(C_DIR)/client.o -O1 

$(C_LIB_DIR)/*/%.o: $(C_LIB_DIR)/*/%.c
	gcc -c -o $@ $< -O1 -g3 
#------------------------------------------


#------------------SERVER------------------
server: $(OBJ_SERVER_LIB_F) server.o 
	gcc $(S_DIR)/server.o $(OBJ_SERVER_LIB_F) -o server.out $(PARAMS)

server.o: $(S_DIR)/server.c
	gcc $(S_DIR)/server.c -c -o $(S_DIR)/server.o -O1 -g3

$(S_LIB_DIR)/*/%.o: $(S_LIB_DIR)/*/%.c
	gcc $@ -c -o $< -O1 -g3 
#------------------------------------------


clean:
	rm -rf ./*/*.o $(OBJ_CLIENT_LIB_F) $(OBJ_SERVER_LIB_F) *.out






message:
	$(info $(SRC_CLIENT_LIB_F))
	$(info $(OBJ_CLIENT_LIB_F))
	$(info $(SUBDIR_C))
	$(info $(SUBDIR_O))
	$(info *****************************************)
	$(info *****************************************)

