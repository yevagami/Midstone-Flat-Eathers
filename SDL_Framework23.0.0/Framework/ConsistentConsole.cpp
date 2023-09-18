#include "ConsistentConsole.h"

void ConsistentConsole::consoleManager(const char* type, const char* MSG) {
	if (isConsoleTextEnabled) {
		if (type == "error") {
			colour("red");
			cout << "Error Occured: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "update") {
			colour("purple");
			cout << "Update: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "not error") {
			colour("green");
			cout << "btw: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "" || type == " ") {
			colour("cyan");
			cout << "btw: [" << MSG << "]" << endl;
			colour("clear");
		}

		else {
			colour("red");
			cout << "error in the error handler : O *dun dun dun*" << endl;
			colour("clear");
		}
	} }



void ConsistentConsole::colour(const char* colour) {
	//yandereDev code time >:)
	if (colour == "red") {
		std::cout << "\033[31m";
	}
	if (colour == "blue") {
		std::cout << "\033[34m";
	}
	if (colour == "green") {
		std::cout << "\033[32m";
	}
	if (colour == "purple") {
		std::cout << "\033[35m";
	}
	if (colour == "cyan") {
		std::cout << "\033[36m";
	}
	if (colour == "yellow") {
		std::cout << "\033[33m";
	}

	if (colour == "clear") {
		std::cout << "\033[0m";
	}
}
