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
	{red, "\033[38;5;196m"},
	{blue, "\033[38;5;27m"},
	{green, "\033[38;5;46m"},
	{purple, "\033[38;5;129m"},
	{cyan, "\033[38;5;51m"},
	{yellow, "\033[38;5;226m"},
	{pink, "\033[38;5;213m"},
	{orange, "\033[38;5;202m"},
	{turquoise, "\033[38;5;80m"},
	{violet, "\033[38;5;93m"},
	{lime, "\033[38;5;154m"},
	{indigo, "\033[38;5;54m"},
	{peach, "\033[38;5;208m"},
	{maroon, "\033[38;5;88m"},
	{teal, "\033[38;5;23m"},
	{gold, "\033[38;5;220m"},
	{lavender, "\033[38;5;183m"},
	{olive, "\033[38;5;58m"},
	{coral, "\033[38;5;203m"},
	{mint, "\033[38;5;120m"},
	{rose, "\033[38;5;210m"},
	{steel, "\033[38;5;146m"},
	{navy, "\033[38;5;17m"}
	}; if (colours.find(colour_) == colours.end()) { return false; }

	std::cout 
		<< colours.at(colour_);	 

	return true;
}

inline bool ConsistentConsole::colour(const char* colour_, const char* modifier_) {
	static std::unordered_map<const char*, const char*> colours = {
	{clear, "\033[0m"},
	{red, "\033[38;5;196m"},
	{blue, "\033[38;5;27m"},
	{green, "\033[38;5;46m"},
	{purple, "\033[38;5;129m"},
	{cyan, "\033[38;5;51m"},
	{yellow, "\033[38;5;226m"},
	{pink, "\033[38;5;213m"},
	{orange, "\033[38;5;202m"},
	{turquoise, "\033[38;5;80m"},
	{violet, "\033[38;5;93m"},
	{lime, "\033[38;5;154m"},
	{indigo, "\033[38;5;54m"},
	{peach, "\033[38;5;208m"},
	{maroon, "\033[38;5;88m"},
	{teal, "\033[38;5;23m"},
	{gold, "\033[38;5;220m"},
	{lavender, "\033[38;5;183m"},
	{olive, "\033[38;5;58m"},
	{coral, "\033[38;5;203m"},
	{mint, "\033[38;5;120m"},
	{rose, "\033[38;5;210m"},
	{steel, "\033[38;5;146m"},
	{navy, "\033[38;5;17m"}
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

const char* red = "red";
const char* blue = "blue";
const char* green = "green";
const char* purple = "purple";
const char* cyan = "cyan";
const char* yellow = "yellow";
const char* pink = "pink";
const char* orange = "orange";
const char* turquoise = "turquoise";
const char* violet = "violet";
const char* lime = "lime";
const char* indigo = "indigo";
const char* peach = "peach";
const char* maroon = "maroon";
const char* teal = "teal";
const char* gold = "gold";
const char* lavender = "lavender";
const char* olive = "olive";
const char* coral = "coral";
const char* mint = "mint";
const char* rose = "rose";
const char* steel = "steel";
const char* navy = "navy";

const char* error = "error";
const char* not_error = "not error";
const char* update = "update";
const char* warning = "warning";
const char* debug = "debug";
#pragma endregion