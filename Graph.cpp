//Brett Sackstein
#include "Graph.h"

Graph::Graph(unsigned int cityCnt, unsigned int flightCnt, std::string *vertexes, std::string *flights){
	for(unsigned int i = 0; i < cityCnt; i++){
		adjLists.push_back(new Vertex(vertexes[i], NULL));
	}
	for(unsigned int j = 0; j < flightCnt; j++){
		std::vector<std::string> toIndex = split(flights[j]);
		int v1 = indexForName(toIndex[0]);
		int v2 = indexForName(toIndex[1]);
		adjLists[v1]->setNextCity(new City(v2, adjLists[v1]->getCities()));
	}
	setVisited(cityCnt);
}

Graph::~Graph(){
	for(unsigned int i = 0; i < adjLists.size(); i++){
		delete(adjLists[i]);
	}
	if(visited != NULL)
		delete []visited;
}

void Graph::setVisited(int cityCnt){
	visited = new int[cityCnt];
}

std::vector<Vertex*> Graph::getAdjList(){
	return adjLists;
}

int Graph::indexForName(std::string name){
	for(unsigned int i = 0; i < adjLists.size(); i++) {
		if(adjLists[i]->getName() == name){
			return i;
		}
	}
	return -1;
}

void Graph::showGraph(){
	for(unsigned int i = 0; i < adjLists.size(); i++){
		for(City *city = adjLists[i]->getCities(); city != NULL; city = city->getNextCity()){
			std::cout << adjLists[i]->getName() << " --> " << adjLists[city->getVertexInd()]->getName();
			if(city->getNextCity() != NULL)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}
}

std::vector<std::string> Graph::split(std::string toParse){
	std::string buf;
	std::stringstream ss(toParse);
	std::vector<std::string> places;
	while(ss >> buf)
		places.push_back(buf);
	return places;
}

void Graph::printHomeRoute(std::string home){
	printTravelRoute(home, "", true);
}

void Graph::printTravelRoute(std::string from, std::string to, bool home){
	std::vector<int> vertexRoute;
	if(from == to){
		printHomeRoute(from);
		return;
	}else{
		vertexRoute = DFST(indexForName(from), indexForName(to), vertexRoute, home);
	}
		std::cout << std::endl;
	if(vertexRoute.size() != 0){
		for (unsigned int i = 0; i < vertexRoute.size(); ++i){
			std::cout << getAdjList()[vertexRoute[i]]->getName() << " ";
		}
		std::cout << std::endl;
	}
	else{
		std::cout << "No" <<  std::endl;
	}	
}

std::vector<int> Graph::DFST(int start, int end, std::vector<int> &vertexRoute, bool home){
	if(end == -1 && home){
		vertexRoute.push_back(start);
		int i = 0;
		std::vector<int> sol;
		City *p = getAdjList()[start]->getCities();
		while(p != NULL){
			i = p->getVertexInd();	
			sol = DFST(i, start, vertexRoute, false);
			if(sol.size() != 0){
				return sol;
			}else{
				vertexRoute.clear();
				vertexRoute.push_back(start);
			}
			p = p->getNextCity();
		}
		return {};	
	}else{
		for(unsigned int i = 0; i < getAdjList().size(); i++)
			visited[i] = 0;
		bool a = DFST1(start, end, vertexRoute);
		if(a)
			return vertexRoute;
		else
			return {};
	}
}

bool Graph::DFST1(int i, int stop, std::vector<int> &vertexRoute){		
	vertexRoute.push_back(i);
	if(i == stop){
		return true;
	}
	City *p = getAdjList()[i]->getCities();
	visited[i] = 1;	
	while(p != NULL){
		i = p->getVertexInd();
		if(!visited[i]){
			auto before = vertexRoute;
			bool found = DFST1(i, stop, vertexRoute);
			if(!found){
				vertexRoute = before;
			}else{
				return true;
			}
		}
		p=p->getNextCity();
	}
	return false;
}
