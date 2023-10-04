#pragma once

/// <summary>
/// The Console Message Management Class
/// 
///		Constructor:
/// - visibility = true, logging = false
/// 
///		Main Methods:
/// - consoleManager
/// - colour (colour)
/// - colour (colour, modifier)
/// 
///		Goals:
/// - cleaning up the console with consistency, colours, and confetti! (sans confetti)
/// - allow for console messages to be togglable (visibility)
/// </summary>

class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
public:
	//	visibility = true, logging = false
	ConsistentConsole(bool visability = true, bool logToFile = false);

	///	Methods
	//	error, warning, safe, or update. then a message for context. ez.
	bool consoleManager(const char* type, const char* MSG);
	//	colour options: red, blue, green, purple, cyan, yellow, pink, clear
	inline bool colour(const char* colour);
	//	modifier options: clear, newline, indent, blink, bold, italic
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
extern const char* blink;

extern const char* error;
extern const char* update;
extern const char* safe;
extern const char* warning;
#pragma endregion