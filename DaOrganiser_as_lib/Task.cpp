#include "Task.h"
using namespace std;

Task::Task()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	status = notDone;
	kind = 'f';
	startDate.day = ltm->tm_mday;
	startDate.month = 1 + ltm->tm_mon;
	startDate.year = 1900 + ltm->tm_year;
	endDate.day = endDate.month = endDate.year = 0;
	startTime.hr = ltm->tm_hour;
	startTime.min = 1 + ltm->tm_min;
	endTime.hr = endTime.min = 0;
	details = "";
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

date Task::returnDate(char check)
{
        date d;
        d.day = d.month = d.year = 0;

        if(check == 's')
                return startDate;
        else if(check == 'e')
                return endDate;
        else
                return d;
}

time_s Task::returnTime(char check)
{
        time_s t;
        t.hr = t.min = 0;

        if(check == 's')
                return startTime;
        else if(check == 'e')
                return endTime;
        else
                return t;
}