#pragma once

class date {
private:
	int _year;
	int _month;
	int _day;
	
public:
	date();
	~date();
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
	int getYear();
	int getMonth();
	int getDay();
};