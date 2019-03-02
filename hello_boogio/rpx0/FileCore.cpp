#include "FileCore.h"


#include <fstream>
#include <sstream>
#include <iostream>

#include <cstdint>

FileCore::FileCore()
{
}


FileCore::~FileCore()
{
}
void FileCore::SetFilePath(std::string file_path)
{
	filePath = file_path;
}
// https://en.cppreference.com/w/cpp/io/basic_istream/read
std::string FileCore::ReadBinaryFile()
{
	// read entire file into string
	if (std::ifstream is{ filePath, std::ios::binary | std::ios::ate }) {
		auto size = is.tellg();
		std::string str(size, '\0'); // construct string to stream size
		is.seekg(0);
		if (is.read(&str[0], size))
		{
			//std::cout << str << '\n';
			return str;
		}
			
		return std::string();
	}
	return std::string();
}
