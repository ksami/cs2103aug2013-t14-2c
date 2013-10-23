#pragma once

#include<iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "task_v0.2.h"

using namespace std;

class taskManager
{
private:

public:
        bool createTask(vector<string>,vector<task>&);
        void readTask(vector<task>&);
        bool updateTask(vector<string>,vector<task>&);
        bool deleteTask(vector<string>,vector<task>&);
};
