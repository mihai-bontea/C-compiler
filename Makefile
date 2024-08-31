CXX = g++
CXXFLAGS = -Wall -g

TARGET = compiler

OBJS = compiler.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

compiler.o: compiler.cpp Token.hpp
	$(CXX) $(CXXFLAGS) -c compiler.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean all

