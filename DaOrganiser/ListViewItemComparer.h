/*

Done by Kenneth

*/

//Implementation of comparer/sorter for listview

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

public ref class ListViewItemComparer: public IComparer
{
protected:
	int col;
	int asc;

public:
	ListViewItemComparer();
	ListViewItemComparer(int, int);
	
	//Implements sorting by columns for listview
	virtual int Compare(Object^ x, Object^ y);
};
