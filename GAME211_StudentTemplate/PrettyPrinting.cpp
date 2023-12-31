#include "PrettyPrinting.h"
#include "EntityMap.h"

using namespace MATH;
using namespace std;


ConsistentConsole ccPrint(false);


PrettyPrinting::PrettyPrinting(const char* primary_, const char* secondary_, const char* accent_) {
	themePrimary = primary_;
	themeSecondary = secondary_;
	themeAccent = accent_;


	eMap = nullptr;
}

void PrettyPrinting::printXYZ(Vec3 v) {
	ccPrint.colour(themeAccent);
	cout << "Vec3";
	cout<< ":";

	ccPrint.colour(themePrimary); 
	cout 
		<< "[" 
		<< v.x 
		<< ", " 
		<< v.y 
		<< ", " 
		<< v.z 
		<< "]\n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printXY(Vec3 v) {
	ccPrint.colour(themeAccent);
	cout << "Vec3(2D)";
	cout<< ":";

	ccPrint.colour(themePrimary); 
	cout 
		<< "[" 
		<< v.x 
		<< ", " 
		<< v.y 
		<< "] \n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printXY(Vec2 v) {
	ccPrint.colour(themeAccent);
	cout << "Vec2D";
	cout<< ":";
	
	ccPrint.colour(themePrimary); 
	cout 
		<< "[" 
		<< v.x 
		<< ", " 
		<< v.y 
		<< "] \n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printVS(vector<string> vString) {
	ccPrint.colour(themeAccent);
	cout << "Vector String";
	cout <<": \n";

	ccPrint.colour(themePrimary);
	if (!vString.empty()) {
		for (string string : vString) {
			cout << "\t" << string << "\n";
		}
	} else {
		ccPrint.log(error, "empty vector<string>");
	} 
	
	ccPrint.colour(clear);

}


void PrettyPrinting::printS(string string) {
	ccPrint.colour(themeAccent);
	cout << "String";
	cout << ": [";

	ccPrint.colour(themePrimary);
	cout << string;
	
	ccPrint.colour(themeSecondary);
	cout << "]\n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printCC(const char* constChar) {
	ccPrint.colour(themeAccent);
	cout << "Const Char*";
	cout << ": [";

	ccPrint.colour(themePrimary);
	cout << constChar;

	ccPrint.colour(themeSecondary);
	cout << "]\n";

	ccPrint.colour(clear);
}

void PrettyPrinting::printEM(EntityMap& entityMap) {
	for (const auto& pair : entityMap.getEntityMap()) {

		std::string first = pair.first;
		std::string second = pair.second;

		ccPrint.colour(themeAccent);
		cout << "Entity Map: ";
		ccPrint.colour(themePrimary);
		cout << first;
		ccPrint.colour(themeSecondary);
		cout << " : ";
		ccPrint.colour(themePrimary);
		cout << second << "\n";

	}

	ccPrint.colour(clear);

}

void PrettyPrinting::printMouseCoords(const SDL_Event& event_) {
	if (event_.type == SDL_MOUSEBUTTONDOWN) {
		if (event_.button.button == SDL_BUTTON_LEFT) {
			const int mx = event_.button.x;
			const int my = event_.button.y;
			ccPrint.colour(pink);
			std::cout << mx << ", " << my << std::endl;
			ccPrint.colour(clear);
		}
	}
}

#pragma region constants
const char* themePrimary = "";
const char* themeSecondary = "";
const char* themeAccent = "";
#pragma endregion