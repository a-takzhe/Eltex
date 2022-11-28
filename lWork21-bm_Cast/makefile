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

broad: bcast_server.c bcast_client.c
	gcc bcast_server.c -o bcast_server.out
	gcc bcast_client.c -o bcast_client.out

multi: mcast_sender.c mcast_reciever.c
	gcc mcast_sender.c -o mcast_sender.out
	gcc mcast_reciever.c -o mcast_reciever.out

clean: 
	rm -rf *.out *.o
