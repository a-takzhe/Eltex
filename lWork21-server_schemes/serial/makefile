.PHONY: all server client cend

all: server client

server:
	cd ./server && make all APP_NAME=server --no-print-directory || cd ..
#./serial/bin/debug/server.out

client:
	cd ./client && make all APP_NAME=client --no-print-directory || cd ..



clean: clean_c clean_s

clean_s:
	cd ./server && make clean APP_NAME=server --no-print-directory || cd ..

clean_c:
	cd ./client && make clean APP_NAME=client --no-print-directory || cd ..