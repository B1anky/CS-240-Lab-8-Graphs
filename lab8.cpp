//Brett Sackstein
#include "Vertex.h"
#include "City.h"
#include "Graph.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::string> parseInput(std::string fileName);
void flightDirectory(Graph *flightGraph, unsigned int num, std::string *cityList);
std::vector<std::string> splitInput(std::string toParse);

int main (int argc, char** argv){
	bool fileset = false;
	std::string filename = "";
	std::stringstream str1;
	std::vector<std::string> inputInfo;
	std::string *vertexes;
	std::string *flights;

	// Parse input and fill files;
	switch(argc){
		case 2: 
			fileset = true;
			filename = argv[1];
			break;
		default:
			exit(0);
	}

	//Pipes file in if file was specified in command line
	if(fileset){
		inputInfo = parseInput(filename);
	}

	unsigned int cityCnt = atoi(inputInfo[0].c_str());
	unsigned int flightCnt = atoi(inputInfo[cityCnt + 1].c_str());
	vertexes = new std::string[cityCnt];
	flights = new std::string[flightCnt];

	//Splits up the two sections of the input into seperate arrays
	for(unsigned int i = 1; i < cityCnt + 1; i++)
		vertexes[i - 1] = inputInfo[i];

	for(unsigned int i = cityCnt + 2; i < flightCnt + cityCnt + 2; i++)
		flights[i - cityCnt - 2] = inputInfo[i];

	Graph *flightGraph = new Graph(cityCnt, flightCnt, vertexes, flights);
	//flightGraph->showGraph();
	
	flightDirectory(flightGraph, flightCnt, vertexes);

	delete []vertexes;
	delete []flights;
	delete flightGraph;
	return 0;
}

std::vector<std::string> parseInput(std::string fileName){
	std::vector<std::string> inputInfo;
	std::ifstream infile(fileName);
	std::string line;

	while (std::getline(infile, line)){
		//Readline character and newline character parsing
		if(!line.empty() && (line[line.length()-1] == '\n' || line[line.length()-1] == '\r')){
			line.erase(line.length()-1);
		}
		//Add commands to a vector because won't know size
		//until run time
		inputInfo.push_back(line);
	}
	std::cout << "\033[1;32m**File has been loaded in**[0m" << std::endl;
	infile.close();

	return inputInfo;
}

void flightDirectory(Graph *flightGraph, unsigned int num, std::string *cityList){
	std::string choice("");
	bool keepGoing = true;
	std::vector<std::string> choiceSplit;
	while(keepGoing){
		std::cout << "\nEnter HOME <city name> or TRAVEL <city 1> <city 2> or QUIT: ";
		getline(std::cin, choice);
		choiceSplit = splitInput(choice);
		if(choiceSplit[0] == "HOME"){
			if(choiceSplit.size() == 2){
				for(unsigned int i = 0; i < num; i++){
					if(choiceSplit[1] == cityList[i]){
						flightGraph->printHomeRoute(choiceSplit[1]);
						break;
					}
					if(i == num - 1)
						std::cerr << "\033[1;31m\nError. City is not in flight directory.[0m" << std::endl;
				}
			}else{
				std::cerr << "\033[1;31m\nError. Incorrect input. Please enter one destination city.[0m" << std::endl;
			}
		}else if(choiceSplit[0] == "TRAVEL"){
			if(choiceSplit.size() == 3){
				flightGraph->printTravelRoute(choiceSplit[1], choiceSplit[2], false);
			}else{
				std::cerr << "\033[1;31m\nError. Incorrect input. Please enter two destination cities.[0m" << std::endl;
			}

		}else if(choice == "QUIT"){
			keepGoing = false;
		}else{
			std::cerr << "\033[1;31m\nError. Please enter one of the correct commands.[0m" << std::endl;
		}
	}	
}

std::vector<std::string> splitInput(std::string toParse){
	std::string buf;
	std::stringstream ss(toParse);
	std::vector<std::string> splitInput;
	while(ss >> buf)
		splitInput.push_back(buf);
	return splitInput;
}

