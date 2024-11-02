CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC_DIR = src/utils
OUT_DIR = src/class

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(SOURCES))

all: $(OUT_DIR)/main

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/main: $(OBJECTS) src/main.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) src/main.cpp -o $@

$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/*
