#include "ConsistentConsole.h"
#pragma region constants
const char* clear = "clear";
const char* newline = "newline";
const char* indent = "indent";
const char* blue = "blue";
const char* cyan = "cyan";
const char* green = "green";
const char* purple = "purple";
const char* pink = "pink";
const char* yellow = "yellow";
const char* red = "red";

const char* bold = "bold";
const char* italic = "italic";

const char* error = "error";
const char* update = "update";
const char* warning = "warning";
const char* safe = "safe";
#pragma endregion
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

//	keep this LOW... [header includes]
#include "FileManager.h"

//	class instances and namespaces
FileManager ccFile;
using namespace std;



	///	Console Functions
#pragma region constructors
ConsistentConsole::ConsistentConsole() {
	isConsoleTextEnabled = true;
}

ConsistentConsole::ConsistentConsole(bool visibility){
	isConsoleTextEnabled = visibility;
}
#pragma endregion


bool ConsistentConsole::consoleManager(const char* type, const char* MSG) {
	if (!isConsoleTextEnabled) { return false; }

	static map<const char*, const char*> types = {
	{"error", red},
	{"update", green},
	{"warning", yellow},
	{"safe", purple},
	};	if (types.find(type) == types.end()) { return false; }

	ostringstream formattedString;
	colour(types.at(type));
	formattedString	//	omg its the string stream!!1!
		<< type	//	format
		<< ": ["	//	the
		<< MSG	//	string 
		<< "]";	//	stream
	cout << formattedString.str() 	<< endl;	//	the string:tm:
	colour(clear);
	return true;
	//log(formattedString.str().c_str());
}


#pragma region formatting
inline bool ConsistentConsole::colour(const char* colour) {
	static map<const char*, const char*> colours = {
	{clear, "\033[0m"},
	{red, "\033[31m"},
	{blue , "\033[34m"},
	{green, "\033[32m"},
	{purple, "\033[35m"},
	{cyan, "\033[36m"},
	{yellow, "\033[33m"},
	{pink, "\033[95m"}
	}; if (colours.find(colour) == colours.end()) { return false; }

	cout 
		<< colours.at(colour);	 

	return true;
}

inline bool ConsistentConsole::colour(const char* colour, const char* modifier) {
	static map<const char*, const char*> colours = {
	{clear, "\033[0m"},
	{red, "\033[31m"},
	{blue , "\033[34m"},
	{green, "\033[32m"},
	{purple, "\033[35m"},
	{cyan, "\033[36m"},
	{yellow, "\033[33m"},
	{pink, "\033[95m"}
	}; if (colours.find(colour) == colours.end()) { return false; }

	static map<const char*, const char*> modifiers = {
		{clear, "\033[0m"},
		{newline, "\n"},
		{indent, "\t"},
	}; if (modifiers.find(modifier) == modifiers.end()) { return false; }

	cout
		<< colours.at(colour)
		<< modifiers.at(modifier);

	return true;
}


void ConsistentConsole::clearConsole() { cout << "\e[2J"; }


void ConsistentConsole::log(const char* logTHIS) {
	const char* logFile = "SaveData/logs/log.txt";
	ccFile.logTo(logTHIS, logFile);
}
#pragma endregion