#pragma once
#include <string>

class ConsistentConsole {
	//	Console Consistency!!! oh, the beauty of cc...
public:
	//	Parameters: 
	//	visibility = true						|		whether to display the console logs
	//	whereAmI = "unspecified"	|		where is this constructor being called?
	ConsistentConsole(bool visability_ = true, const char* whereAmI_ = "unspecified ;-;");  // NOLINT(readability-inconsistent-declaration-parameter-name)

	///	Methods
	//	error, warning, not_error, debug, or update. then a message for context. ez.
	bool log(const char* type_ , const char* msg_, const std::string& variable_ = "");
	//	colour options: red, blue, green, purple, cyan, yellow, pink, clear
	inline bool colour(const char* colour_);
	//	added modifier options: clear, newline, indent, blink, bold, italic
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
extern const char* debug;
#pragma endregion