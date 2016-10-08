//Brett Sackstein
#ifndef CITY
#define CITY
#include <string>

class City{
	private:
		int vertexInd;		
		City *next;

	public:
		City();
		City(int vertexInd, City *otherCity);
		~City();
		int getVertexInd();
		City* getNextCity();
		bool operator=(City* otherCity);
		bool operator!=(City* otherCity);
	
};

#endif
