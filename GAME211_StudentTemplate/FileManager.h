#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//new Naming Convention (in progress)
// file methods:
	//	fileCreate
	// fileCheck
	// fileRead 
	// fileWrite
	// fileEmpty
	// fileInsert
	// 
//	boolean methods: (add support for both file and vectors)
	//	isEqual (file)
	// isEqual (vstr)
	// isHere (file
	// isHere (vstring)
	// isWhat (from file)
	// isWhat (from vector<string>
	// isEmpty
//	replaces
	//	replaceValue (in file)
	// replaceValue (in vector<string>)
	// 
//	vector methods:
	//	parseTHIS
	// scanVectorFor (vectorGetAssociatedValue)
	//
//	string methods:
	//	formatString (stringReformatForSerialization)
	//	

struct FileManager {
private:
	//	DO. NOT. USE. pls<3
	bool deleteFromFile(string content, const char* fileDirectory);

public:
	///	File Methods
		///	Basic File Manipulation
	//	creates a file at the provided directory ex. "Folder\Folder\File.txt"
	bool fileCreate(const char* fileDirectory);
	//	checks if the file at the given directory exists
	bool fileCheck(const char* fileDirectory);
	//	load the provided vector<string> with the provided file contents
	bool fileRead(vector<string>& savedData, const char* fileDirectory);
	//	write the provided vector<string> to the provided file
	bool fileWrite(vector<string>& savedData, const char* fileDirectory);
	// clears the given file
	bool fileEmpty(const char* fileDirectory);
	//	adds the string to the file
	bool fileInsert(string content, const char* fileDirectory);

	//	replace the variable's value in the file with a provided newValue
	bool replaceValue(const char* variable, const char* newValue, const char* fileDirectory);
	//	replace the variable's value in the vector with a provided newValue
	vector<string> replaceValue(const char* variableName_, const char* newValue_, vector<string>& vectorS);

		/// File-Based Operations
	//	scans the file for the search variable and value. if the value in the file == the provided value, return true
	inline bool isEqual(const char* variable, const char* value, const char* fileDirectory);
	//	scans the vector for the search variable and value. if the value in the vector == the provided value, return true
	inline bool isEqual(const char* variable, const char* value, vector<string> vString);
	//	scans the file for the search string. returns a bool
	bool isHere(const char* searchTarget, const char* fileDirectory);
	//	scans the vector for the search string. returns a bool
	bool isHere(const char* searchTarget, vector<string> vString);
	//	reads the VALUE associated with a variable from a VECTOR
	string isWhat(const char* variableName, vector<string>& vector);
	//	reads the VALUE associated with a variable from a FILE
	string isWhat(const char* variableName, const char* fileDir);
	//	if the file is empty, return a bool
	bool isEmpty(const char* fileDirectory);


	///	Vector & String Methods
		///	Basic Vector<string> Manipulation
	//	parses the passed file, storing all the information into a vector of strings (raw parse)
	vector<string> parseTHIS(const char* fileDirectory);
	// scans the vector for the *value associated with* the provided variableName
	string scanVectorFor(const vector<string> vector, const char* variableName_);
		///	Basic String Manipulation
	// formats the provided information into a Fancy Formatted String:tm:
	string stringReformat(const char* variableName, const char* value);
};

//	entity maps in EntityMap.h