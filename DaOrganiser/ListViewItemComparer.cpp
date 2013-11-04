/*

Done by Kenneth

*/

// Implements sorting by columns for ListViewItems

#include "stdafx.h"
#include "ListViewItemComparer.h"

#define COL_TASKID 0
#define COL_DETAILS 3
#define COL_START 1
#define COL_END 2
#define COL_STATUS 4
#define COL_KIND 5
#define DATETIME_DELIMITERS " ", "/", ":"


ListViewItemComparer::ListViewItemComparer(void)
{
	col = 0;
	asc = 1;
}

ListViewItemComparer::ListViewItemComparer( int column, int ascending )
{
	col = column;
	asc = ascending;
}

// Return 1 if x is above y, -1 if x is lower than y
int ListViewItemComparer::Compare(Object^ x, Object^ y)
{
	int returnVal=0;

	String^ item1 = (dynamic_cast<ListViewItem^>(x))->SubItems[col]->Text;
	String^ item2 = (dynamic_cast<ListViewItem^>(y))->SubItems[col]->Text;

	//use different ways of comparing depending on type of data in that column
	switch(col)
	{
	case COL_TASKID:
		{
			returnVal = asc * (System::Convert::ToInt32(item1) - System::Convert::ToInt32(item2));
			break;
		}
	case COL_STATUS:
		{
		}
	case COL_KIND:
		{
		}
	case COL_DETAILS:
		{
			returnVal = asc * String::Compare(item1, item2);
			break;
		}
	case COL_START:
		{
		}
	case COL_END:
		{
			array <String^>^ delimiter = {DATETIME_DELIMITERS};

			//datetime[0] = dd
			//datetime[1] = MM
			//datetime[2] = yy
			//datetime[3] = hh
			//datetime[4] = mm
			array <String^>^ dateTime1 = item1->Split(delimiter, System::StringSplitOptions::RemoveEmptyEntries);
			array <String^>^ dateTime2 = item2->Split(delimiter, System::StringSplitOptions::RemoveEmptyEntries);

			//concatenate into yyMMddhhmm for ease of comparison
			String^ date1 = dateTime1[2]+dateTime1[1]+dateTime1[0]+dateTime1[3]+dateTime1[4];
			String^ date2 = dateTime2[2]+dateTime2[1]+dateTime2[0]+dateTime2[3]+dateTime2[4];

			returnVal = asc * String::Compare(date1, date2);
			break;
		}
	}
	return returnVal;
}