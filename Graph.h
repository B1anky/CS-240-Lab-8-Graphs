//Brett Sackstein
#ifndef GRAPH
#define GRAPH

#include "City.h"
#include "Vertex.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Graph{
	public:
		Graph(unsigned int cityCnt, unsigned int flightCnt, std::string *vertexes, std::string *flights);
		~Graph();
		int indexForName(std::string name);
		void showGraph();
		void printHomeRoute(std::string home);
		void printTravelRoute(std::string from, std::string to, bool home);
		std::vector<Vertex*> getAdjList();
		void setVisited(int num);

	private:
		std::vector<Vertex*> adjLists;
		std::vector<std::string> split(std::string toParse);
		int *visited;
		std::vector<int> DFST(int start, int end, std::vector<int> &vertexRoute, bool home);
		bool DFST1(int i, int stop, std::vector<int> &vertexRoute);
};

#endif

