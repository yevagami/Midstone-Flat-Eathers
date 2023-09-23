#pragma once
#include <iostream>



class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
protected:
	///	Variables
	bool isConsoleTextEnabled;
		
	
public:
	//	starts the class with console text enabled
	ConsistentConsole();
	// starts the class with console text set to the provided bool
	ConsistentConsole(bool visibility);


	//	sets the console text state to the provided bool
	inline void setConsoleState(bool state) { isConsoleTextEnabled = state; }
	//	returns the consoleText boolean state
	inline bool getConsoleState() { return isConsoleTextEnabled; }


	///	Methods
	//	error, not error, update, or "". Then a message for context. ez.
	inline void consoleManager(const char* type, const char* MSG);
	//	red, blue, green, purple, cyan, yellow, pink, clear
	inline void colour(const char* colour);
	//	clears the console using system("cls");
	inline void clearConsole();

};