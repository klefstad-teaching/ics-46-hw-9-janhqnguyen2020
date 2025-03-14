CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: main

main: src/dijkstras_main.cpp lib/dijkstras.o src/dijkstras.h
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp -o dijkstras_main lib/dijkstras.o src/dijkstras.h

lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o lib/dijkstras.o
	
clean:
	rm -f lib/*.o main