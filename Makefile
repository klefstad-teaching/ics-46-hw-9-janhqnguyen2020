CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic

all: main

#main: src/dijkstras_main.cpp lib/dijkstras.o src/dijkstras.h
#	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp -o dijkstras_main lib/dijkstras.o src/dijkstras.h

#lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h
#	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o lib/dijkstras.o
	
main: src/ladder_main.cpp lib/ladder.o src/ladder.h
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp -o ladder_main lib/ladder.o src/ladder.h

lib/ladder.o: src/ladder.cpp src/ladder.h
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o lib/ladder.o

clean:
	rm -f lib/*.o main