#pragma once
#include "FileManager.h"




class SaveManager : private FileManager {
protected:
	///	Variable
	bool
		//	do both of the main save files exist (saveFile and currentSaveFile)
		isSafeToSave = false;

	const char
		//	Save Files
		* saveFile = "SaveData/save.txt",
		* currentSaveFile = "SaveData/currentSave.txt",
		* defaultSaveFile = "SaveData/currentSave.txt",
		//	Debug
		* testFile = "SaveData/testFile.txt";

public:
	///	Constructors / Destructors
	SaveManager();


	///	Getters / Setters
	vector<string> getOldSaveData();
	vector<string> getCurrentSaveData();
	const char* getSaveFileDirectory();
	const char* getCurrentSaveFileDirectory();
	const char* getDefaultSaveFileDirectory();
	void toggleSafeToSave();


	///	Main Public Methods
	//	loads the game; saveFile into the currentSaveFile
	bool readSave();
	//	saves the game; currentSaveData into the saveFile
	bool writeSave();
	//	clears both the save files.
	bool clearBothSaves();
	//	clears the old save file
	bool clearOldSave();
	//	clears the current save file
	bool clearCurrentSave();

	//	adds a variable and value to the current save file
	bool addValueToCurrentSaveFile(const char* variableName_, const char* value_);
	//	updates a value in the current save file
	bool replaceValueInCurrentSave(const char* variableName_, const char* newValue_);
	//	reads the VALUE associated with a variable from a FILE
	string whatIs(const char* variableName);

};


class SaveState : public SaveManager {
protected:
	///	Variables
	////does nothing rn
	//vector <string>
	//saveDataOld,
	//saveDataCurrent;

public:
	
};
