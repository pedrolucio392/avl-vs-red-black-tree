CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -Iinclude

TARGET = output/main.exe

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)

test_avl: tests/test_avl.cpp
	$(CXX) $(CXXFLAGS) tests/test_avl.cpp -o output/test_avl.exe
	output/test_avl.exe

test_avl_remove: tests/test_avl_remove.cpp
	$(CXX) $(CXXFLAGS) tests/test_avl_remove.cpp -o output/test_avl_remove.exe
	output/test_avl_remove.exe