#include "BoogioDataParser.h"

#include <iostream>
#include <sstream>

BoogioDataParser::BoogioDataParser()
{
}


BoogioDataParser::~BoogioDataParser()
{
}

void BoogioDataParser::ConvertStringToData(std::string *buffer)
{
	tokens.clear();

	std::istringstream string_stream(*buffer);
	std::string token;
	while (getline(string_stream, token, ' ')) 
	{
		tokens.push_back(token);
	}
	
	if (tokens.size() < 13)
	{
		return;
	}

	fsr0 = atoi(tokens.at(0).c_str());
	fsr1 = atoi(tokens.at(1).c_str());
	fsr2 = atoi(tokens.at(2).c_str());
	fsr3 = atoi(tokens.at(3).c_str());

	accelerationX = (float)atof(tokens.at(4).c_str());
	accelerationY = (float)atof(tokens.at(5).c_str());
	accelerationZ = (float)atof(tokens.at(6).c_str());

	rotationX = (float)atof(tokens.at(7).c_str());
	rotationY = (float)atof(tokens.at(8).c_str());
	rotationZ = (float)atof(tokens.at(9).c_str());

	headingX = (float)atof(tokens.at(10).c_str());
	headingY = (float)atof(tokens.at(11).c_str());
	headingZ = (float)atof(tokens.at(12).c_str());
}

