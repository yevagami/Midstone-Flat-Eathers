#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "UtilFunctions.h"
#include "debugFunc.h"
using namespace std;


class SaveManager {
protected:
	///	Variables
	const char 
		*saveFile = "SaveData/save.txt",
		*currentSaveFile = "SaveData/currentSave.txt",
		*defaultSaveFile = "SaveData/currentSave.txt",
		*testFile = "SaveData/testFile.txt";

	//vector <string>
		//saveDataOld,
		//saveDataCurrent;

	bool
		isConsoleTextEnabled,
		isSafeToSave = false;


	/// Utility Methods
	//	for managing console text
	void consoleManager(const char* type, const char* MSG);


	///	Main Private Methods
	//	creates a file at the provided directory ex. "Folder\Folder\File.txt"
	bool createFile(const char* fileDirectory);
	//	parses the passed file, storing all the information into a vector of strings
	vector<string> parseTHIS(const char* fileDirectory);
	//	write the provided vector<string> to the provided file directory
	bool writeData(vector<string>& savedData, const char* fileDirectory);
	//	forcefully load the provided vector<string> with the provided file directory file contents
	bool readData(vector<string>& savedData, const char* fileDirectory);
	//	scans the provided file for the string 
	bool scanFileFor(const char* target, const char* fileDirectory);
	//	checks to see if the string contents already exists in the file, if not its added.
	bool addToFile(string content, const char* fileDirectory);
	//	DO. NOT. USE. 
	bool deleteFromFile(string content, const char* fileDirectory);


	//	Vector Methods
	// scan the provided vector for the variable name's value
	string scanVectorFor(vector<string> vector, const char* variableName_);
	//	replace the value with a provided newValue at the variableName's spot in the provided vector
	vector<string> replaceValueInVector(const char* variableName_, const char* newValue_, vector<string>& strings);


	//	String Methods
	string formatString(const char* variableName, const char* value);


public:
	///	'Variables'
	vector<string> getOldSaveData() { return parseTHIS(saveFile); };
	vector<string> getCurrentSaveData() { return parseTHIS(currentSaveFile); };
		//could change this^
		//make an "updateCurrentInfo" that parses it, then the getter just gets the most recent parse.

	const char* getOldSaveFileDirectory() { return saveFile; };
	const char* getCurrentSaveFileDirectory() { return currentSaveFile; };
	const char* getDefaultSaveFileDirectory() { return defaultSaveFile; };
		
	void toggleConsoleText() { isConsoleTextEnabled = !isConsoleTextEnabled;  consoleManager("not error", "consoleText toggled"); }
	bool getConsoleTextState() {return isConsoleTextEnabled; }
	void toggleSafeToSave() { isSafeToSave = !isSafeToSave; consoleManager("not error", "safeToSave toggled"); }
	

	SaveManager();
	~SaveManager();


	///	Main Public Methods
	//	loads the game; saveFile into the currentSaveFile
	bool loadGame(); 
	//	saves the game; currentSaveData into the saveFile
	bool saveGame();

	//	adds a variable and value to the current save file
	bool addValueToCurrentSave(const char* variableName_, const char* value_);
	//	updates a value in the current save file
	bool replaceValueInCurrentSave(const char* variableName_, const char* newValue_);

	//	these functions allow for reading of variables, returning the value in a string
	string whatIs(const char* variableName, vector<string>& vector) { return scanVectorFor(vector, variableName); }
	string whatIs(const char* variableName, const char* fileDir) { return scanVectorFor(parseTHIS(fileDir), variableName); }

};