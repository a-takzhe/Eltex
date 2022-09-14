#---------------------------------------------------------------------
# Common dirs, names, files
#---------------------------------------------------------------------
COM_DIR := ./common
SRC_COM := $(wildcard $(COM_DIR)/*.c)
OBJ_COM := $(SRC_COM:.c=.o)


#---------------------------------------------------------------------
# Clients dirs, names, files
#---------------------------------------------------------------------
CLIENT_DIR := ./client
CLIENT_LIB_DIR := $(CLIENT_DIR)/lib

CLIENT_SRC := $(wildcard $(CLIENT_DIR)/*.c)
CLIENT_LIB_SRC := $(wildcard $(CLIENT_LIB_DIR)/*/*.c)

CLIENT_OBJ :=  $(CLIENT_SRC:.c=.o)
CLIENT_LIB_OBJ := $(CLIENT_LIB_SRC:.c=.o)


#---------------------------------------------------------------------
# Server dirs, names, files
#---------------------------------------------------------------------
SERVER_DIR := ./server
SERVER_LIB_DIR := $(SERVER_DIR)/module

SERVER_SRC := $(wildcard $(SERVER_DIR)/*.c)
SERVER_LIB_SRC := $(wildcard $(SERVER_LIB_DIR)/*.c)

SERVER_OBJ := $(SERVER_SRC:.c=.o)
SERVER_LIB_OBJ := $(SERVER_LIB_SRC:.c=.o)


#---------------------------------------------------------------------
# Compiles settings
#---------------------------------------------------------------------
CC_FLAGS := -O1 -Wall -g3
LD_FLAGS := -L. -lcommon -lncurses -lrt -lpthread -lm



all: common client server
	@mkdir -p ./semaphores


#------------------COMMON LIBRARY-------------------------------------
common: lib_msg $(OBJ_COM)
	ar rc libcommon.a $(OBJ_COM)

$(COM_DIR)/%.o: $(COM_DIR)/%.c
	gcc -c -o $@ $< -lrt -g3  

lib_msg:
	$(info *****************************************)
	$(info ********Build common LIB*****************)
	$(info *****************************************)
#---------------------------------------------------------------------


#------------------CLIENT---------------------------------------------
client: cli_msg $(CLIENT_LIB_OBJ) $(CLIENT_OBJ)
	gcc $(CLIENT_OBJ) $(CLIENT_LIB_OBJ) -o client.out $(CC_FLAGS) $(LD_FLAGS)

$(CLIENT_DIR)/%.o: $(CLIENT_DIR)/%.c
	gcc -c -o $@ $< $(CC_FLAGS)

$(CLIENT_LIB_DIR)/%.o: $(CLIENT_LIB_DIR)/%.c
	gcc -c -o $@ $< $(CC_FLAGS) 

cli_msg:
	$(info *****************************************)
	$(info ********Build Client app*****************)
	$(info *****************************************)
#---------------------------------------------------------------------


#------------------SERVER---------------------------------------------
server: srv_msg $(SERVER_LIB_OBJ) $(SERVER_OBJ)
	gcc $(SERVER_OBJ) $(SERVER_LIB_OBJ) -o server.out $(CC_FLAGS) $(LD_FLAGS) 

$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.c
	gcc -c -o $@ $< $(CC_FLAGS)

$(SERVER_LIB_DIR)/%.o: $(SERVER_LIB_DIR)/%.c
		gcc -c -o $@ $< $(CC_FLAGS)

srv_msg:
	$(info *****************************************)
	$(info ********Build Server app*****************)
	$(info *****************************************)
# #---------------------------------------------------------------------

clean:
	rm -rf $(CLIENT_LIB_OBJ) 
	rm -rf $(CLIENT_OBJ) 
	rm -rf $(SERVER_LIB_OBJ)
	rm -rf $(SERVER_OBJ)
	rm -rf $(OBJ_COM)
	rm -rf *.out ./semaphores ./*.a
	bash ./kill_ipc.sh
