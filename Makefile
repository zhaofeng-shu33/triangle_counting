# deprecated
BUILD_DIR = ./build

.PHONY: all

all: $(BUILD_DIR)/test

$(BUILD_DIR): Makefile
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/counting.o: $(BUILD_DIR) counting.cpp 
	g++ -std=gnu++11 -c counting.cpp -o $(BUILD_DIR)/counting.o

$(BUILD_DIR)/test.o: $(BUILD_DIR) test.cpp
	g++ -std=gnu++11 -c test.cpp -o $(BUILD_DIR)/test.o


$(BUILD_DIR)/io.o: $(BUILD_DIR) io.cpp
	g++ -std=gnu++11 -c io.cpp -o $(BUILD_DIR)/io.o

# we only use the header only feature of library lemon, no need to pass -llemon etc.
$(BUILD_DIR)/test_alg: $(BUILD_DIR)/test.o $(BUILD_DIR)/counting.o $(BUILD_DIR)/io.o
	g++ $(BUILD_DIR)/test.o $(BUILD_DIR)/counting.o $(BUILD_DIR)/io.o -o $(BUILD_DIR)/test_alg
