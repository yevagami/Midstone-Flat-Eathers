#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "UtilFunctions.h"
using namespace std;


class Save {
private:
	///	Variables
	const char* testFile = "SaveData/testFile.txt";
	const char* saveFile = "SaveData/saveData.txt";
	const char* tempSaveFile = "SaveData/tempSaveData.txt";

	/// Utility Methods
	//	for managing console text
	void consoleManager(const char* type, const char* MSG);
	///	Main Methods
	bool createFile(const char* fileDir);
	// scan the provided vector for the variable name's value
	string getValue(vector<string> vector, const char* variableName_);
	//	replace the value with a provided newValue at the variableName's spot in the provided vector
	vector<string> replaceValue(const char* variableName_, const char* newValue_, vector<string>& strings);
	//	write the provided vector<string> to the provided file directory
	bool writeData(vector<string>& savedData, const char* fileDir);


public:
	//	loads the saveFile contents into the tempSaveFile
	bool loadGame();
	//saves the game (transfers the contents from the tempSaveFile to the main saveFile)
	bool saveGame();
	//	updates a value in the temporary save file
	void replaceValueForSaving(const char* variableName_, const char* newValue_);
	//	parse the passed file, storing all the information into the passed vector<string>.
	vector<string> parseTHIS(const char* fileDir);


	string whatIs(const char* variableName) { return getValue(parseTHIS(saveFile), variableName); }
	string whatIs(const char* variableName, vector<string>& vector) { return getValue(vector, variableName); }
	string whatIs(const char* variableName, const char* fileDir) { return getValue(parseTHIS(fileDir), variableName); }


};

