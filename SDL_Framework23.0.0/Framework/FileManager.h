#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


struct FileManager {
private:
	//	DO. NOT. USE. 
	bool deleteFromFile(string content, const char* fileDirectory);

public:
	///	Main Private Methods
	//	creates a file at the provided directory ex. "Folder\Folder\File.txt"
	bool createFile(const char* fileDirectory);
	//	write the provided vector<string> to the provided file directory
	bool writeData(vector<string>& savedData, const char* fileDirectory);
	//	forcefully load the provided vector<string> with the provided file directory file contents
	bool readData(vector<string>& savedData, const char* fileDirectory);

	//	parses the passed file, storing all the information into a vector of strings
	vector<string> parseTHIS(const char* fileDirectory);
	//	scans the provided file for the string 
	bool scanFileFor(const char* target, const char* fileDirectory);
	//	checks to see if the string contents already exists in the file, if not its added.
	bool addToFile(string content, const char* fileDirectory);


	///	Vector Methods
// return the value associated with the provided variableName in the vector.
	string scanVectorFor(vector<string> vector, const char* variableName_);
	//	replace the value with a provided newValue at the variableName's spot in the provided vector
	vector<string> replaceValueInVector(const char* variableName_, const char* newValue_, vector<string>& strings);
	//prints the provided string vector
	void printVectorString(vector<string> vector);


	///	String Methods
	// Formats the provided information into a Fancy Formatted String:tm:
	string formatString(const char* variableName, const char* value);
	//	allow for reading of variables, returning the value in a string
	string whatIs(const char* variableName, vector<string>& vector);
	//	allow for reading of variables, returning the value in a string
	string whatIs(const char* variableName, const char* fileDir);

};
