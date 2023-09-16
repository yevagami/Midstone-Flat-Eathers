#include "debugFunc.h"

void debugFunc::printXYZ_Vec3(Vec3 v){
	std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
}

void debugFunc::printXY_Vec3(Vec3 v){
	std::cout << "(" << v.x << ", " << v.y << ")\n";
}

void debugFunc::printVectorString(vector<string>& vString) {   
    for (std::string string : vString) {
        std::cout << string << "\n"; }
}