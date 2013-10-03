#include "clock.h"

clockTime::clockTime() {
	_hour=_min=0;
	_flagHour=_flagMin=false;
}

clockTime::~clockTime() {
}

void clockTime::setHour(int hour) {
	if (checkValidHour(hour)) {
		_hour=hour;
		_flagHour=true;
	}
	else {
		_flagHour=false;
		cout<<"Invalid hour entered"<<endl;
	}
}

void clockTime::setMin(int min) {
	if (checkValidMin(min)) {
		_min=min;
		_flagMin=true;
	}
	else {
		_flagMin=false;
		cout<<"Invalid minute entered"<<endl;
	}
}

int clockTime::getHour() {
	return _hour;
}

int clockTime::getMin() {
	return _min;
}

bool clockTime::checkValidHour(int hour) {
	if (hour<0||hour>23)
		return false;
	else 
		return true;
}

bool clockTime::checkValidMin(int min) {
	if (min<0||min>59)
		return false;
	else 
		return true;
}

bool clockTime::getHourStatus() {
	return _flagHour;
}

bool clockTime::getMinStatus() {
	return _flagMin;
}