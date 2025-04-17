CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
LIBS = -lncurses

all: game

game: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o ascii-runner $(LIBS)

clean:
	rm -f game