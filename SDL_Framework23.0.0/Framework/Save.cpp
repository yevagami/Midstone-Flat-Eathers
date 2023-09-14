#include "Save.h"

void Save::consoleManager(const char* type, const char* MSG) {
	if (type == "error") {
		cerr << "\033[31m" << "Error Occured: [" << MSG << "]\033[0m" << endl;
	} else if (type == "not error") {
		cerr << "\033[32m" << "This might be useful: [" << MSG << "]\033[0m" << endl; }
	else if (type == "" || type == " ") {
		cout	<< "\033[33m" << "[" << MSG << "]\033[0m" << endl; }
}

void Save::createSaveFile() {
	//	try to open the file
	fstream file(saveFile);
	if (file.fail()) {
		//	if it doesn't open...
		consoleManager("error", "saveData failed to open");
		file.open(saveFile, ios::out); //creating the file if it doesn't exist
		if (file.fail()) {
			//	if it isn't created...
			consoleManager("error", "saveData failed to be created"); 
			file.close();
		} else { 
			//	if it is created...
			consoleManager("not error", "saveData successfully created!"); }
		file.close();
	} else {
		//	if it does open...
		consoleManager("not error", "saveData opened");
		file.close();
	}
}

void Save::applySaveData() {

}

void Save::writeSaveData() {

}


void Save::parseTHIS(vector<string> data, const char* fileToOpen) {
	fstream file(fileToOpen, ios::in);

	// check if the file is open
	if (file.is_open()) {
		string line;

		// read each line of the file until the end of file is reached
		while (getline(file, line)) {
			// check if the line contains ":"
			if (line.find(":") != string::npos) {
				// find the position of ":"
				int pos = line.find(":");
				string value = line.substr(pos + 1);

				// check if the value contains "[" and "]", as well as " ".
				if (value.find("[") != string::npos && value.find("]") != string::npos) {
					// remove "[" and "]" + leading and trailing spaces
					value.erase(value.find("["), 1); // remove "["
					value.erase(value.find("]"), 1); // remove "]"
					value = value.substr(value.find_first_not_of(" ")); // remove leading spaces
					value = value.substr(0, value.find_last_not_of(" ") + 1); // remove trailing spaces
				}
				// add value to data vector
				data.push_back(value);
			}
		}
		file.close();

		// [debug] display the data
		cout << "Information from the Save File:\n";
		for (int i = 0; i < data.size(); i++) { cout << data[i] << "\n"; }
	}
	else { consoleManager("error", "Couldn't open saveFile in Save::Parser"); }


}
