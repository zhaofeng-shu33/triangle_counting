BUILD_DIR = ./build

.PHONY: all

all: $(BUILD_DIR)/test

$(BUILD_DIR): Makefile
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/counting.o: $(BUILD_DIR) counting.cpp 
	g++ -c counting.cpp -o $(BUILD_DIR)/counting.o

$(BUILD_DIR)/test.o: $(BUILD_DIR) test.cpp
	g++ -c test.cpp -o $(BUILD_DIR)/test.o

# we only use the header only feature of library lemon, no need to pass -llemon etc.
$(BUILD_DIR)/test: $(BUILD_DIR)/test.o $(BUILD_DIR)/counting.o
	g++ $(BUILD_DIR)/test.o $(BUILD_DIR)/counting.o -o $(BUILD_DIR)/test
