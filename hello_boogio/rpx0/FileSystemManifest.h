#pragma once

#include <string>
#include <vector>

class FileSystemManifest
{
public:
	FileSystemManifest();
	~FileSystemManifest();

	std::string RecursivelyScanContentsOfPath(std::string path);
	void ClearManifestCache();

	std::string CompleteThisPath(std::string prefix);


private:
	std::vector<std::string> discoveredDirectories;
	std::vector<std::string> discoveredFilePaths;
};

