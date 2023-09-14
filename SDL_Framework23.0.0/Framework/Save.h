#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


//sava data formatting:
//variableName: [data]
//otherVarName: [data]

//currentHealth, maxHealth, level;


class Save
{
	vector <string> tempVector;
	string tempString,
		  tempString2;

	string saveFile = "SaveData/saveData.txt"; //dir to the save file

public:

	void consoleManager(const char* type, const char* MSG);


	void readSaveData();
	void applySaveData();
	void writeSaveData();

	string parseTHIS();



};

