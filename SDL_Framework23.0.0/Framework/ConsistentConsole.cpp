#include "ConsistentConsole.h"
#include <cstdlib>
using namespace std;

ConsistentConsole::ConsistentConsole(){
isConsoleTextEnabled = true;
//or
consoleTextVisibilityLevel = 3;	
}
ConsistentConsole::ConsistentConsole(int visibilityLevel){
	isConsoleTextEnabled = true;
	consoleTextVisibilityLevel = visibilityLevel;
	
}


void ConsistentConsole::consoleManager(const char* type, const char* MSG) {
	if (isConsoleTextEnabled) {
		if (type == "error") {
			colour("red");
			cout << "Error: [" << MSG << "]" << endl;
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
			cout << ": [" << MSG << "]" << endl;
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
		cout << "\033[31m";
	}
	if (colour == "blue") {
		cout << "\033[34m";
	}
	if (colour == "green") {
		cout << "\033[32m";
	}
	if (colour == "purple") {
		cout << "\033[35m";
	}
	if (colour == "cyan") {
		cout << "\033[36m";
	}
	if (colour == "yellow") {
		cout << "\033[33m";
	}

	if (colour == "clear") {
		cout << "\033[0m";
	}
}

void ConsistentConsole::clearConsole() { system("cls"); }
