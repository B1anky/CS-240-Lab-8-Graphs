//Brett Sackstein
#include "Vertex.h"

Vertex::Vertex(std::string nameIn, City *cities){
	name = nameIn;
	adjList = cities;
}

Vertex::~Vertex(){
	delete(adjList);
}

std::string Vertex::getName(){
	return name;
}

City* Vertex::getCities(){
	return adjList;
}

void Vertex::setNextCity(City *nextCity){
	adjList = nextCity;
}
