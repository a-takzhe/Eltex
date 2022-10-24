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

all: main 

main: server.c client.c
	gcc server.c -o server.out
	gcc client.c -o client.out

main1: server1.c client1.c
	gcc server1.c -o server1.out
	gcc client1.c -o client1.out

clean: 
	rm -rf *.out *.o
