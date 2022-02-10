all: main

main: main.o plug_worker.o
	gcc main.o plug_worker.o -o main -ldl

main.o: main.c
	gcc main.c -c -g

plug_worker.o: plug_worker.c lib_add.so lib_subtract.so
	gcc plug_worker.c -c

lib_add.so: ./bin/add.o
	gcc -shared ./bin/add.o -o ./bin/lib_add.so

./bin/add.o: ./bin/add.c
	gcc -fPIC ./bin/add.c -c -o ./bin/add.o

lib_subtract.so: ./bin/subtract.o
	gcc -shared ./bin/subtract.o -o ./bin/lib_subtract.so

./bin/subtract.o: ./bin/subtract.c
	gcc -fPIC ./bin/subtract.c -c -o ./bin/subtract.o

clean:
	rm -rf *.o main ./bin/*.o ./bin/*.so

