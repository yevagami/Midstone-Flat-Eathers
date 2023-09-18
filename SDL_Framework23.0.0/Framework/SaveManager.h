#pragma once
#include "FileManager.h"



class SaveManager : private FileManager {
protected:
	///	Variables
	const char
		* saveFile = "SaveData/save.txt",
		* currentSaveFile = "SaveData/currentSave.txt",
		* defaultSaveFile = "SaveData/currentSave.txt",
		* testFile = "SaveData/testFile.txt";

	//vector <string>
		//saveDataOld,
		//saveDataCurrent;

	bool
		isSafeToSave = false;

public:
	///	Constructors / Destructors
	SaveManager();
	~SaveManager();


	///	Getters / Setters
	vector<string> getOldSaveData();
	vector<string> getCurrentSaveData();
	const char* getSaveFileDirectory() { return saveFile; };
	const char* getCurrentSaveFileDirectory() { return currentSaveFile; };
	const char* getDefaultSaveFileDirectory() { return defaultSaveFile; };
	void toggleSafeToSave();


	///	Main Public Methods
	//	loads the game; saveFile into the currentSaveFile
	bool loadGame();
	//	saves the game; currentSaveData into the saveFile
	bool saveGame();
	//	adds a variable and value to the current save file
	bool addValueToCurrentSave(const char* variableName_, const char* value_);
	//	updates a value in the current save file
	bool replaceValueInCurrentSave(const char* variableName_, const char* newValue_);
};