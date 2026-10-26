CXX = g++
CXXFLAGS = -O2 -Wall -Wextra -std=c++17 -Iinclude

TARGET = output/main.exe

$(shell if not exist output mkdir output 2>nul)

all: $(TARGET)

$(TARGET): src/main.cpp src/AVLTree.cpp src/RBTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	del /f /q output\*.exe 2>nul || rm -f output/*.exe

test_avl: tests/test_avl.cpp src/AVLTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o output/test_avl.exe
	output/test_avl.exe

test_avl_remove: tests/test_avl_remove.cpp src/AVLTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o output/test_avl_remove.exe
	output/test_avl_remove.exe

test_rb: tests/test_rb.cpp src/RBTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o output/test_rb.exe
	output/test_rb.exe