//@Kenneth A0097075W

// Implements sorting by columns for ListViewItems

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

public ref class ListViewItemComparer: public IComparer
{
protected:
	// Column number to sort by
	int col;

	// Sort by ascending or descending order
	int asc;

public:
	ListViewItemComparer();
	ListViewItemComparer(int, int);
	
	virtual int Compare(Object^ x, Object^ y);
};
