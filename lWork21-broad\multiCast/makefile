#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
MD := mkdir
RM := rm
CC := gcc

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
.PHONY: all clean title udp

all: tcp udp 

broad: broadcast_server.c broadcast_client.c
	gcc broadcast_server.c -o broadcast_server.out
	gcc broadcast_client.c -o broadcast_client.out

multi: bmulticast_server.c bmulticast_client.c
	gcc bmulticast_server.c -o bmulticast_server.out
	gcc bmulticast_client.c -o bmulticast_client.out

clean: 
	rm -rf *.out *.o
