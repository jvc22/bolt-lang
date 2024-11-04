TARGET = program

CXX = g++
CXXFLAGS = -std=c++11 -Wall

SOURCES = $(shell find . -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
