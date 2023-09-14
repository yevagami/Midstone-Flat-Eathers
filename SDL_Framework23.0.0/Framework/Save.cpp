#include "Save.h"

void Save::consoleManager(const char* type, const char* MSG) {
	if (type == "error") {
		cerr << "\033[31m" << "Error Occured: [" << MSG << "]\033[0m" << endl;
	}
	else if (type == "not error") {
		cerr << "\033[32m" << "This might be useful: [" << MSG << "]\033[0m" << endl;
	}
}

void Save::readSaveData() {
	//open the file
	fstream file(saveFile);
	if (file.fail()) {
		//if it doesn't open...
		consoleManager("error", "saveData failed to open");
		file.open(saveFile, ios::out); //creating the file if it doesn't exist
		if (file.fail()) {
			//if it isn't created...
			consoleManager("error", "saveData failed to be created"); 
		}else { 
			//if it is created...
			consoleManager("not error", "saveData successfully created!"); }
	}

	else {
		//if it does open...
		consoleManager("not error", "saveData opened");
	}


	//read the file and store the necessary data in 


}

void Save::applySaveData()
{
}

void Save::writeSaveData()
{
}

string Save::parseTHIS() {
	
	
	return string();
}
