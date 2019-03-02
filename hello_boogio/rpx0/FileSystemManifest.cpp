#include "FileSystemManifest.h"
#include <filesystem>


FileSystemManifest::FileSystemManifest()
{
}


FileSystemManifest::~FileSystemManifest()
{
}
void FileSystemManifest::ClearManifestCache()
{
	discoveredDirectories.clear();
	discoveredFilePaths.clear();
}
std::string FileSystemManifest::CompleteThisPath(std::string prefix)
{
	for (int i = 0; i < discoveredDirectories.size(); i++)
	{
		if (discoveredDirectories.at(i).find(prefix) != std::string::npos)
		{
			return discoveredDirectories.at(i);
		}
	}
	return std::string();
}
std::string FileSystemManifest::RecursivelyScanContentsOfPath(std::string path)
{
	std::string path_contents = "";
	
	try {
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{

			std::string item = entry.path().u8string();
			path_contents.append(item);
			bool item_is_directory = std::filesystem::is_directory(item);

			// If the item is a directory, append a trailing '\'
			// to indicate it IS indeed a directory and not a file
			path_contents.append("\n");
			if (item_is_directory)
			{
				discoveredDirectories.push_back(item);
				path_contents.append(RecursivelyScanContentsOfPath(item));
			}
			else
			{
				discoveredFilePaths.push_back(item);
			}

		}
	}
	catch (std::filesystem::filesystem_error e) {}
	return path_contents;

}

