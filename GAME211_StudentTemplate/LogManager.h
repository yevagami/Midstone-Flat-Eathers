#pragma once
#include "FileManager.h"


class LogManager : private FileManager {
public:
	bool logToFile(std::string content);

private:
	const char* createLogFileDir();
	bool logTo(string content, const char* fileDirectory);
	string giveDateTimeString();

protected:
	const char
		* logFileDir = "SaveData/logs/logs", //no extension
		* fileExtension = ".txt";
};