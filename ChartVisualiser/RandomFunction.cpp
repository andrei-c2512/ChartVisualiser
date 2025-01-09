#include "RandomFunction.h"
#include <fstream>

std::ifstream file("FunctionExamples2.txt");
std::vector<std::string> functionList;
std::random_device rd;
std::mt19937 rng;
std::uniform_int_distribution<int> range;

void initRandomFunc() {
	rng = std::mt19937(rd());

	std::string ex;
	while (file >> ex) {
		functionList.emplace_back(ex);
	}

	range = std::uniform_int_distribution<int>(0, functionList.size() - 1);
	file.close();
}
std::string getRandomFunction() {
	return functionList[range(rng)];
}