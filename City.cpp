//Brett Sackstein
#include "City.h"

City::City(){
	vertexInd = -1;
	next = NULL;
}

City::City(int vIn, City *otherCity){
	vertexInd = vIn;
	next = otherCity;
}

City::~City(){
	if(next != NULL)
		delete next;
}

int City::getVertexInd(){
	return vertexInd;
}

City* City::getNextCity(){
	return next;
}

bool City::operator=(City* otherCity){
	if(this->getVertexInd() == otherCity->getVertexInd())
		return true;
	else
		return false;
}

bool City::operator!=(City* otherCity){
	if(this->getVertexInd() != otherCity->getVertexInd())
		return true;
	else
		return false;
}
