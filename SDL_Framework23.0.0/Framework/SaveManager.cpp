#include "SaveManager.h"
#include "ConsistentConsole.h"

FileManager fmSave;
ConsistentConsole ccSave;
SaveState ssSave;



void SaveManager::toggleSafeToSave() {
 isSafeToSave = !isSafeToSave; 
 ccSave.consoleManager("not error", "safeToSave toggled"); 
}


SaveManager::SaveManager() {
	//	safeguard in the constructor (WIP)
	if (createFile(ssSave.getCurrentSaveFileDirectory()) && createFile(ssSave.getCurrentSaveFileDirectory())) {
		isSafeToSave = true;
	}

}


SaveManager::~SaveManager() {
	isSafeToSave = false;
}


bool SaveManager::writeSave() {
	if (isSafeToSave) {
		ccSave.consoleManager("", "goofiness aside, it's ready to save");
		vector<string> saveDataCurrent = getCurrentSaveData();
		vector<string> saveDataOld = getOldSaveData();

		if (ccSave.getConsoleTextState()) {
			ccSave.consoleManager("", "replacing:");
			fmSave.printVectorString(saveDataOld);
			ccSave.consoleManager("", "with:");
			fmSave.printVectorString(saveDataCurrent);
		}

		//copies the contents from the temp SaveManager file to the main SaveManager file.
		if (writeData(saveDataCurrent, getSaveFileDirectory())) {
			ccSave.consoleManager("not error", "file succ1essfully saved");
		}
		else { ccSave.consoleManager("error", "uh oh... file saved't"); }
		return true;


	}
	else {
		ccSave.consoleManager("error", "save game failed, save file doesn't exist and cannot be created...");
		return false;
	}
}

bool SaveManager::clearBothSaves() {
	bool resultOld = clearOldSave();
	bool resultCurrent = clearCurrentSave();

	if (!resultOld) {
		ccSave.consoleManager("error", "couldn't clear the Old Save"); }
	if (!resultCurrent) {
		ccSave.consoleManager("error", "couldn't clear the Current Save"); }

	return resultOld && resultCurrent;
}

bool SaveManager::clearOldSave() {
	bool resultOld = fmSave.emptyFile(getSaveFileDirectory());

	if (!resultOld) {
		ccSave.consoleManager("error", "couldn't clear the Old Save");
	}

	return resultOld;
}

bool SaveManager::clearCurrentSave() {
	bool resultCurrent = fmSave.emptyFile(getCurrentSaveFileDirectory());

	if (!resultCurrent) {
		ccSave.consoleManager("error", "couldn't clear the Current Save");
	}

	return resultCurrent;
}


bool SaveManager::readSave() {
	if (isSafeToSave) {
		vector<string> saveDataCurrentTemp = getCurrentSaveData();
		readData(saveDataCurrentTemp, ssSave.getSaveFileDirectory());
		ccSave.consoleManager("not error", "save load succ1essful");
		return true;

	}
	else {
		ccSave.consoleManager("error", "save load failed, unsafe to load save.");
		return false;

	}
}


bool SaveManager::replaceValueInCurrentSave(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = getCurrentSaveData();
	tempVector = fmSave.replaceValueInVector(tempVector, variableName_, newValue_);
	if (writeData(tempVector, ssSave.getCurrentSaveFileDirectory())) {
		return true;



	}
	else {
		return false;
	}
}


bool SaveManager::addValueToCurrentSave(const char* variableName_, const char* value_) {
	if (!scanFileFor(variableName_, ssSave.getCurrentSaveFileDirectory())) {
		string toAdd = fmSave.formatString(variableName_, value_);
		addToFile(toAdd, ssSave.getCurrentSaveFileDirectory());

	}
	else {
		ccSave.consoleManager("error", "variable already exists inside the current save");
	}





	return false;
}


vector<string> SaveManager::getOldSaveData() {
	return fmSave.parseTHIS(getSaveFileDirectory());
}


vector<string> SaveManager::getCurrentSaveData() { 
	return fmSave.parseTHIS(getCurrentSaveFileDirectory());
}

const char* SaveManager::getSaveFileDirectory() {
	return saveFile;
}

const char* SaveManager::getCurrentSaveFileDirectory() {
	return currentSaveFile;
}

const char* SaveManager::getDefaultSaveFileDirectory() {
	return defaultSaveFile;
}