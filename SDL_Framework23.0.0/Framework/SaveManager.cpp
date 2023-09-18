#include "SaveManager.h"
#include "ConsistentConsole.h"

FileManager fm;
ConsistentConsole cc1;


void SaveManager::toggleSafeToSave() {
 isSafeToSave = !isSafeToSave; 
 cc1.consoleManager("not error", "safeToSave toggled"); 
}


SaveManager::SaveManager() {
	//	safeguard in the constructor (WIP)
	if (createFile(saveFile) && createFile(currentSaveFile)) {
		isSafeToSave = true;
	}

}


SaveManager::~SaveManager() {
	isSafeToSave = false;
}


bool SaveManager::saveGame() {
	if (isSafeToSave) {
		cc1.consoleManager("", "goofiness aside, it's ready to save");
		vector<string> saveDataCurrent = getCurrentSaveData();
		vector<string> saveDataOld = getOldSaveData();

		if (cc1.getConsoleTextState()) {
			cc1.consoleManager("", "replacing:");
			fm.printVectorString(saveDataOld);
			cc1.consoleManager("", "with:");
			fm.printVectorString(saveDataCurrent);
		}

		//copies the contents from the temp SaveManager file to the main SaveManager file.
		if (writeData(saveDataCurrent, saveFile)) {
			cc1.consoleManager("not error", "file succ1essfully saved");
		}
		else { cc1.consoleManager("error", "uh oh... file saved't"); }
		return true;


	}
	else {
		cc1.consoleManager("error", "save game failed, save file doesn't exist and cannot be created...");
		return false;
	}
}


bool SaveManager::loadGame() {
	if (isSafeToSave) {
		vector<string> saveDataCurrentTemp = getCurrentSaveData();
		readData(saveDataCurrentTemp, saveFile);
		cc1.consoleManager("not error", "save load succ1essful");
		return true;

	}
	else {
		cc1.consoleManager("error", "save load failed, unsafe to load save.");
		return false;

	}
}


bool SaveManager::replaceValueInCurrentSave(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = getCurrentSaveData();
	tempVector = fm.replaceValueInVector(variableName_, newValue_, tempVector);
	if (writeData(tempVector, currentSaveFile)) {
		return true;



	}
	else {
		return false;
	}
}


bool SaveManager::addValueToCurrentSave(const char* variableName_, const char* value_) {
	if (!scanFileFor(variableName_, currentSaveFile)) {
		string toAdd = fm.formatString(variableName_, value_);
		addToFile(toAdd, currentSaveFile);

	}
	else {
		cc1.consoleManager("error", "variable already exists inside the current save");
	}





	return false;
}


vector<string> SaveManager::getOldSaveData() { return fm.parseTHIS(saveFile); }


vector<string> SaveManager::getCurrentSaveData() { return fm.parseTHIS(currentSaveFile); }
