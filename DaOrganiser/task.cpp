#include "task.h"

task::task() {
}

task::~task() {
}

task::task(date Date,clockTime Clock) {
	_endDate.setYear(Date.getYear());
	_endDate.setMonth(Date.getMonth());
	_endDate.setDay(Date.getDay());
	_endTime.setHour(Clock.getHour());
	_endTime.setMin(Clock.getMin());
}

task::task(date startDate, date endDate, clockTime startTime, clockTime endTime) {
	_startDate.setYear(startDate.getYear());
	_startDate.setMonth(startDate.getMonth());
	_startDate.setDay(startDate.getDay());
	_startTime.setHour(startTime.getHour());
	_startTime.setMin(startTime.getMin());
	_endDate.setYear(endDate.getYear());
	_endDate.setMonth(endDate.getMonth());
	_endDate.setDay(endDate.getDay());
	_endTime.setHour(endTime.getHour());
	_endTime.setMin(endTime.getMin());
}

date task::getStartDate() {
	return _startDate;
}

date task::getEndDate() {
	return _endDate;
}

clockTime task::getStartTime() {
	return _startTime;
}

clockTime task::getEndTime() {
	return _endTime;
}

void task::printTask() {
	cout<<setw(2)<<setfill('0')<<_endDate.getYear()<<"/"<<_endDate.getMonth()<<"/"<<_endDate.getDay()<<" "<<setw(2)<<setfill('0')<<_endTime.getHour()<<":"<<setw(2)<<setfill('0')<<_endTime.getMin()<<endl;
}