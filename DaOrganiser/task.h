#pragma once

#include <iostream>
#include <iomanip>
#include "clock.h"
#include "date.h"
using namespace std;

class task{
private:
	date _startDate;
	clockTime _startTime;
	date _endDate;
	clockTime _endTime;

public:
	task();							//floating
	task(date,clockTime);				//deadline
	task(date,date,clockTime,clockTime);		//timed
	~task();
	date getStartDate();
	date getEndDate();
	clockTime getStartTime();
	clockTime getEndTime();
	void printTask();
};