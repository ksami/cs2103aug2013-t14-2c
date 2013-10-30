#include "stdafx.h"
#include "Task.h"

Task::Task()
{
    status = notDone;
    kind = 'f';
    startDate.day = startDate.month = startDate.year = 0;
    endDate.day = endDate.month = endDate.year = 0;
    startTime.hr = startTime.min = 0;
    endTime.hr = endTime.min = 0;
    details = "";
}

string Task::getIdAsString()
{
	return std::to_string(taskID);
}
string Task::getStartDateAsString()
{
	string startDateAsString;
	startDateAsString += std::to_string(startDate.year);
	startDateAsString += "/";
	startDateAsString += std::to_string(startDate.month);
	startDateAsString += "/";
	startDateAsString += std::to_string(startDate.day);
	return startDateAsString;
}
string Task::getEndDateAsString()
{
	string endDateAsString;
	endDateAsString += std::to_string(endDate.year);
	endDateAsString += "/";
	endDateAsString += std::to_string(endDate.month);
	endDateAsString += "/";
	endDateAsString += std::to_string(endDate.day);
	return endDateAsString;
}
string Task::getStartTimeAsString()
{
	string startTimeAsString;
	startTimeAsString += std::to_string(startTime.hr);
	startTimeAsString += ":";
	startTimeAsString += std::to_string(startTime.min);
	return startTimeAsString;
}
string Task::getEndTimeAsString()
{	
	string endTimeAsString;
	endTimeAsString += std::to_string(endTime.hr);
	endTimeAsString += ":";
	endTimeAsString += std::to_string(endTime.min);
	return endTimeAsString;
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
	case 'n': statusAsString = "Not done"; break;
	case 'd': statusAsString = "Done"; break;
	default: assert(false); break;  //invalid status
	}
	return statusAsString;
}
string Task::getKindAsString()
{
	string kindAsString;
	switch(kind)
	{
	case 'd': kindAsString = "Deadline Task"; break;
	case 'f': kindAsString = "Floating Task"; break;
	case 't': kindAsString = "Timed Task"; break;
	default: assert(false); break;  //invalid kind
	}
	return kindAsString;
}

int Task::checkDate(date first, date second)
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

int Task::checkTime(time_s first, time_s second)
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

char Task::checkStatus()
{
        return status;
}

bool Task::changeStatus(char complete)
{
        if (complete == done)
                status = done;
        else if(complete == notDone)
                status = notDone;
        else
                return false;

        return true;
}

bool Task::assignDateValue(date value, char dateOption)
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

bool Task::assignTimeValue(time_s value, char timeOption)
{
        if(value.hr>23||value.hr<0||value.min>59||value.min<0)
                return false;

        if(timeOption== start)
                startTime = value;
        else
                endTime = value;

        return true;
}

bool Task::assignKind(char value)
{
        if((value == timed)||(value == deadline)||(value == floating))
        {
                kind = value;
                return true;
        }
        else
                return false;
}

void Task::assignDetails(string description)
{
        details = description;
}

//for CLI
void Task::displayDetail()
{
    cout<<taskID<<endl;
 
    cout<<"Start date: "<<
        setfill('0')<<setw(2)<<to_string(startDate.day)<<" / "<<
        setfill('0')<<setw(2)<<to_string(startDate.month)<<" / "<<
        setfill('0')<<setw(2)<<to_string(startDate.year)<<endl;
 
    cout<<"End date: "<<
        setfill('0')<<setw(2)<<to_string(endDate.day)<<" / "<<
        setfill('0')<<setw(2)<<to_string(endDate.month)<<" / "<<
        setfill('0')<<setw(2)<<to_string(endDate.year)<<endl;
 
    cout<<"Start time: "<<        
        setfill('0')<<setw(2)<<to_string(startTime.hr)<<" : "<<
        setfill('0')<<setw(2)<<to_string(startTime.min)<<endl;
 
    cout<<"End time: "<<
        setfill('0')<<setw(2)<<to_string(endTime.hr)<<" : "<<
        setfill('0')<<setw(2)<<to_string(endTime.min)<<endl;
 
    cout<<"Details: "<<details<<endl;
 
    if(status == 'd') 
        cout<<"Status: Task completed"<<endl; 
    else
        cout<<"Status: Task yet to be complete"<<endl; 
  
    if(kind == 'f') 
        cout<<"Kind: Floating Task"; 
    else if (kind == 'd') 
        cout<<"Kind: Task with deadline";
    else
        cout<<"Kind: Timed Task";
    cout<<endl<<"--------------------------------------------";

}

void Task::assignIDNumber(int number) {
    taskID=number;
}
 
char Task::returnKind()
{
        return kind;
}
 
int Task::getTaskID() {
    return taskID;
}