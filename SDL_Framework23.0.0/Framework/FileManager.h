#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;



struct FileManager {
private:
	//	DO. NOT. USE. pls<3
	bool deleteFromFile(string content, const char* fileDirectory);

public:
	///	File Methods
	//	creates a file at the provided directory ex. "Folder\Folder\File.txt"
	bool createFile(const char* fileDirectory);
	//	checks if the file at the given directory exists
	bool checkFile(const char* fileDirectory);
	//	write the provided vector<string> to the provided file
	bool writeData(vector<string>& savedData, const char* fileDirectory);
	//	load the provided vector<string> with the provided file contents
	bool readData(vector<string>& savedData, const char* fileDirectory);
	// clears the given file
	bool emptyFile(const char* fileDirectory);

	//	adds the string to the file
	bool addToFile(string content, const char* fileDirectory);
	//	scans for the string in the file
	bool scanFileFor(const char* searchTarget, const char* fileDirectory);
	//	returns true if the file is empty
	bool isEmpty(const char* fileDirectory);


	///	Vector & String Methods
	//	parses the passed file, storing all the information into a vector of strings (raw parse)
	vector<string> parseTHIS(const char* fileDirectory);
	// formats the provided information into a Fancy Formatted String:tm:
	string formatString(const char* variableName, const char* value);
	//	replace the value with a provided newValue
	vector<string> replaceValueInVector(vector<string> vectorS, const char* variableName_, const char* newValue_);
	// scans the vector for the *value associated with* the provided variableName
	string scanVectorFor(vector<string> vector, const char* variableName_);

	//	prints the provided string vector
	void printVectorString(vector<string> vector);
	//	literally just prints a string. NOTHING fancy
	void printString(string string);

	//	reads the value associated with a variable from a VECTOR
	string whatIs(const char* variableName, vector<string>& vector);
	//	reads the value associated with a variable from a FILE
	string whatIs(const char* variableName, const char* fileDir);

};
