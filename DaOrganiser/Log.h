// Log.h

//
// Written by Kenneth Ang
//

//////////////////////////////////////////////////////
// Purpose: Implements logging with severity levels //
//////////////////////////////////////////////////////

//
// To use, add into your source file:	#include "Log.h"
// change line 46 below:				#define PROGRAM_NAME "yourProgramName"
// call this function to log:			logging(std::string message, LogLevel level);
//
// example:
// #include "Log.h"
// #define PROGRAM_NAME "MyOrganiser"
// logging("This is a log message", LogLevel::Info);
//

//
// Creates a file called Log PROGRAM_NAME YYYYMMDDHHMMSS.txt
// Write logs using the macro function logging(string message, LogLevel level)
// Logging Severity Levels: DEBUG, INFO, WARNING, ERROR
// Use #define NLOG before #include "Log.h" to switch off logging
//

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

//to switch off assertions
//#define NDEBUG
#include <assert.h>

#undef logging

#ifdef NLOG
#define logging(string, LogLevel) ((void)0)
#else
#define logging(string, LogLevel) Log::logging(string, LogLevel)

enum LogLevel {Debug, Info, Warning, Error};

#define PROGRAM_NAME "yourProgramName"

// Use to selectively switch off logging messages
//#define NLOG_DEBUG
//#define NLOG_INFO
//#define NLOG_WARNING
//#define NLOG_ERROR

class Log
{
public:
	static void logging(std::string, LogLevel);
	static std::string getCurrentTime(void);
};

#endif