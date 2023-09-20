#pragma once
#include "Vector.h"
#include <string>
#include <vector>


//	all of these methods are now availible under PrettyPrinting (its pretty)

struct debugFunc {
	static void printXYZ_Vec3(MATH::Vec3 v);
	static void printXY_Vec3(MATH::Vec3 v);

	static void printVectorString(std:: vector<std::string> vString);


};