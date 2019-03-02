#include <chrono>
#include <iostream>

#include "FileSystemManifest.h"
#include "BoogioDataParser.h"
#include "FileCore.h"


// Prototypes
std::string GetPresentTimestamp();

using namespace std;

int main(int argc, char **argv)
{
	// We need to find the followin directory path
	// Because the files we'll be reading will be in here
	// C:\Users\<YOUR_USER_NAME>\AppData\Local\Packages\REFLXLabsInc.Boogio_qr7cmpxc4qvfw\LocalState

	FileSystemManifest file_system;
	
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/dupenv-s-wdupenv-s?view=vs-2017
	char *pValue;
	size_t len;
	errno_t err = _dupenv_s(&pValue, &len, "TEMP");
	if (err)
	{
		return -1;
	}
    
	// Now we have C:\Users\<YOUR_USER_NAME>\AppData\Local\Temp
	
	std::string partial_path = std::string(pValue);
	free(pValue);

	int index = (int)partial_path.find("\\Temp");
	partial_path.replace(index, index ,"\\Packages");
	// Now we have C:\Users\<YOUR_USER_NAME>\AppData\Local\Packages

	file_system.RecursivelyScanContentsOfPath(partial_path);
	partial_path.append("\\REFLXLabsInc.Boogio_");

	// Now we have C:\Users\<YOUR_USER_NAME>\AppData\Local\Packages\REFLXLabsInc.Boogio_

	string boogio_app_path = file_system.CompleteThisPath(partial_path);
	string boogio_app_path_data_directory = boogio_app_path;
	boogio_app_path_data_directory.append("\\LocalState");
	
	// Now we have C:\Users\<YOUR_USER_NAME>\AppData\Local\Packages\REFLXLabsInc.Boogio_qr7cmpxc4qvfw\LocalState
	
	std::cout << boogio_app_path_data_directory << std::endl;

	string boogio_readings_left_file_path  = boogio_app_path_data_directory + "\\left_shoe_readings.txt";
	string boogio_readings_right_file_path = boogio_app_path_data_directory + "\\right_shoe_readings.txt";

	FileCore left_file_core;
	FileCore right_file_core;

	left_file_core.SetFilePath(boogio_readings_left_file_path);
	right_file_core.SetFilePath(boogio_readings_right_file_path);

	string previous_left_file_contents = std::string();
	string previous_right_file_contents = std::string();


	// File Format
	// FSR_0 FSR_1 FSR_2 FSR_3 ACCELERATION_X ACCELERATION_Y ACCELERATION_Z ROTATION_X ROTATION_Y ROTATION_Z HEADING_X HEADING_Y HEADING_Z
	BoogioDataParser left_shoe_data_parser;
	BoogioDataParser right_shoe_data_parser;

	string present_timestamp = GetPresentTimestamp();

	string delimieter = " ";

	while(true)
	{
		string new_left_file_contents = left_file_core.ReadBinaryFile();
		string new_right_file_contents = right_file_core.ReadBinaryFile();
		if (previous_left_file_contents.compare(new_left_file_contents) != 0)
		{
			left_shoe_data_parser.ConvertStringToData(&new_left_file_contents);
			previous_left_file_contents = new_left_file_contents;
			
			cout << present_timestamp << delimieter
				 << left_shoe_data_parser.fsr0 << delimieter
				 << left_shoe_data_parser.fsr1 << delimieter
				 << left_shoe_data_parser.fsr2 << delimieter
				 << left_shoe_data_parser.fsr3 << delimieter
				 << left_shoe_data_parser.accelerationX << delimieter
				 << left_shoe_data_parser.accelerationY << delimieter
				 << left_shoe_data_parser.accelerationZ << delimieter
				 << left_shoe_data_parser.rotationX << delimieter
				 << left_shoe_data_parser.rotationY << delimieter
				 << left_shoe_data_parser.rotationZ << delimieter
				 << left_shoe_data_parser.headingX << delimieter
				 << left_shoe_data_parser.headingY << delimieter
				 << left_shoe_data_parser.headingZ << endl;
		}
		if (previous_right_file_contents.compare(new_right_file_contents) != 0)
		{
			right_shoe_data_parser.ConvertStringToData(&new_right_file_contents);
			previous_right_file_contents = new_right_file_contents;
			
		    cout << present_timestamp << delimieter
				 << right_shoe_data_parser.fsr0 << delimieter
				 << right_shoe_data_parser.fsr1 << delimieter
				 << right_shoe_data_parser.fsr2 << delimieter
				 << right_shoe_data_parser.fsr3 << delimieter
				 << right_shoe_data_parser.accelerationX << delimieter
				 << right_shoe_data_parser.accelerationY << delimieter
				 << right_shoe_data_parser.accelerationZ << delimieter
				 << right_shoe_data_parser.rotationX << delimieter
				 << right_shoe_data_parser.rotationY << delimieter
				 << right_shoe_data_parser.rotationZ << delimieter
				 << right_shoe_data_parser.headingX << delimieter
				 << right_shoe_data_parser.headingY << delimieter
				 << right_shoe_data_parser.headingZ << endl;
		}
	}
	
	

	return 0;
}

std::string GetPresentTimestamp()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);
	return std::to_string(ms.count());

}