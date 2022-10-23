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

main: some_proc.c killer.c
	gcc some_proc.c -o some_proc.out
	gcc killer.c -o killer.out

clean: 
	rm -rf *.out *.o
