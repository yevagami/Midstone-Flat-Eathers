#include "FileManager.h"
#include "ConsistentConsole.h"
#include <fstream>

//#include <unordered_map>


ConsistentConsole ccFile(true);



bool FileManager::fileCreate(const char* fileDirectory) {
	fstream file(fileDirectory);
	if (file.fail()) {
		ccFile.log("error", "file failed to open");
		
		file.open(fileDirectory, ios::out);
		if (file.fail()) {	//creating the file if it doesn't exist
			ccFile.log("error", "file failed to be created");
			return false;
		} }

	file.close();
	return true;
}


bool FileManager::fileCheck(const char* fileDirectory) {
	ifstream file(fileDirectory);
	return file.good();
}


vector<string> FileManager::parseTHIS(const char* fileDirectory) {
	vector<string> data;
	fstream file(fileDirectory, ios::in);

	// check if the file is open
	if (file.fail()) {
	ccFile.log("error", "Couldn't open saveFile in SaveManager::Parser");
	return data; }
	string line;
	
	while (getline(file, line)) {
		// check if the line contains ":"
		if (line.find(":") != string::npos) {
			data.push_back(line);	//	add the whole line to data vector
		} }

	file.close();
	return data;
}


bool FileManager::fileWrite(vector<string>& savedData, const char* fileDirectory) {
	ofstream file(fileDirectory);

	if (file.fail()) {
		ccFile.log("error", "file didn't open in writeData function");
		return false; }

	// loop through the vector elements
	for (const auto& element : savedData) {
		// write each element to the file, followed by a newline
		file << element << "\n";
	}

	file.close();
	return true;
}


bool FileManager::fileLoadToVector(vector<string>& savedData, const char* fileDirectory) {
	if (!fileCheck(fileDirectory)) {
		ccFile.log("error", "uh oh... file loadn't");
		return false;
	}

	if (!fileWrite(savedData, fileDirectory)) {
		ccFile.log("error", "save load failed, save file doesn't exist and cannot be created...");
		return false;
	}


	ccFile.log("update", "file loaded");
	return true;
		
}



bool FileManager::fileEmpty(const char* fileDirectory) {
	///	doesnt work haha (idk)
	ofstream file(fileDirectory, ios::trunc);
	//opens the file in truncate (t r u n c) mode
	if (file.fail()) { 
		ccFile.log(error, "no trunc :( (file didn't empty"); 
		return false; 
	}

	file.close();
	file.open(fileDirectory, ios::out | ios::trunc);  // reopen for writing and truncation

	if (!file.is_open()) {
		ccFile.log(error, "no trunc");
		return false;
	}

	file.close();
	return true;
}


bool FileManager::isHere(const char* searchTarget, const char* fileDirectory) {
	ifstream file(fileDirectory);

	if (!file.is_open()) {
		ccFile.log("error", "failed to open file for searching :(");
		return false;
	}

	string line;
	while (getline(file, line)) {
		if (line.find(searchTarget) != string::npos) {
			file.close();
			return true;
		}
	}

	file.close();
	return false;
}

bool FileManager::isHere(const char* searchTarget, vector<string> vString) {
	for (std::string& str : vString) {
		if (str.find(searchTarget) != std::string::npos) {
			return true;
		} 
	}
	return false;
}


bool FileManager::isEmpty(const char* fileDirectory) {
	ifstream file(fileDirectory); // open the file
	return file.peek() == ifstream::traits_type::eof(); // check if the file is empty
}


bool FileManager::isEqual(const char* variable, const char* value, const char* fileDirectory) {
	return std::string(value) == isWhat(variable, fileDirectory);
}


bool FileManager::isEqual(const char* variable, const char* value, vector<string> vString) {
	return std::string(value) == isWhat(variable, vString);
}


string FileManager::isWhat(const char* variableName, const char* fileDir) { 
	return scanVectorFor(parseTHIS(fileDir), variableName); 
}


bool FileManager::fileInsert(string content, const char* fileDirectory) {
	if (isHere(content.c_str(), fileDirectory)) {
		return false; // Content already exists in the file.
	}

	ofstream outFile(fileDirectory, ios::app);
	if (outFile.is_open()) {
		outFile << content << "\n";
		return true;
	}
	else {
		ccFile.log("error", "addToFile failed. cannot open file :(");
		return false;
	}
}

bool FileManager::replaceValue(const char* variable, const char* newValue, const char* fileDirectory) {
	std::ifstream inputFile(fileDirectory);
	if (inputFile.fail()) {
		ccFile.log(error, "couldn't open file to replace variable in");
		return false;
	}
	std::string line;
	std::string fileContents;
	bool didReplace = false;

	while (getline(inputFile, line)) {
		size_t pos = line.find(variable);
		if (pos != std::string::npos) {
			size_t pos1 = line.find('[');
			size_t pos2 = line.find(']');
			if (pos1 != std::string::npos && pos2 != std::string::npos) {
				line.replace(pos1 + 1, pos2 - 1, newValue);
				didReplace = true;
			}
		}
		fileContents += line + "\n";
	}
	inputFile.close();

	if (didReplace) {
		std::ofstream outputFile(fileDirectory);
		if (!outputFile.is_open()) {
			std::cerr << "Error: Could not open file " << fileDirectory << " for writing." << std::endl;
			return false;
		}
		outputFile << fileContents;
		outputFile.close();
	}

	return didReplace;

}


string FileManager::scanVectorFor(const vector<string> vector, const char* variableName_) {
	string variableName = variableName_;

	for (const string string : vector) {
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


vector<string> FileManager::replaceValue(const char* variableName_, const char* newValue_, vector<string>& vectorS) {
	string variableName = variableName_;
	string newValue = newValue_;
	vector<string> result;
	bool flag = false;

	for (const string& str : vectorS) {
		if (str.find(variableName + ": ") == 0) {
			// find the position of the square brackets in the string
			size_t pos1 = str.find('[');
			size_t pos2 = str.find(']');

			// if both positions are valid, replace the substring between them with the new value, keeping the beautiful brackets
			if (pos1 != string::npos && pos2 != string::npos) {
				string modifiedStr = str;
				modifiedStr.replace(pos1 + 1, pos2 - pos1 - 1, newValue);
				result.push_back(modifiedStr);
				flag = true;
			}
		} else {
			result.push_back(str);
		}
	}

	if (!flag) {
		ccFile.log("error", "no match or replacement was made for SaveManager::replaceValues :(");
	}

	return result;
}


string FileManager::stringReformat(const char* variableName, const char* value) {
	string result;
	result += variableName;

	result += ": ";
	result += "[";
	result += value;
	result += "]";

	return result;
}


string FileManager::isWhat(const char* variableName, vector<string>& vector) {
	return scanVectorFor(vector, variableName);
}


bool FileManager::deleteFromFile(string content, const char* fileDirectory) {
	//	from ai
	//don't use. like fr dont.

	const char* contentcc = content.c_str();
	bool exists = isHere(contentcc, fileDirectory);


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
				ccFile.log("error", "deleteLine failed. cannot open temporary file");
				return false;
			}
		}
		else {
			ccFile.log("error", "deleteLine failed. cannot open original file");
			return false;
		}
	}
	else {
		// Return false to indicate that the content does not exist in the file
		return false;
	}
}