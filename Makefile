# deprecated
BUILD_DIR = ./build

.PHONY: all

all: $(BUILD_DIR)/main

$(BUILD_DIR): Makefile
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/counting.o: $(BUILD_DIR) counting.cpp 
	g++ -I./ -fopenmp -std=gnu++11 -c counting.cpp -o $(BUILD_DIR)/counting.o

$(BUILD_DIR)/competition.o: $(BUILD_DIR) competition.cpp
	g++ -I./ -fopenmp -std=gnu++11 -c competition.cpp -o $(BUILD_DIR)/competition.o


$(BUILD_DIR)/io.o: $(BUILD_DIR) io.cpp
	g++ -I./ -fopenmp -std=gnu++11 -c io.cpp -o $(BUILD_DIR)/io.o

# we only use the header only feature of library lemon, no need to pass -llemon etc.
$(BUILD_DIR)/main: $(BUILD_DIR)/competition.o $(BUILD_DIR)/counting.o $(BUILD_DIR)/io.o
	g++ -I./ -fopenmp $(BUILD_DIR)/competition.o $(BUILD_DIR)/counting.o $(BUILD_DIR)/io.o -o $(BUILD_DIR)/main
