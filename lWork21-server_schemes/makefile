BLACK        := $(shell tput -Txterm setaf 0)
RED          := $(shell tput -Txterm setaf 1)
GREEN        := $(shell tput -Txterm setaf 2)
YELLOW       := $(shell tput -Txterm setaf 3)
LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
PURPLE       := $(shell tput -Txterm setaf 5)
BLUE         := $(shell tput -Txterm setaf 6)
WHITE        := $(shell tput -Txterm setaf 7)
RESET        := $(shell tput -Txterm sgr0)

#case ":$SERV_CHEMES" in *"thread"*) echo "exists";; *) echo "not exists";; esac

.PHONY: serial test client all

all: client test serial  

client:
	cd ./client && make all PROJ_NAME=client --no-print-directory || cd ..

test:
	cd ./test && make all PROJ_NAME=test --no-print-directory || cd ..

serial:
	cd ./serial_server && make all PROJ_NAME=serial --no-print-directory || cd ..