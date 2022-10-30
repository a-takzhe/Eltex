#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
MD := mkdir
RM := rm
CC := gcc

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
.PHONY: all clean title 

all: tcp udp 

tcp: server_tcp.c client_tcp.c
	gcc server_tcp.c -o server_tcp.out
	gcc client_tcp.c -o client_tcp.out

udp: server_udp.c client_udp.c
	gcc server_udp.c -o server_udp.out
	gcc client_udp.c -o client_udp.out

clean: 
	rm -rf *.out *.o
