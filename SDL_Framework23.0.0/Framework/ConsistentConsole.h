#pragma once
#include <iostream>



class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
protected:
	///	Variables
	bool isConsoleTextEnabled;
	int consoleTextVisibilityLevel;
		
	
public:
	
	ConsistentConsole();
	ConsistentConsole(int visibility);

	//	toggles the console text visibility
	void toggleConsoleText() { isConsoleTextEnabled = !isConsoleTextEnabled;  consoleManager("not error", "consoleText toggled"); }
	bool getConsoleTextState() { return isConsoleTextEnabled; }
	void setConsoleTextVisibility();


	///	Methods
	//	error, not error, update, or "". Then a message for context. ez.
	void consoleManager(const char* type, const char* MSG);
	//	red, blue, green, purple, cyan, yellow, clear
	void colour(const char* colour);
	//clears the console using system("cls");
	void clearConsole();

};

