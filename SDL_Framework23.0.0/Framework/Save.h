#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Save {
private:
	///	Variables
	string saveFile = "SaveData/saveData.txt"; 
	
	/// Utility Methods
	//	for managing console text
	void consoleManager(const char* type, const char* MSG);


public:
	///	Main Methods
	//	creates the SaveData File.
	void createSaveFile();
	//parse the passed file, storing all the information into the passed vector<string>.
	void parseTHIS(vector<string> data, const char* fileToOpen);


	//	unused / not done
	void applySaveData();
	void writeSaveData();
};

