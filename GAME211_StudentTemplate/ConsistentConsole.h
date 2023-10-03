#pragma once

/// <summary>
/// The Console Message Management Class
/// 
///		Possible Constructors:
/// - default | visibility = true, logging = false
/// - visibility constructor | visibility = your choice, logging = false
/// - visibility and logging constructor | visibility and logging = your choice
/// 
///		Main Methods:
/// - consoleManager
/// - colour
/// 
///		Goals:
/// - cleaning up the console with consistency, colours, and confetti! (sans confetti)
/// - allow for console messages to be togglable (visibility)
/// </summary>

class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
public:
	//	visibility = true, logging = false
	ConsistentConsole();
	// visibility constructor
	ConsistentConsole(bool visibility);
	//	visibility and logging constructor
	ConsistentConsole(bool visability, bool logToFile);

	///	Methods
	//	error, warning, safe, or update. Then a message for context. ez.
	bool consoleManager(const char* type, const char* MSG);
	//	colour options: red, blue, green, purple, cyan, yellow, pink, clear
	inline bool colour(const char* colour);
	//	modifier options: clear, newline, indent
	inline bool colour(const char* colour, const char* modifier);

	//	clears the console using system("cls"); (literally just system("cls");)
	void clearConsole();

#pragma region getters / setters
	//	sets the console text state to the provided bool
	void setConsoleState(bool state) { isConsoleTextEnabled = state; }
	//	returns the consoleText boolean state
	bool getConsoleState() { return isConsoleTextEnabled; }	
	
	//	sets the logging state to the provided bool
	void setLogState(bool state) { isLogging = state; }
	//	returns the log boolean state
	bool getLogState() { return isLogging; }
#pragma endregion
protected:
	///	Variables
	bool isConsoleTextEnabled;
	bool isLogging;
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