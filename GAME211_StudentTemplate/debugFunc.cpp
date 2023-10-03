#include "debugFunc.h"
using namespace MATH;

//	all the print functions are now availible in PrettyPrinting (its pretty)

void debugFunc::printXYZ_Vec3(Vec3 v){
	std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
}

void debugFunc::printXY_Vec3(Vec3 v){
	std::cout << "(" << v.x << ", " << v.y << ")\n";
}

void debugFunc::printVectorString(std::vector<std::string> vString) {   
	if (!vString.empty()) {
		for (std::string string : vString) {
			std::cout << string << "\n";
		}
	}
	else {
		std::cout << "its empty\n";
	}

}