CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude



SRC = src/memory.cpp \
      src/register.cpp \
      src/machine.cpp \
	  src/fetch.cpp \
	  src/decode.cpp \
	  src/elf_loader.cpp \
	  src/execute.cpp \
	  src/test_execute.cpp \
	
	
	 


OBJ = $(SRC:.cpp=.o)
TARGET = riscv_vm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
