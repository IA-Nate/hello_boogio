#pragma once
#include <string>
#include <iostream>

class LogCore
{
public:
	LogCore();
	~LogCore();

	static void Print(std::string output);
	static void PrintLine(std::string output = std::string(""));
	static void PrintError(std::string output);
	
};

