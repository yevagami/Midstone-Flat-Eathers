#include "ConsistentConsole.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
//header includes:

//	class instances and namespaces
//using namespace std;



	///	Console Functions
#pragma region constructor
ConsistentConsole::ConsistentConsole(bool visibility, const char* whereAmI_) {
	isConsoleTextEnabled = visibility;
	if(isConsoleTextEnabled) {
		colour(purple);
		std::cout <<"Consistent Console Initialized at " << whereAmI_;
		colour(clear, newline);
	}
}
#pragma endregion

bool ConsistentConsole::log(const char* type_, const char* msg_, const std::string& variable_) {
	if (!isConsoleTextEnabled) { return false; }

	static std::unordered_map<const char*, const char*> types = {
		{error, red},
		{update, green},
		{debug, blue},
		{warning, yellow},
		{not_error, purple},
	}; if (types.find(type_) == types.end()) { return false; }

	colour(types.at(type_));

	std::ostringstream formattedString; const char* specialMessage = "";
	if (strcmp(type_, "error") == 0) {
		specialMessage = "[error] "; }
	else if (strcmp(type_, "update") == 0) {
		specialMessage = "[update] "; }
	else if (strcmp(type_, "warning") == 0) {
		specialMessage = "[uh oh] "; }
	else if (strcmp(type_, "not error") == 0) {
		specialMessage = ""; }
	else if (strcmp(type_, "debug") == 0) {
		specialMessage = "[debug] "; }

	formattedString
		<< specialMessage
		<< "[" << msg_ << "]";

	if(!variable_.empty()) { formattedString << " " << "[" << variable_ << "]"; }

	std::cout << formattedString.str() << std::endl;
	
	colour(clear);
	return true;
}

#pragma region formatting
inline bool ConsistentConsole::colour(const char* colour_) {
	static std::unordered_map<const char*, const char*> colours = {
	{clear, "\033[0m"},
	{red, "\033[31m"},
	{blue , "\033[34m"},
	{green, "\033[32m"},
	{purple, "\033[35m"},
	{cyan, "\033[36m"},
	{yellow, "\033[33m"},
	{pink, "\033[95m"}
	}; if (colours.find(colour_) == colours.end()) { return false; }

	std::cout 
		<< colours.at(colour_);	 

	return true;
}

inline bool ConsistentConsole::colour(const char* colour_, const char* modifier_) {
	static std::unordered_map<const char*, const char*> colours = {
		{clear, "\033[0m"},
		{red, "\033[31m"},
		{blue , "\033[34m"},
		{green, "\033[32m"},
		{purple, "\033[35m"},
		{cyan, "\033[36m"},
		{yellow, "\033[33m"},
		{pink, "\033[95m"}
	}; if (colours.find(colour_) == colours.end()) { return false; }

	static std::unordered_map<const char*, const char*> modifiers = {
		{clear, "\033[0m"},
		{newline, "\n"},
		{indent, "\t"},
		{blink, "\033[6m"},
		{italic, "\033[3m"},
		{bold, "\033[1m"},
	}; if (modifiers.find(modifier_) == modifiers.end()) { return false; }

	std::cout
		<< colours.at(colour_)
		<< modifiers.at(modifier_);

	return true;
}

void ConsistentConsole::clearConsole() { std::cout << "\e[2J"; }
#pragma endregion

#pragma region constants
const char* clear = "clear";
const char* newline = "newline";
const char* indent = "indent";
const char* bold = "bold";
const char* italic = "italic";
const char* blink = "blink";

const char* blue = "blue";
const char* cyan = "cyan";
const char* green = "green";
const char* purple = "purple";
const char* pink = "pink";
const char* yellow = "yellow";
const char* red = "red";

const char* error = "error";
const char* not_error = "not error";
const char* update = "update";
const char* warning = "warning";
const char* debug = "debug";
#pragma endregion