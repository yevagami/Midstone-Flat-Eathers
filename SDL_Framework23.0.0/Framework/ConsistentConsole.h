#pragma once
#include <iostream>
using namespace std;


class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
protected:
	///	Variables
	bool isConsoleTextEnabled;

public:
	void toggleConsoleText() { isConsoleTextEnabled = !isConsoleTextEnabled;  consoleManager("not error", "consoleText toggled"); }
	bool getConsoleTextState() { return isConsoleTextEnabled; }


	/// Methods
	void consoleManager(const char* type, const char* MSG);
	void colour(const char* colour);

};

