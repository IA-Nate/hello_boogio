#include "LogCore.h"



LogCore::LogCore()
{
}


LogCore::~LogCore()
{
}

void LogCore::Print(std::string output)
{
	std::cout << output;
}

void LogCore::PrintLine(std::string output)
{
	LogCore::Print(output);
	std::cout << std::endl;
}

void LogCore::PrintError(std::string output)
{
	std::cerr << output;
}

