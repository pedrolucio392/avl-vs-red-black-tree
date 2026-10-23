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

test_avl: tests/test_avl.cpp src/AVLTree.cpp
	$(CXX) $(CXXFLAGS) tests/test_avl.cpp src/AVLTree.cpp -o output/test_avl.exe
	output/test_avl.exe

test_avl_remove: tests/test_avl_remove.cpp src/AVLTree.cpp
	$(CXX) $(CXXFLAGS) tests/test_avl_remove.cpp src/AVLTree.cpp -o test_avl_remove.exe
	output/test_avl_remove.exe

test_rb: tests/test_rb.cpp src/RBTree.cpp
	$(CXX) $(CXXFLAGS) tests/test_rb.cpp src/RBTree.cpp -o output/test_rb.exe
	output/test_rb.exe