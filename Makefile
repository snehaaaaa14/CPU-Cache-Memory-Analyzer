CXX = g++

CXXFLAGS = -O2 -std=c++17 -Wall -Wextra

TARGET = cache_analyzer
SOURCE = src/main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
