CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude



SRC = src/memory.cpp \
      src/register.cpp \
      src/machine.cpp \
	  src/elf_loader.cpp \
	  src/test_elf.cpp \


OBJ = $(SRC:.cpp=.o)
TARGET = riscv_vm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
