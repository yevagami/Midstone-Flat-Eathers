#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "UtilFunctions.h"
#include "debugFunc.h"
using namespace std;


class SaveManager {
private:
	///	Variables
	const char 
		*saveFile = "SaveData/saveData.txt",
		*currentSaveFile = "SaveData/tempSaveData.txt",
		*testFile = "SaveData/testFile.txt";

	vector <string>
		saveDataOld,
		saveDataCurrent;



	/// Utility Methods
	//	for managing console text
	void consoleManager(const char* type, const char* MSG);


	///	Main Private Methods
	//	creates a file at the provided directory ex. "Folder\Folder\File.txt"
	bool createFile(const char* fileDir);
	// scan the provided vector for the variable name's value
	string getValue(vector<string> vector, const char* variableName_);
	//	replace the value with a provided newValue at the variableName's spot in the provided vector
	vector<string> replaceValue(const char* variableName_, const char* newValue_, vector<string>& strings);
	//	write the provided vector<string> to the provided file directory
	bool writeData(vector<string>& savedData, const char* fileDir);
	//	forcefully load the provided vector<string> with the provided file directory file contents
	bool loadData(vector<string>& savedData, const char* fileDir);



public:
	///	'Variables'
	vector<string> getSaveDataOld() { return saveDataOld; };
	vector<string> getSaveDataCurrent() { return saveDataCurrent; };
	const char* getSaveFile() { return saveFile; };
	const char* getCurrentSaveFile() { return currentSaveFile; };
	const char* getTestFile() { return testFile; };

	bool
		isConsoleTextEnabled;



	SaveManager();
	~SaveManager();



	///	Main Public Methods
	//	loads the game; saveFile into the currentSaveData
	bool loadGame(); 
	//	saves the game; currentSaveData into the saveFile
	bool saveGame();

	//	parses the passed file, storing all the information into a vector of strings
	vector<string> parseTHIS(const char* fileDir);
	//	updates a value in the temporary save file
	void replaceValueInCurrentSave(const char* variableName_, const char* newValue_);

	//	these functions allow for reading of variables, returning the value in a string
	string whatIs(const char* variableName, vector<string>& vector) { return getValue(vector, variableName); }
	string whatIs(const char* variableName, const char* fileDir) { return getValue(parseTHIS(fileDir), variableName); }
};