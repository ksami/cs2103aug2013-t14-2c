#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

#define TASK_STATUS_NOTDONE 'n'
#define TASK_STATUS_DONE 'd'
#define TASK_STATUS_APPROACHING 'a'
#define TASK_STATUS_MISSED 'm'
#define TASK_DATETIME_START 's'
#define TASK_DATETIME_END 'e'
#define TASK_KIND_TIMED 't'
#define TASK_KIND_DEADLINE 'd'
#define TASK_KIND_FLOATING 'f'

#define COMPARE_MORETHAN 1
#define COMPARE_LESSTHAN -1
#define COMPARE_EQUALTO 0

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

	string getDetailsAsString();
	string getEndDateAsString();
	string getEndDateTimeAsString();
	string getEndTimeAsString();
	string getIdAsString();
	string getKindAsString();
	string getStartDateAsString();
	string getStartDateTimeAsString();
	string getStartTimeAsString();
	string getStatusAsString();

	int getTaskID();
	char returnStatus();
	char returnKind();
	date returnDate(char);
	time_s returnTime(char);

	int checkDate(date, date);
	int checkTime(time_s, time_s);


	bool assignDateValue(date, char);
	void assignDetails(string);
	void assignIDNumber(int);
	bool assignKind(char);
	bool assignTimeValue(time_s, char);
	bool changeStatus(char);

	bool checkLeapYear(int);
};
