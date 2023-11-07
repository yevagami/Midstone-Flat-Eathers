#include "SaveManager.h"
#include "ConsistentConsole.h"
#include "PrettyPrinting.h"

//FileManager fmSave;
ConsistentConsole ccSave(true);
SaveState ssSave;
//PrettyPrinting ppSave; //	lol pp



void SaveManager::toggleSafeToSave() {
 isSafeToSave = !isSafeToSave; 
 ccSave.log("update", "safeToSave toggled"); 
}


SaveManager::SaveManager() {
	//	safeguard in the constructor (WIP)
	if ((ssSave.getCurrentSaveFileDirectory()) && fileCheck(ssSave.getCurrentSaveFileDirectory())) {
		isSafeToSave = true;
	}

}


bool SaveManager::writeSave() {
	if (!isSafeToSave) {
		ccSave.log("error", "save game failed, save file doesn't exist and cannot be created...");
		return false;
	}

	ccSave.log("update", "goofiness aside, saving...");
	vector<string> saveDataCurrent = getCurrentSaveData();
	vector<string> saveDataOld = getOldSaveData();

	//	printing
	if (ccSave.getConsoleState()) {
		ccSave.log("", "replacing:");
		//ppSave.printVS(saveDataOld);
		ccSave.log("", "with:");
		//ppSave.printVS(saveDataCurrent); }

	//copies the contents from the temp SaveManager file to the main SaveManager file.
		if (!fileWrite(saveDataCurrent, getSaveFileDirectory())) {
			ccSave.log("error", "uh oh... file saved't");
		}

		ccSave.log("update", "file succ1essfully saved");
		return true;

	}
}

	bool SaveManager::clearBothSaves() {
		if (!clearOldSave() && !clearCurrentSave()) {
			ccSave.log(error, "couldn't clear both the Saves");
			return false;
		}

		ccSave.log(update, "cleared both files");
		return true;
	}

bool SaveManager::clearOldSave() {
	if (!fileEmpty(getSaveFileDirectory())) {
		ccSave.log(error, "couldn't clear the Old Save");
		return false;
	}

	return true;
}

bool SaveManager::clearCurrentSave() {
	if (!fileEmpty(getCurrentSaveFileDirectory())) {
		ccSave.log(error, "couldn't clear the Current Save");
		return false;
	}

	return true;
}


bool SaveManager::readSave() {
	if (!isSafeToSave) {
		ccSave.log("error", "save load failed, unsafe to load save.");
		return false;
	}

	vector<string> saveDataCurrentTemp = getCurrentSaveData();
	fileLoadToVector(saveDataCurrentTemp, ssSave.getSaveFileDirectory());
	ccSave.log("update", "save loaded");
	return true;

}



bool SaveManager::replaceValueInCurrentSave(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = getCurrentSaveData();
	tempVector = replaceValue(variableName_, newValue_, tempVector);

	if (fileWrite(tempVector, ssSave.getCurrentSaveFileDirectory())) {
		return true; 
	} else {
		return false;
	}
}


string SaveManager::whatIs(const char* variableName) {
	return scanVectorFor(parseTHIS(currentSaveFile), variableName);
}


bool SaveManager::addValueToCurrentSaveFile(const char* variableName_, const char* value_) {
	if (!isHere(variableName_, ssSave.getCurrentSaveFileDirectory())) {
		string toAdd = stringReformat(variableName_, value_);
		fileInsert(toAdd, ssSave.getCurrentSaveFileDirectory());
		return true;

	} else {
		ccSave.log("error", "variable already exists inside the current save");
	}
	return false;
}


vector<string> SaveManager::getOldSaveData() {
	return parseTHIS(getSaveFileDirectory());
}


vector<string> SaveManager::getCurrentSaveData() { 
	return parseTHIS(getCurrentSaveFileDirectory());
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