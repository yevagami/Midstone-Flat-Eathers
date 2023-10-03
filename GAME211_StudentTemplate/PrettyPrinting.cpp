#include "PrettyPrinting.h"
using namespace MATH;
using namespace std;

ConsistentConsole ccPrint;


void PrettyPrinting::printXYZ(Vec3 v) {
	ccPrint.colour(purple);

	cout << "Vec3:"; 	ccPrint.colour(pink); cout << "[" << v.x << ", " << v.y << ", " << v.z << "]\n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printXY(Vec3 v) {
	ccPrint.colour(purple);

	cout << "Vec3(2D):"; 	ccPrint.colour(pink); cout << "[" << v.x << ", " << v.y << "] \n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printXY(Vec2 v) {
	ccPrint.colour(purple);

	cout << "Vec2D:"; 	ccPrint.colour(pink); cout << "[" << v.x << ", " << v.y << "] \n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printVS(vector<string> vString) {
	ccPrint.colour(purple);

	cout << "Vector String: \n";
	ccPrint.colour(pink);
	if (!vString.empty()) {
		for (string string : vString) {
			cout << string << "\n";
		}
	}
	else {
		ccPrint.consoleManager("error", "failed to print vector string lmao");
	}

	ccPrint.colour(clear);
}


void PrettyPrinting::printS(string string) {
	ccPrint.colour(purple);

	cout << "String: [";
	ccPrint.colour(pink);
	cout << string;
	ccPrint.colour(purple);
	cout << "]\n";

	ccPrint.colour(clear);
}


void PrettyPrinting::printCC(const char* constChar) {
	ccPrint.colour(purple);
	cout << "Const Char*: [";
	ccPrint.colour(pink);
	cout << constChar;
	ccPrint.colour(purple);
	cout << "]\n";

	ccPrint.colour(clear);
}