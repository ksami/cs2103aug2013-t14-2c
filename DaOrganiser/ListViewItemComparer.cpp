/*

Done by Kenneth

*/

#include "stdafx.h"
#include "ListViewItemComparer.h"


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

//return 1 if x is above y, -1 if x is lower than y
int ListViewItemComparer::Compare(Object^ x, Object^ y)
{
	int retVal=0;

	String^ item1 = (dynamic_cast<ListViewItem^>(x))->SubItems[col]->Text;
	String^ item2 = (dynamic_cast<ListViewItem^>(y))->SubItems[col]->Text;

	//use different ways of comparing depending on type of data in that column
	switch(col)
	{
	case 1: //TODO
	default:
		break;
	}

	retVal = asc * String::Compare(item1, item2);

	return retVal;
}