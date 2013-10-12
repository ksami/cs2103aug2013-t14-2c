#include "storage.h"

storage::~storage() {
	inputFile.close();
	fileVector.close();
}

void storage::checkStatusInputFile() {
	if (inputFile.is_open())
		cout<<"Input file opened successfully"<<endl;
	else
		cout<<"Error occured in input file"<<endl;
}		

void storage::checkStatusOutputFile() {
	if (fileVector.is_open())
		cout<<"Output file opened successfully"<<endl;
	else
		cout<<"Error occured in output file"<<endl;
}		

void storage::readFile() {
	string line;	
	while (getline(inputFile,line)) {
		temp.push_back(line);
	}
}

void storage::displayString() {
	while (!temp.empty()) {
		cout<<temp.back()<<endl;
		temp.pop_back();
	}
} //for testing

void storage::getVector() {
	//todo
	//get latest updated vector of task from the logic class
}

void storage::writeToFile(string task) {
	fileVector<<task<<endl;
}

