BIN_DIR=bin
BUILD_DIR=build
INCLUDE_DIR=include
SRC_DIR=src

CFLAGS=-Wall -O -g

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

.PHONY: all
all: $(BIN_DIR)/main

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*
	rm -f $(BUILD_DIR)/*.o


$(BIN_DIR)/main: $(OBJECTS)
	gcc $(CFLAGS) -o $(BIN_DIR)/main $(OBJECTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $(SRC_DIR)/$*.c -o $(BUILD_DIR)/$*.o
