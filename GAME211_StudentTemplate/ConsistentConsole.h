#pragma once

/// <summary>
/// The Console Message Management Class
/// 
///		Constructor:
/// - visibility = true, logging = false
/// 
///		Main Methods:
/// - log
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
	ConsistentConsole(bool visability_ = true, bool logToFile_ = false);  // NOLINT(readability-inconsistent-declaration-parameter-name)

	///	Methods
	//	error, warning, safe, or update. then a message for context. ez.
	bool log(const char* type_, const char* msg_);
	//	colour options: red, blue, green, purple, cyan, yellow, pink, clear
	inline bool colour(const char* colour_);
	//	modifier options: clear, newline, indent, blink, bold, italic
	inline bool colour(const char* colour_, const char* modifier_);

	//	clears the console using system("cls"); (literally just system("cls");)
	void clearConsole();

#pragma region getters / setters
	//	sets the console text state to the provided bool
	void setConsoleState(const bool state_) { isConsoleTextEnabled = state_; }
	//	returns the consoleText boolean state
	[[nodiscard]] bool getConsoleState() const { return isConsoleTextEnabled; }	
#pragma endregion
protected:
	///	Variables
	bool isConsoleTextEnabled;
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
extern const char* not_error;
extern const char* update;
extern const char* warning;
#pragma endregion