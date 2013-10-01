#include"process.h"

bool process::createTask(char value)
{
	if(value == timed)
	{

	}
	else if (value == deadline)
	{

	}
	else
	{

	}

	return true;
}

void process::readTask()
{
	// I didnt understand this function so just skipped it
	//NIC: this function is gernerally more for the command line interface so as to display out all the task that is stored into the vector
	//as previously discussed
}

bool process::updateTask()
{
	// What exactly to update?
	//NIC: update task function is for jobs that have been completed
	//so by updating it means that the task is completed
	return true;
}

bool process::deleteTask()
{
	// On what basis
	//NIC: this function can be used for undoing 
	//another way to use this function will be when the user specifically wished to delete a task from the vector
	return true;
}

//NIC: hope the above helps you a little in understanding the different functionality purposes.
//		another thing that i think is missing is the search function, when the user wants to search somethin via name or deadline