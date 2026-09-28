CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -Wextra -g -MMD -MP
TARGET    := campusguard
SOURCES   := $(wildcard *.cpp)
OBJECTS   := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(TARGET)

-include $(OBJECTS:.o=.d)

.PHONY: all run valgrind clean