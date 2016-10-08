//Brett Sackstein
#ifndef VERTEX
#define VERTEX

#include "City.h"
#include <string>

class Vertex{
	private:
		std::string name;
		City *adjList;

	public:
		Vertex(std::string name, City *cities);
		~Vertex();
		std::string getName();
		City* getCities();
		void setNextCity(City *nextCity);
};

#endif
