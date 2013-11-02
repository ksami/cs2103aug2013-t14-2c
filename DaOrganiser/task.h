#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <assert.h>
using namespace std;

const char notDone = 'n';
const char done = 'd';
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

struct time_s
{
	int hr, min;
};


class Task
{
private:
	int taskID;
	date startDate, endDate;
	time_s startTime, endTime;
	string details;
	char status, kind;
public:
	Task();

	string getIdAsString();
	string getStartDateTimeAsString();
	string getEndDateTimeAsString();
	string getStartDateAsString();
	string getEndDateAsString();
	string getStartTimeAsString();
	string getEndTimeAsString();
	string getDetailsAsString();
	string getStatusAsString();
	string getKindAsString();

	int checkDate(date, date);
	int checkTime(time_s, time_s);
	char checkStatus();
	char returnKind();
	date returnDate(char);
    time_s returnTime(char);
	bool changeStatus(char);
	bool assignDateValue(date, char);
	bool assignTimeValue(time_s, char);
	bool assignKind(char);
	void assignDetails(string);
	void assignIDNumber(int);
	void displayDetail();
	int getTaskID();
};
