#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "ConsistentConsole.h"


//	printing to the console... but pretty
struct PrettyPrinting {
public:
	static void printXYZ(MATH::Vec3 v);
	static void printXY(MATH::Vec3 v);
	static void printXY(MATH::Vec2 v);


	static void printVS(std::vector<std::string> vString);
	static void printS(std::string string);
	static void printCC(const char* constChar);

};

