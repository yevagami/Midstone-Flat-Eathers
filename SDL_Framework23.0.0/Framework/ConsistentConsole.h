#pragma once
#include <iostream>


class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
public:
	//	starts the class with console text enabled
	ConsistentConsole();
	// starts the class with console text set to the provided bool
	ConsistentConsole(bool visibility);

	///	Methods
	//	error, not error, update, or "". Then a message for context. ez.
	bool consoleManager(const char* type, const char* MSG);
	//	red, blue, green, purple, cyan, yellow, pink, clear
	inline bool colour(const char* colour);
	//	clear, newline, indent
	inline bool colour(const char* colour, const char* modifier);
	//	clears the console using system("cls"); (literally just system("cls");)
	void clearConsole();

	//	sets the console text state to the provided bool
	void setConsoleState(bool state) { isConsoleTextEnabled = state; }
	//	returns the consoleText boolean state
	bool getConsoleState() { return isConsoleTextEnabled; }

protected:
	///	Variables
	bool isConsoleTextEnabled;
	//static std::map<std::string, std::string> types;
};

#pragma region constants
extern const char* clear;
extern const char* newline;
extern const char* indent;
extern const char* blue;
extern const char* cyan;
extern const char* green;
extern const char* purple;
extern const char* pink;
extern const char* yellow;
extern const char* red;

extern const char* bold;
extern const char* italic;

extern const char* error;
extern const char* update;
extern const char* safe;
extern const char* warning;
#pragma endregion