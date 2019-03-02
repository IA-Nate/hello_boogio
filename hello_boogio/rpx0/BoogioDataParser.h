#pragma once

#include <string>
#include <vector>

class BoogioDataParser
{
public:
	BoogioDataParser();
	~BoogioDataParser();

	void ConvertStringToData(std::string *buffer);
	

	unsigned int fsr0;
	unsigned int fsr1;
	unsigned int fsr2;
	unsigned int fsr3;

	float accelerationX;
	float accelerationY;
	float accelerationZ;

	float rotationX;
	float rotationY;
	float rotationZ;

	float headingX;
	float headingY;
	float headingZ;

private:
	std::vector<std::string> tokens;
};

