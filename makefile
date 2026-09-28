CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = campuseguard
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBEJCTS) $(TARGET)