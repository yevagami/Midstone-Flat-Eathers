#include "ConsistentConsole.h"
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;



	///	Console Functions

ConsistentConsole::ConsistentConsole(){
	isConsoleTextEnabled = true;	

}


ConsistentConsole::ConsistentConsole(bool visibility){
	isConsoleTextEnabled = visibility;
}

//ConsistentConsole::ConsistentConsole(const char* visibility) {
//	if (visibility == "all" || visibility == "some" || visibility == "none") {
//		consoleTextVisibilityLevel = visibility;
//		isConsoleTextEnabled = true;
//	}
//}


void ConsistentConsole::consoleManager(const char* type, const char* MSG) {

	// check the console text visibility level
	//if (consoleTextVisibilityLevel == "all") {
	//	// show all messages
	//	isConsoleTextEnabled = true;
	//}
	//else if (consoleTextVisibilityLevel == "some") {
	//	// show only error and update messages
	//	isConsoleTextEnabled = (type == "error" || type == "update");
	//}
	//else if (consoleTextVisibilityLevel == "none") {
	//	// show no messages
	//	isConsoleTextEnabled = false;
	//}
	//else {
	//	// invalid visibility level
	//	isConsoleTextEnabled = false;
	//}

	if (isConsoleTextEnabled) {
		if (type == "error") {
			colour("red");
			cout << "Error: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "update") {
			colour("green");
			cout << "Update: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "not error") {
			colour("cyan");
			cout << "btw: [" << MSG << "]" << endl;
			colour("clear");
		}

		else if (type == "" || type == " ") {
			colour("purple");
			cout << "[" << MSG << "]" << endl;
			colour("clear");
		}

		else {
			colour("red");
			cout << "error in the error handler : O *dun dun dun*" << endl;
			colour("clear");
		}
	}
	else {

	}
}



void ConsistentConsole::colour(const char* colour) {
	//yandereDev code time >:)
	if (colour == "clear") {
			cout << "\033[0m";
	}
	else if (colour == "red") {
		cout << "\033[31m";
	}
	else if (colour == "blue") {
		cout << "\033[34m";
	}
	else if (colour == "green") {
		cout << "\033[32m";
	}
	else if (colour == "purple") {
		cout << "\033[35m";
	}
	else if (colour == "cyan") {
		cout << "\033[36m";
	}
	else if (colour == "yellow") {
		cout << "\033[33m";
	}
	else if (colour == "pink") {
		cout << "\033[95m";
	}
}


void ConsistentConsole::clearConsole() { system("cls"); }
