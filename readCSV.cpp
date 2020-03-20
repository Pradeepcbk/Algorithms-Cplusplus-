/**
* @section License
*
* The MIT License (MIT)
*
* Copyright (c) 2017, Pradeep Siddagangaiah
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without
* restriction, including without limitation the rights to use, copy,
* modify, merge, publish, distribute, sublicense, and/or sell copies
* of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
* BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
* ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

/**
Problem Statement: To read in a csv file containing data in the format ax,ay,az
*/

#include "stdafx.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

std::map<int, std::vector<double>> readCSV(std::ifstream& fin) {
	std::map<int, std::vector<double>> accelerationValues;
	// Check if it is not opened successfully
	if (!fin) {
		std::cout << "Error, could not open the file";
		std::vector<double> myVector = { INT_MAX };
		std::map<int, std::vector<double>> myMap;
		myMap.insert(std::pair<int, std::vector<double>>(0, myVector));
		return myMap;
	}
	std::string line;
	size_t pos;
	int rowCounter = 0;
	while (!fin.eof()) {
		std::vector<double> valuesVector;
		getline(fin, line);
		line += ",";
		while ((pos = line.find(",")) != std::string::npos) {
			std::string token = line.substr(0, pos);
			valuesVector.push_back(std::stod(token));
			line.erase(0, pos + 1);
		}
		accelerationValues.insert(std::pair<int, std::vector<double>>(rowCounter, valuesVector));
		rowCounter++;
	}
	return accelerationValues;
}

int main()
{
	// Open the inertial sensor measurement file
	std::ifstream fin;
	fin.open("data.csv");									// File to be opened
	std::map<int, std::vector<double>> accelerationData = readCSV(fin);
	if (accelerationData[0][0] == INT_MAX) {
		std::cout << "File reading unsuccessful \n";
	}
	else {
		std::cout << "File reading successful \n";
		std::cout << "Contents of the file in the format ax,ay,az\n";
		for (auto value : accelerationData) {
			std::cout << value.second[0] << "," << value.second[1] << "," << value.second[2] << std::endl;
		}
	}
    return 0;
}

/**
Sample input file will contain data of the format below:
0.947509765625,-0.6260833740234375,11.1258544921875
1.1061248779296875,-0.526123046875,11.4849853515625
1.12646484375,-0.4542999267578125,11.610076904296875
1.202484130859375,-0.462677001953125,11.66455078125
*/