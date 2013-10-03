#include "date.h"

date::date() {
	_year=_month=_day=0;
}

date::~date() {
}

void date::setYear(int year) {
	_year=year;
}

void date::setMonth(int month) {
	_month=month;
}

void date::setDay(int day) {
	_day=day;
}

int date::getYear() {
	return _year;
}

int date::getMonth() {
	return _month;
}

int date::getDay() {
	return _day;
}