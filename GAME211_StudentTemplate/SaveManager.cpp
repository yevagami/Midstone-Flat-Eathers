#include "SaveManager.h"
#include "ConsistentConsole.h"
#include "PrettyPrinting.h"

FileManager fmSave;
ConsistentConsole ccSave(false);
SaveState ssSave;
PrettyPrinting ppSave; //	lol pp



void SaveManager::toggleSafeToSave() {
 isSafeToSave = !isSafeToSave; 
 ccSave.consoleManager("update", "safeToSave toggled"); 
}


SaveManager::SaveManager() {
	//	safeguard in the constructor (WIP)
	if ((ssSave.getCurrentSaveFileDirectory()) && checkFile(ssSave.getCurrentSaveFileDirectory())) {
		isSafeToSave = true;
	}

}


bool SaveManager::writeSave() {
	if (!isSafeToSave) {
		ccSave.consoleManager("error", "save game failed, save file doesn't exist and cannot be created...");
		return false; }

	ccSave.consoleManager("update", "goofiness aside, saving...");
	vector<string> saveDataCurrent = getCurrentSaveData();
	vector<string> saveDataOld = getOldSaveData();

		//	printing
	if (ccSave.getConsoleState()) {
		ccSave.consoleManager("", "replacing:");
		ppSave.printVS(saveDataOld);
		ccSave.consoleManager("", "with:");
		ppSave.printVS(saveDataCurrent); }

	//copies the contents from the temp SaveManager file to the main SaveManager file.
	if (!writeData(saveDataCurrent, getSaveFileDirectory())) {
		ccSave.consoleManager("error", "uh oh... file saved't"); }
		
		ccSave.consoleManager("update", "file succ1essfully saved");
		return true;

}

bool SaveManager::clearBothSaves() {
	if (!clearOldSave() && !clearCurrentSave()) {
		ccSave.consoleManager("error", "couldn't clear both the Saves");
		return false;
	}

	return true;
}

bool SaveManager::clearOldSave() {
	if (!fmSave.emptyFile(getSaveFileDirectory())) {
		ccSave.consoleManager("error", "couldn't clear the Old Save");
		return false;
	}

	return true;
}

bool SaveManager::clearCurrentSave() {
	if (!fmSave.emptyFile(getCurrentSaveFileDirectory())) {
		ccSave.consoleManager("error", "couldn't clear the Current Save");
		return false;
	}

	return true;
}


bool SaveManager::readSave() {
	if (!isSafeToSave) {
		ccSave.consoleManager("error", "save load failed, unsafe to load save.");
		return false;
	}

	vector<string> saveDataCurrentTemp = getCurrentSaveData();
	readData(saveDataCurrentTemp, ssSave.getSaveFileDirectory());
	ccSave.consoleManager("update", "save loaded");
	return true;

}



bool SaveManager::replaceValueInCurrentSave(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = getCurrentSaveData();
	tempVector = fmSave.replaceValueInVector(tempVector, variableName_, newValue_);

	if (writeData(tempVector, ssSave.getCurrentSaveFileDirectory())) {
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
		string toAdd = fmSave.formatString(variableName_, value_);
		addToFile(toAdd, ssSave.getCurrentSaveFileDirectory());
		return true;

	} else {
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