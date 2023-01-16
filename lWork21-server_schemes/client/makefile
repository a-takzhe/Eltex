BLACK        := $(shell tput -Txterm setaf 0)
RED          := $(shell tput -Txterm setaf 1)
GREEN        := $(shell tput -Txterm setaf 2)
YELLOW       := $(shell tput -Txterm setaf 3)
LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
PURPLE       := $(shell tput -Txterm setaf 5)
BLUE         := $(shell tput -Txterm setaf 6)
WHITE        := $(shell tput -Txterm setaf 7)
RESET        := $(shell tput -Txterm sgr0)

# ifdef RELEASE 
#     C_MODE 	  := /release
# 	CC_FLAGS  := -Wall -O1
# else
#     C_MODE    := /debug
# 	CC_FLAGS  := -Wall -O1 -g3 
# endif

SRC_DIR     := ./src
OUT_O_DIR   := ./objs$(C_MODE)
OUTPUT_DIR  := ./bin$(C_MODE)

#---------------------------------------------------------------------
# settings
#---------------------------------------------------------------------
SOURCES_C = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(subst ./src,$(OUT_O_DIR),$(SOURCES_C:.c=.o))
BINS	  = $(subst ./src,$(OUTPUT_DIR),$(SOURCES_C:.c=.out))


CC_FLAGS  := -Wall -O1 -g3 
#CC_FLAGS  +=  

LCF_FLAGS := 

LD_FLAGS  := 

#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
MD := mkdir
RM := rm
CC := gcc

#---------------------------------------------------------------------
# rules
#---------------------------------------------------------------------
.PHONY: all clean

all: MD $(OBJS) $(BINS)
	bash ./deploy.sh $(BINS)
	@echo -n "${RESET}"

$(OUTPUT_DIR)/%.out: $(OUT_O_DIR)/%.o
	$(CC) -o $@ $< $(CC_FLAGS) $(LD_FLAGS)


$(OUT_O_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c -o $@ $< $(CC_FLAGS)

$(OUT_O_DIR)/%.o: $(SRC_DIR)/%.h
	gcc -c -o $@ $< $(CC_FLAGS)

MD:
	@echo -n "${YELLOW}"
	@echo "**************************************************"
	@echo "****************$(PROJ_NAME)**$(APP_NAME)****************"
	@echo "**************************************************"
	$(MD) -p $(OUTPUT_DIR)
	$(MD) -p $(OUT_O_DIR)

clean:
	$(RM) -rf $(OUT_O_DIR) $(OUTPUT_DIR)
