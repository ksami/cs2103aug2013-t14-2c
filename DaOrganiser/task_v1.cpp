/*

Author: Priya

*/

#include"task.h"
#include<iostream>
#include<string>

using namespace std;

task::task()
{
	status = notDone;
	kind = 'f';
	startDate.day = startDate.month = startDate.year = 0;
	endDate.day = endDate.month = endDate.year = 0;
	startTime.hr = startTime.min = 0;
	endTime.hr = endTime.min = 0;
	details = "";
}

int task::checkDate(date first, date second)
{
	if(first.year>second.year)
		return moreThan;
	if(first.year<second.year)
		return lessThan;
	if(first.month>second.month)
		return moreThan;
	if(first.month<second.month)
		return lessThan;
	if(first.day>second.day)
		return moreThan;
	if(first.day<second.day)
		return lessThan;

	return equalTo;	
}

int task::checkTime(time first, time second)
{
	if(first.hr>second.hr)
		return moreThan;
	if(first.hr<second.hr)
		return lessThan;
	if(first.min>second.min)
		return moreThan;
	if(first.min<second.min)
		return lessThan;

	return equalTo;
}

char task::checkStatus()
{
	return status;
}

bool task::changeStatus(char complete)
{
	if (complete == done)
		status = done;
	else if(complete == notDone)
		status == notDone;
	else
		return false;

	return true;
}

bool task::assignDateValue(date value, char dateOption)
{
	if(value.day<one||value.month<one||value.year<one)
		return false;

	switch(value.month)
	{
	case 1: if(value.day<=31) break; 
	case 2: if(value.day<=29) break;
	case 3: if(value.day<=31) break;
	case 4: if(value.day<= 30) break;
	case 5: if(value.day<=31) break;
	case 6: if(value.day<=30) break;
	case 7: if(value.day<=31) break;
	case 8: if(value.day<=31) break;
	case 9: if(value.day<=30) break;
	case 10: if(value.day<=31) break;
	case 11: if(value.day<=30) break;
	case 12: if(value.day<=31) break;
	default: return false;
	}

	if((!(value.year%400 ==0 || (value.year%100 != 0 && value.year%4 == 0)))&&(value.day>28))
		return false;

	if(dateOption==start)
		startDate = value;
	else
		endDate = value;

	return true;
}

bool task::assignTimeValue(time value, char timeOption)
{
	if(value.hr>23||value.hr<0||value.min>59||value.min<0)
		return false;

	if(timeOption== start)
		startTime = value;
	else
		endTime = value;

	return true;
}

bool task::assignKind(char value)
{
	if((value == timed)||(value == deadline)||(value == floating))
	{
		kind = value;
		return true;
	}
	else
		return false;
}

void task::assignDetails(string description)
{
	details = description;
}

void task::displayDetail()
{
	string sdate = "", edate = "", stime = "", etime = "";
	sdate = to_string(startDate.day)+" / "+to_string(startDate.month)+" / "+to_string(startDate.year);
	edate = to_string(endDate.day)+" / "+to_string(endDate.month)+" / "+to_string(endDate.year);
	stime = to_string(startTime.hr)+" : "+to_string(startTime.min);
	etime = to_string(endTime.hr)+" : "+to_string(endTime.min);
	cout<<"Start date: "<<sdate<<endl;
	cout<<"End date: "<<edate<<endl;
	cout<<"Start time: "<<stime<<endl;
	cout<<"End time: "<<etime<<endl;
	cout<<"Details: "<<details<<endl;
	cout<<"Status: "<<status<<endl;
	cout<<"Kind: "<<kind<<endl;

}

char task::returnKind()
{
	return kind;
}