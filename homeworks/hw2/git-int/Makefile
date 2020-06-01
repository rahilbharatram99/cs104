CXX = g++
CXXFLAGS = -g3 -O0 -Wall --std=c++11

all: gitint-shell

gitint-shell: gitint.cpp gitint-shell.cpp 
	$(CXX) $(CXXFLAGS) gitint.cpp gitint-shell.cpp -o gitint-shell

clean: 
	rm -rf gitint-shell
