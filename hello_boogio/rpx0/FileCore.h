#pragma once
#include <string>

class FileCore
{
public:
	FileCore();
	~FileCore();

	void SetFilePath(std::string file_path);
	std::string ReadBinaryFile();

private:
	std::string filePath;
};

