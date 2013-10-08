#pragma once

#include <string>
#include <iostream>

using namespace std;

const char notDone = 'n';
const char done = 'd';
const char yes = 'y';
const char start = 's';
const char end = 'e';
const char timed = 't';
const char deadline = 'd';
const char floating = 'f';

const int moreThan = 1;
const int lessThan = -1;
const int equalTo = 0;
const int one = 1;
const int zero = 0;

struct date
{
	int day, month, year;
};

struct time
{
	int hr, min;
};


class task
{
private:

	date startDate, endDate;
	time startTime, endTime;
	string details;
	char status, kind;
public:
	task();
	int checkDate(date, date);
	int checkTime(time, time);
	char checkStatus();
	char returnKind();
	void changeStatus(char);
	bool assignDateValue(date, char);
	bool assignTimeValue(time, char);
	bool assignKind(char);
	void assignDetails(string);
	void displayDetail();
};