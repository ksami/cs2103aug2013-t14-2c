#include "stdafx.h"
#include "Task.h"

Task::Task()
{
	status = TASK_STATUS_NOTDONE;
	kind = TASK_KIND_FLOATING;
	details = "";

	startDate.day = startDate.month = startDate.year = 0;
	endDate.day = endDate.month = endDate.year = 0;
	startTime.hr = startTime.min = 0;
	endTime.hr = endTime.min = 0;
}

string Task::getIdAsString()
{
	return std::to_string(taskID);
}

// Returns startdate as dd/mm/yy
string Task::getStartDateAsString()
{
	string startDateAsString;

	if(startDate.day<=9)
	{
		startDateAsString += '0';
	}
	startDateAsString += std::to_string(startDate.day);
	startDateAsString += "/";

	if(startDate.month<=9)
	{
		startDateAsString += '0';
	}
	startDateAsString += std::to_string(startDate.month);
	startDateAsString += "/";

	if(startDate.year<=9)
	{
		startDateAsString += '0';
	}
	startDateAsString += std::to_string(startDate.year);

	return startDateAsString;
}

// Returns starttime as hh:mm
string Task::getStartTimeAsString()
{
	string startTimeAsString;

	if(startTime.hr<=9)
	{
		startTimeAsString += '0';
	}
	startTimeAsString += std::to_string(startTime.hr);
	startTimeAsString += ":";

	if(startTime.min<=9)
	{
		startTimeAsString += '0';
	}
	startTimeAsString += std::to_string(startTime.min);

	return startTimeAsString;
}

// Returns enddate as dd/mm/yy
string Task::getEndDateAsString()
{
	string endDateAsString;

	if(endDate.day<=9)
	{
		endDateAsString += '0';
	}
	endDateAsString += std::to_string(endDate.day);
	endDateAsString += "/";

	if(endDate.month<=9)
	{
		endDateAsString += '0';
	}
	endDateAsString += std::to_string(endDate.month);
	endDateAsString += "/";

	if(endDate.year<=9)
	{
		endDateAsString += '0';
	}
	endDateAsString += std::to_string(endDate.year);

	return endDateAsString;
}

// Returns endtime as hh:mm
string Task::getEndTimeAsString()
{
	string endTimeAsString;

	if(endTime.hr<=9)
	{
		endTimeAsString += '0';
	}
	endTimeAsString += std::to_string(endTime.hr);
	endTimeAsString += ":";

	if(endTime.min<=9)
	{
		endTimeAsString += '0';
	}
	endTimeAsString += std::to_string(endTime.min);

	return endTimeAsString;
}

// Returns startdatetime as dd/mm/yy hh:mm
string Task::getStartDateTimeAsString()
{	
	return getStartDateAsString() + " " + getStartTimeAsString();
}

// Returns enddatetime as dd/mm/yy hh:mm
string Task::getEndDateTimeAsString()
{
	return getEndDateAsString() + " " + getEndTimeAsString();
}

string Task::getDetailsAsString()
{
	return details;
}

string Task::getStatusAsString()
{
	string statusAsString;
	switch(status)
	{
	case TASK_STATUS_NOTDONE: statusAsString = "Not done"; break;
	case TASK_STATUS_DONE: statusAsString = "Done"; break;
	case TASK_STATUS_APPROACHING: statusAsString = "Approaching deadline"; break;
	case TASK_STATUS_MISSED: statusAsString = "Missed deadline"; break;
	}
	return statusAsString;
}

string Task::getKindAsString()
{
	string kindAsString;
	switch(kind)
	{
	case TASK_KIND_DEADLINE: kindAsString = "Deadline Task"; break;
	case TASK_KIND_FLOATING: kindAsString = "Floating Task"; break;
	case TASK_KIND_TIMED: kindAsString = "Timed Task"; break;
	}
	return kindAsString;
}

// Returns 1 if first is more than second, -1 if less, 0 if equal
int Task::checkDate(date first, date second)
{
	if(first.year>second.year)
		return COMPARE_MORETHAN;
	if(first.year<second.year)
		return COMPARE_LESSTHAN;
	if(first.month>second.month)
		return COMPARE_MORETHAN;
	if(first.month<second.month)
		return COMPARE_LESSTHAN;
	if(first.day>second.day)
		return COMPARE_MORETHAN;
	if(first.day<second.day)
		return COMPARE_LESSTHAN;

	return COMPARE_EQUALTO; 
}

