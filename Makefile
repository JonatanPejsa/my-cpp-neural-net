CXX = g++
CXXFLAGS = -Wall -pedantic

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main
