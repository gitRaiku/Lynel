all: build

.PHONY: build run debug clean remove tar

TARGET   = mcp
SRC_DIR  = src
OBJ_DIR  = .obj
BIN_DIR  = bin

CC       = gcc
CCFLAGS  = -ggdb3 -Og \
					 -Wall -march=native -mtune=native -fmodulo-sched \
					 -fstack-clash-protection -pthread -pipe \
					 -D_FORTIFY_SOURCE=2 \
					 -I/usr/include/hidapi

LFLAGS   = -lhidapi-libusb

LINKER   = $(CC)

DEBUGGER = gdb -q
VALGRIND = valgrind --leak-check=summary --log-file=valgrind.log

DATE := $(shell date "+%Y-%m-%d")

C_SRC = $(wildcard $(SRC_DIR)/*.c)
C_OBJ = $(C_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

build: $(BIN_DIR) $(BIN_DIR)/$(TARGET)

$(BIN_DIR):
	mkdir -p $@

$(C_OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CCFLAGS) $< -o $@

$(BIN_DIR)/$(TARGET): $(C_OBJ)
	$(LINKER) $(C_OBJ) $(LFLAGS) -o $@

run: build
	./$(BIN_DIR)/$(TARGET)

valgrind: build
	$(VALGRIND) $(BIN_DIR)/$(TARGET)

debug: build
	$(DEBUGGER) $(BIN_DIR)/$(TARGET)

clean:
	rm -f $(C_OBJ)

remove: clean
	rm -f $(BIN_DIR)/$(TARGET)
