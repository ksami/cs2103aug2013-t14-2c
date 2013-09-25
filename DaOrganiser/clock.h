#pragma once

#include <iostream>
using namespace std;

class clockTime {
private:
	int _hour;
	int _min;
	bool _flagHour;
	bool _flagMin;
	
	bool checkValidHour(int);
	bool checkValidMin(int);
public:

	clockTime();
	~clockTime();
	void setHour(int hour);
	void setMin(int min);
	int getHour();
	int getMin();
	bool getHourStatus();
	bool getMinStatus();
};