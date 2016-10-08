
FLAGS = -g -Wall -pedantic -Wextra -std=c++11

all: clean lab8

lab8: Vertex.o City.o Graph.o lab8.o
	g++ $(FLAGS) Vertex.o City.o Graph.o lab8.o -o lab8

Vertex.o: Vertex.cpp Vertex.h
	g++ $(FLAGS) -c Vertex.cpp -o Vertex.o

City.o: City.cpp City.h
	g++ $(FLAGS) -c City.cpp -o City.o

Graph.o: Graph.cpp Graph.h
	g++ $(FLAGS) -c Graph.cpp -o Graph.o

lab8.o: lab8.cpp
	g++ $(FLAGS) -c lab8.cpp -o lab8.o

clean:
	rm -f *.o lab8
