C_DIR := ./client
S_DIR := ./server
COM_DIR := ./common

C_LIB_DIR := $(C_DIR)/lib
S_LIB_DIR := $(S_DIR)/module

SRC_COM := $(wildcard $(COM_DIR)/*.c)
OBJ_COM := $(SRC_COM:.c=.o)

SRC_CLIENT_LIB_F := $(wildcard $(C_LIB_DIR)/*/*.c)
OBJ_CLIENT_LIB_F := $(SRC_CLIENT_LIB_F:.c=.o)

SRC_SERVER_LIB_F := $(wildcard $(S_LIB_DIR)/*.c)
OBJ_SERVER_LIB_F := $(SRC_SERVER_LIB_F:.c=.o)

CC_FLAGS    := -Wall -g3
LD_FLAGS 	:= -L. -lcommon -lncurses -lrt -lpthread -lm
#PARAMS := -lncurses -lrt -lpthread -lm

all: common client server
	@mkdir -p ./semaphores

#------------------CLIENT------------------
common: $(OBJ_COM)
	ar rc libcommon.a $(OBJ_COM)

$(COM_DIR)/%.o: $(COM_DIR)/%.c
	gcc -c -o $@ $< -lrt -g3  
#rpath=/usr/lib/x86_64-linux-gnu/librt.a

#------------------------------------------


#------------------CLIENT------------------
client: $(OBJ_CLIENT_LIB_F) client.o 
	gcc $(C_DIR)/client.o $(OBJ_CLIENT_LIB_F) -o client.out $(CC_FLAGS) $(LD_FLAGS)

client.o: $(C_DIR)/client.c
	gcc $(C_DIR)/client.c -c -g -o $(C_DIR)/client.o -O1 

$(C_LIB_DIR)/*/%.o: $(C_LIB_DIR)/*/%.c
	gcc -c -o $@ $< -O1 -g3 
#------------------------------------------


#------------------SERVER------------------
server: common $(OBJ_SERVER_LIB_F) server.o
	gcc $(S_DIR)/server.o $(OBJ_SERVER_LIB_F) -o server.out $(CC_FLAGS) $(LD_FLAGS) 
	@mkdir -p ./semaphores

server.o: $(S_DIR)/server.c
	gcc $(S_DIR)/server.c -c -o $(S_DIR)/server.o -O1 -g3

$(S_LIB_DIR)/%.o: $(S_LIB_DIR)/%.c
		gcc -c -o $@ $< -g3 
# ------------------------------------------

clean:
	rm -rf ./*/*.o $(OBJ_CLIENT_LIB_F) $(OBJ_SERVER_LIB_F) *.out ./semaphores ./*.a



message:
	$(info $(SRC_CLIENT_LIB_F))
	$(info $(OBJ_CLIENT_LIB_F))
	$(info $(SUBDIR_C))
	$(info $(SUBDIR_O))
	$(info *****************************************)
	$(info *****************************************)