// Returns 1 if first is more than second, -1 if less, 0 if equal
int Task::checkTime(time_s first, time_s second)
{
	if(first.hr>second.hr)
		return COMPARE_MORETHAN;
	if(first.hr<second.hr)
		return COMPARE_LESSTHAN;
	if(first.min>second.min)
		return COMPARE_MORETHAN;
	if(first.min<second.min)
		return COMPARE_LESSTHAN;

	return COMPARE_EQUALTO;
}

char Task::returnStatus()
{
	return status;
}

// Returns false if newStatus is invalid
bool Task::changeStatus(char newStatus)
{
	newStatus = tolower(newStatus);

	if (newStatus == TASK_STATUS_DONE)
		status = TASK_STATUS_DONE;
	else if(newStatus == TASK_STATUS_NOTDONE)
		status = TASK_STATUS_NOTDONE;
	else if(newStatus == TASK_STATUS_APPROACHING)
		status = TASK_STATUS_APPROACHING;
	else if(newStatus == TASK_STATUS_MISSED)
		status = TASK_STATUS_MISSED;
	else
		return false;

	return true;
}

// Returns false if newDate is invalid
bool Task::assignDateValue(date newDate, char dateOption)
{
	bool negativeDate = newDate.day<1||newDate.month<1||newDate.year<1;
	if(negativeDate)
		return false;

	switch(newDate.month)
	{
	case 1: if(newDate.day<=31) break; 
	case 2: if(newDate.day<=29) break;
	case 3: if(newDate.day<=31) break;
	case 4: if(newDate.day<=30) break;
	case 5: if(newDate.day<=31) break;
	case 6: if(newDate.day<=30) break;
	case 7: if(newDate.day<=31) break;
	case 8: if(newDate.day<=31) break;
	case 9: if(newDate.day<=30) break;
	case 10: if(newDate.day<=31) break;
	case 11: if(newDate.day<=30) break;
	case 12: if(newDate.day<=31) break;
	default: return false;
	}

	if(!checkLeapYear(newDate.year)&&newDate.month==2&&newDate.day==29) {
		return false;
	}

	if(dateOption==TASK_DATETIME_START)
		startDate = newDate;
	else
		endDate = newDate;

	return true;
}

// Returns false if newTime is invalid
bool Task::assignTimeValue(time_s newTime, char timeOption)
{
	if(newTime.hr>23||newTime.hr<0||newTime.min>59||newTime.min<0)
		return false;

	if(timeOption== TASK_DATETIME_START)
		startTime = newTime;
	else
		endTime = newTime;

	return true;
}

// Returns false if newKind is invalid
bool Task::assignKind(char newKind)
{
	newKind = tolower(newKind);
	bool validKind = (newKind == TASK_KIND_TIMED)||(newKind == TASK_KIND_DEADLINE)||(newKind == TASK_KIND_FLOATING);

	if(validKind)
	{
		kind = newKind;
		return true;
	}
	else
		return false;
}

void Task::assignDetails(string description)
{
	details = description;
}

void Task::assignIDNumber(int number)
{
	taskID=number;
}

char Task::returnKind()
{
	return kind;
}

int Task::getTaskID()
{
	return taskID;
}

// Returns start or end date depending on dateOption, 0 date if invalid
date Task::returnDate(char dateOption)
{
	date d;
	d.day = d.month = d.year = 0;

	if(dateOption == TASK_DATETIME_START)
		return startDate;
	else if(dateOption == TASK_DATETIME_END)
		return endDate;
	else
		return d;
}

// Returns start or end time depending on timeOption, 0 time if invalid
time_s Task::returnTime(char timeOption)
{
	time_s t;
	t.hr = t.min = 0;

	if(timeOption == TASK_DATETIME_START)
		return startTime;
	else if(timeOption == TASK_DATETIME_END)
		return endTime;
	else
		return t;
}

// Returns true if year is a leap year, false otherwise
bool Task::checkLeapYear(int year)
{
	if (year%4 != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}