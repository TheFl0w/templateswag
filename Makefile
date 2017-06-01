SRC := main.cpp
OBJ := $(SRC:.cpp=.o)
DEP := $(SRC:.cpp=.d)
TARGET := app
CXX := clang++
CXXFLAGS := -std=c++14 -MMD -Wall -Wextra

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJ) $(DEP)

.PHONY: all clean 

-include $(DEP)