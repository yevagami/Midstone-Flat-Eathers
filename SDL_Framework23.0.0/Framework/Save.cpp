#include "Save.h"

Save::Save(){
	isConsoleTextEnabled = true;


	//	safeguard in the constructor (WIP)
	if (createFile(saveFile) && createFile(currentSaveFile)) {
		isSafeToSave = true;
	}

}



Save::~Save() {
	isSafeToSave = false;
}



void Save::consoleManager(const char* type, const char* MSG) {
	if (isConsoleTextEnabled) {
		if (type == "error") {
			cerr << "\033[31m" << "Error Occured: [" << MSG << "]\033[0m" << endl; }
		else if (type == "not error") {
			cerr << "\033[32m" << "Update: [" << MSG << "]\033[0m" << endl; }

		else if (type == "" || type == " ") {
			cout << "\033[33m" << "Update: [" << MSG << "]\033[0m" << endl; }


		else {
			cerr << "\033[31m" << "error in the error handler : O *dun dun dun*" << "\033[0m" << endl; }
	} }



bool Save::createFile(const char* fileDirectory) {
	fstream file(fileDirectory);
	if (file.fail()) {
		consoleManager("error", "file failed to open");
		file.open(saveFile, ios::out);
		if (file.fail()) {	//creating the file if it doesn't exist
			consoleManager("error", "file failed to be created");
			file.close();
			return false;

		} else {	//	 if it is created...
			file.close();
			return true;

		}

	} else {	 // if it does open...
		file.close();
		return true;

	}
}



bool Save::loadGame() {
	if (isSafeToSave) {
		vector<string> saveDataCurrentTemp = getCurrentSaveData();
		readData(saveDataCurrentTemp, saveFile);
		consoleManager("update", "save load successful");
		return true;

	}
	else {
		consoleManager("error", "save load failed, unsafe to load save.");
		return false;

	}
}



bool Save::saveGame() {
	if (isSafeToSave) {
		consoleManager("", "goofiness aside, it's ready to save");
		vector<string> saveDataCurrent = getCurrentSaveData();
		vector<string> saveDataOld = getOldSaveData();

		if (isConsoleTextEnabled) {
			debugFunc dF;
			consoleManager("", "replacing:");
			dF.printVectorString(saveDataOld);
			consoleManager("", "with:");
			dF.printVectorString(saveDataCurrent);
		}

		//copies the contents from the temp Save file to the main Save file.
		if (writeData(saveDataCurrent, saveFile)) {
			consoleManager("update", "file successfully saved");
		} else { consoleManager("error", "uh oh... file saved't"); }
		return true;


	}else {
		consoleManager("error", "save game failed, save file doesn't exist and cannot be created...");	
		return false; } 
}

bool Save::addValueToCurrentSave(const char* variableName_, const char* value_) {
	if (!scanFileFor(variableName_, currentSaveFile)) {
		string toAdd = formatString(variableName_, value_);
		addToFile(toAdd, currentSaveFile);

	} else {
		consoleManager("error", "variable already exists inside the current save");
	}





	return false;
}



bool Save::replaceValueInCurrentSave(const char* variableName_, const char* newValue_) {
	vector<string> tempVector = getCurrentSaveData();
	tempVector = replaceValueInVector(variableName_, newValue_, tempVector);
	if (writeData(tempVector, currentSaveFile)) {
		return true;



	} else {
		return false; }
}



vector<string> Save::parseTHIS(const char* fileDirectory) {
	vector<string> data;
	fstream file(fileDirectory, ios::in);

	// check if the file is open
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			// check if the line contains ":"
			if (line.find(":") != string::npos) {
				data.push_back(line);	//	add the whole line to data vector
			} }
		file.close();


	} else { consoleManager("error", "Couldn't open saveFile in Save::Parser"); }
	return data;

}



bool Save::writeData(vector<string>& SavedData, const char* fileDirectory) {
	ofstream file(fileDirectory);
	if (file.is_open()) {
		// loop through the vector elements
		for (const auto& element : SavedData) {
			// write each element to the file, followed by a newline
			file << element << "\n";
		}
		file.close();
		return true;


	} else {
		consoleManager("error", "file didn't open in writeData function");
		return false;
	}

}



bool Save::readData(vector<string>& saveData, const char* fileDirectory) {
	if (createFile(fileDirectory)) {
		if (writeData(saveData, fileDirectory)) {
			consoleManager("update", "file successfully loaded"); }
		else { consoleManager("error", "uh oh... file loadn't"); }
		return true;

	} else {
		consoleManager("error", "save load failed, save file doesn't exist and cannot be created...");
		return false; 
	
	}

}

bool Save::scanFileFor(const char* target, const char* fileDirectory) {
	ifstream file;
	file.open(fileDirectory);
	if (file.is_open()) {
		string line;


		while (getline(file, line)) {
			if (line.find(target) != string::npos) {
				file.close(); return true;
			} }
		file.close();
		return false;


	} else {
		consoleManager("error", "scanFileFor failed, file cannot be opened");
		return false;
	}
}

bool Save::addToFile(string content, const char* fileDirectory) {
	const char* contentCC = content.c_str();


	bool exists = scanFileFor(contentCC, fileDirectory);

	if (!exists) {
		ofstream outFile;
		// open the file in the given directory in append mode (allows edits)
		outFile.open(fileDirectory, ios::app);
		if (outFile.is_open()) {
			outFile << content << "\n";
			outFile.close();
			return true;


		} else {
			consoleManager("error", "addToFile failed. cannot open file");
			return false;
		}
	}
}

bool Save::deleteFromFile(string content, const char* fileDirectory) {
	//	from ai


	const char* contentCC = content.c_str();
	bool exists = scanFileFor(contentCC, fileDirectory);


	if (exists) {
		ifstream inFile;
		inFile.open(fileDirectory);
		if (inFile.is_open()) {
			// Create a temporary file name
			string tempFileName = "temp.txt";
			// Create an output file stream object
			ofstream outFile;
			// Open the temporary file in write mode
			outFile.open(tempFileName);
			// Check if the temporary file is opened successfully
			if (outFile.is_open()) {
				// Create a string variable to store each line of the file
				string line;
				// Loop through the file line by line
				while (getline(inFile, line)) {
					// Check if the content is found in the current line
					if (line.find(content) == string::npos) {
						// If not, then write the line to the temporary file
						outFile << line << "\n";
					}
				}
				// Close both files
				inFile.close();
				outFile.close();
				// Remove the original file
				remove(fileDirectory);
				// Rename the temporary file to the original file name
				rename(tempFileName.c_str(), fileDirectory);

				return true;


			}
			else {
				consoleManager("error", "deleteLine failed. cannot open temporary file");
				return false;
			}
		}
		else {
			consoleManager("error", "deleteLine failed. cannot open original file");
			return false;
		}
	}
	else {
		// Return false to indicate that the content does not exist in the file
		return false;
	}
}



string Save::scanVectorFor(vector<string> vector, const char* variableName_) {
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


	return "";
}



vector<string> Save::replaceValueInVector(const char* variableName_, const char* newValue_, vector<string>& strings) {
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



	} if (!flag) { 
		consoleManager("error", "no match or replacement was made for Save::replaceValues"); 
	}


	return result;
}

string Save::formatString(const char* variableName, const char* value) {
	string result;
	result += variableName;

	result += ": ";
	result += "[";
	result += value;
	result += "]";

	return result;
}
