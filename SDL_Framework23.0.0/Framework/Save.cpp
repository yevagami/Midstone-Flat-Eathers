#include "Save.h"
#include "debugFunc.h"

void Save::consoleManager(const char* type, const char* MSG) {
	if (type == "error") {
		cerr << "\033[31m" << "Error Occured: [" << MSG << "]\033[0m" << endl;
	} else if (type == "not error") {
		cerr << "\033[32m" << "So Silly: [" << MSG << "]\033[0m" << endl; }
	else if (type == "" || type == " ") {
		cout	<< "\033[33m" << "[" << MSG << "]\033[0m" << endl; }


	else {
		cerr << "\033[31m" << "error in the error handler : O *dun dun dun*" << "\033[0m" << endl; }
}


bool Save::createFile(const char* fileDir) {
	fstream file(fileDir);
	if (file.fail()) {
		//	if it doesn't open...
		consoleManager("error", "file failed to open");
		file.open(saveFile, ios::out); //creating the file if it doesn't exist
		if (file.fail()) {
			//	if the file isn't created...
			consoleManager("error", "file failed to be created");
			file.close();
			return false;
		} else {
			//	if it is created...
			consoleManager("not error", "file successfully created!");
			file.close();
			return true;
		}

	} else {
		//	if it does open...
		consoleManager("not error", "file opened");
		file.close();
		return true;
	}
}


bool Save::loadGame() {
	if (createFile(saveFile)) {
		vector<string> saveDataOld = parseTHIS(saveFile); // save the full saveFile into a vector<string>
		vector<string> saveDataNew = parseTHIS(tempSaveFile); // save the full tempSaveFile into a vector<string>

		if (writeData(saveDataOld, tempSaveFile)) {
			consoleManager("not error", "file successfully loaded"); }
		else { consoleManager("error", "uh oh... file loadn't"); }
		return true;

	}
	else {
		consoleManager("error", "save load failed, save file doesn't exist and cannot be created...");
		return false;
	}
}

bool Save::saveGame() {
	if (createFile(saveFile)) {
		consoleManager("", "goofiness aside, it's ready to save");
		vector<string> saveDataOld = parseTHIS(saveFile); // save the full saveFile into a vector<string>
		vector<string> saveDataNew = parseTHIS(tempSaveFile); // save the full tempsavefile into a vector<string>

		debugFunc dF;
		dF.printVectorString(saveDataOld);
		dF.printVectorString(saveDataNew);

		//copies the contents from the temp save file to the main save file.
		if (writeData(saveDataNew, saveFile)) {
			consoleManager("not error", "file successfully saved");
		} else { consoleManager("error", "uh oh... file saven't"); }



		return true;
	}else {
		consoleManager("error", "save game failed, save file doesn't exist and cannot be created...");	
		return false;
	} 
}

void Save::replaceValueForSaving(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = parseTHIS(tempSaveFile);
	tempVector = replaceValue(variableName_, newValue_, tempVector);
	writeData(tempVector, tempSaveFile);
}




vector<string> Save::parseTHIS(const char* fileDir) {
	vector<string> data;
	fstream file(fileDir, ios::in);

	// check if the file is open
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			// check if the line contains ":"
			if (line.find(":") != string::npos) {
				data.push_back(line);	//	add the whole line to data vector
			} }
		file.close();
	}
	else { consoleManager("error", "Couldn't open saveFile in Save::Parser"); }
	
	return data;
}


bool Save::writeData(vector<string>& savedData, const char* fileDir) {
	ofstream file(fileDir);
	if (file.is_open()) {
		// loop through the vector elements
		for (const auto& element : savedData) {
			// write each element to the file, followed by a newline
			file << element << "\n";
		}
		file.close();
		return true;
	}
	else {
		consoleManager("error", "file didn't open in writeData function");
		return false;
	}

}


string Save::getValue(vector<string> vector, const char* variableName_) {
	string variableName = variableName_;

	for (string string : vector) {
		// check if the string starts with the variable name, followed by a colon and a space
		if (string.find(variableName + ": ") == 0) {
			// find the position of the square brackets in the string
			size_t pos1 = string.find('[');
			size_t pos2 = string.find(']');
			// if both positions exist, return the substring between them
			if (pos1 != string::npos && pos2 != string::npos) {
				return string.substr(pos1 + 1, pos2 - pos1 - 1);
			} }
	}

	//	if nothing is found, return an empty string
	return "";
}


vector<string> Save::replaceValue(const char* variableName_, const char* newValue_, vector<string>& strings) {
	string variableName = variableName_;
	string newValue = newValue_;
	vector<string> result;
	bool flag = false;

	for (int i = 0; i < strings.size(); i++) {
		string str = strings[i];
		if (str.find(variableName + ": ") == 0) {
			// find the position of the square brackets in the string
			size_t pos1 = str.find('[');
			size_t pos2 = str.find(']');
			// if both positions are valid, replace the substring between them with the new value, keeping the brackets
			if (pos1 != string::npos && pos2 != string::npos) {
				str.replace(pos1 + 1, pos2 - pos1 - 1, newValue);
				flag = true; } }
	
		result.push_back(str);


	} if (!flag) { consoleManager("error", "no match or replacement was made for Save::replaceValues"); }

	return result;
}