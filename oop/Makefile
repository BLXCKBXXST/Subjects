CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

.PHONY: all lab1 lab2 lab3 lab4 lab5 run1 run2 run3 run4 run5 clean

all: lab1 lab2 lab3 lab4 lab5

build:
	mkdir -p build

lab1: build
	$(CXX) $(CXXFLAGS) lab-01/variant-24/airport_basic.cpp -o build/lab1

lab2: build
	$(CXX) $(CXXFLAGS) lab-02/variant-24/main.cpp -o build/lab2

lab3: build
	$(CXX) $(CXXFLAGS) lab-03/variant-24/create.cpp -o build/create
	$(CXX) $(CXXFLAGS) lab-03/variant-24/process.cpp -o build/process

lab4: build
	$(CXX) $(CXXFLAGS) lab-04/main.cpp -o build/lab4

lab5: build
	$(CXX) $(CXXFLAGS) lab-05/variant-23/main.cpp -o build/lab5

run1: lab1
	./build/lab1

run2: lab2
	./build/lab2

run3: lab3
	cd lab-03/variant-24 && ../../build/create && ../../build/process

run4: lab4
	./build/lab4

run5: lab5
	./build/lab5

clean:
	rm -rf build
	rm -f lab-03/variant-24/tea.bin
