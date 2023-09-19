#include "FileManager.h"
#include "ConsistentConsole.h"

ConsistentConsole ccFile;



bool FileManager::createFile(const char* fileDirectory) {
	fstream file(fileDirectory);
	if (file.fail()) {
		ccFile.consoleManager("error", "file failed to open");
		file.open(fileDirectory, ios::out);
		if (file.fail()) {	//creating the file if it doesn't exist
			ccFile.consoleManager("error", "file failed to be created");
			file.close();
			return false;
	
		}
		else {	//	 if it is created...
			file.close();
			return true;

		}

	}
	else {	 // if it does open...
		file.close();
		return true;

	}
}


bool FileManager::checkFile(const char* fileDirectory) {
	ifstream file(fileDirectory);
	return file.good();
}


vector<string> FileManager::parseTHIS(const char* fileDirectory) {
	vector<string> data;
	fstream file(fileDirectory, ios::in);

	// check if the file is open
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			// check if the line contains ":"
			if (line.find(":") != string::npos) {
				data.push_back(line);	//	add the whole line to data vector
			}
		}
		file.close();


	}
	else { ccFile.consoleManager("error", "Couldn't open saveFile in SaveManager::Parser"); }
	return data;

}


bool FileManager::writeData(vector<string>& savedData, const char* fileDirectory) {
	ofstream file(fileDirectory);
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
		ccFile.consoleManager("error", "file didn't open in writeData function");
		return false;
	}
}


bool FileManager::readData(vector<string>& savedData, const char* fileDirectory) {
	if (createFile(fileDirectory)) {
		if (writeData(savedData, fileDirectory)) {
			ccFile.consoleManager("not error", "file successfully loaded");
		}
		else { ccFile.consoleManager("error", "uh oh... file loadn't"); }
		return true;

	}
	else {
		ccFile.consoleManager("error", "save load failed, save file doesn't exist and cannot be created...");
		return false;

	}

}


bool FileManager::emptyFile(const char* fileDirectory) {
	ofstream file(fileDirectory, ios::trunc);
		//opens the file in truncate (t r u n c) mode
		file.close();
		return true;
}


bool FileManager::scanFileFor(const char* searchTarget, const char* fileDirectory) {
	ifstream file;
	file.open(fileDirectory);
	if (file.is_open()) {
		string line;


		while (getline(file, line)) {
			if (line.find(searchTarget) != string::npos) {
				file.close(); return true;
			}
		}
		file.close();
		return false;


	}
	else {
		ccFile.consoleManager("error", "scanFileFor failed, file cannot be opened");
		return false;
	}
}


bool FileManager::isEmpty(const char* fileDirectory) {
	ifstream file(fileDirectory); // open the file
	return file.peek() == ifstream::traits_type::eof(); // check if the file is empty
}


string FileManager::whatIs(const char* variableName, const char* fileDir) { 
	return scanVectorFor(parseTHIS(fileDir), variableName); 
}


void FileManager::printString(string string) { cout << string << "\n"; }


bool FileManager::addToFile(string content, const char* fileDirectory) {
	const char* contentcc = content.c_str();


	bool exists = scanFileFor(contentcc, fileDirectory);

	if (!exists) {
		ofstream outFile;
		// open the file in the given directory in append mode (allows edits)
		outFile.open(fileDirectory, ios::app);
		if (outFile.is_open()) {
			outFile << content << "\n";
			outFile.close();
			return true;


		}
		else {
			ccFile.consoleManager("error", "addToFile failed. cannot open file");
			return false;
		}
	}
}


bool FileManager::deleteFromFile(string content, const char* fileDirectory) {
	//	from ai
	//don't use. like fr dont.

	const char* contentcc = content.c_str();
	bool exists = scanFileFor(contentcc, fileDirectory);


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
				ccFile.consoleManager("error", "deleteLine failed. cannot open temporary file");
				return false;
			}
		}
		else {
			ccFile.consoleManager("error", "deleteLine failed. cannot open original file");
			return false;
		}
	}
	else {
		// Return false to indicate that the content does not exist in the file
		return false;
	}
}





string FileManager::scanVectorFor(vector<string> vector, const char* variableName_) {
	string variableName = variableName_;

	for (string string : vector) {
		// check if the string starts with the variable name, followed by a colon (formatting stuff)
		if (string.find(variableName + ": ") == 0) {
			// find the position of the square brackets in the string
			size_t pos1 = string.find('[');
			size_t pos2 = string.find(']');
			// if both positions exist, return the substring between them
			if (pos1 != string::npos && pos2 != string::npos) {
				return string.substr(pos1 + 1, pos2 - pos1 - 1);
			}
		}
	}

	return "";
}


vector<string> FileManager::replaceValueInVector(vector<string> vectorS, const char* variableName_, const char* newValue_) {
	string variableName = variableName_;
	string newValue = newValue_;
	vector<string> result;
	bool flag = false;

	for (int i = 0; i < vectorS.size(); i++) {
		string str = vectorS[i];
		if (str.find(variableName + ": ") == 0) {
			// find the position of the square brackets in the string
			size_t pos1 = str.find('[');
			size_t pos2 = str.find(']');
		
			// if both positions are valid, replace the substring between them with the new value, keeping the brackets
			if (pos1 != string::npos && pos2 != string::npos) {
				str.replace(pos1 + 1, pos2 - pos1 - 1, newValue);
				flag = true; }
		}
		result.push_back(str);



	} if (!flag) {
		ccFile.consoleManager("error", "no match or replacement was made for SaveManager::replaceValues"); }

	return result;
}


void FileManager::printVectorString(vector<string> vector) {
	if (!vector.empty()) {
		for (string string : vector) {
			cout << string << "\n";
		}
	}
	else {
		cout << "its empty\n";
	}

}


string FileManager::formatString(const char* variableName, const char* value) {
	string result;
	result += variableName;

	result += ": ";
	result += "[";
	result += value;
	result += "]";

	return result;
}

string FileManager::whatIs(const char* variableName, vector<string>& vector) {
	return scanVectorFor(vector, variableName);
}