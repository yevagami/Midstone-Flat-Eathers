#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "ConsistentConsole.h"
#include "EntityMap.h"


//	printing to the console... but pretty
class PrettyPrinting {
public:
	PrettyPrinting(const char* primary = pink, const char* secondary = purple, const char* accent = cyan);

	static void printXYZ(MATH::Vec3 v);
	static void printXY(MATH::Vec3 v);
	static void printXY(MATH::Vec2 v);

	static void printVS(std::vector<std::string> vString);
	static void printS(std::string string);
	static void printCC(const char* constChar);

	static void printEM(EntityMap& entityMap);

private:
	class EntityMap* eMap;

};
#pragma region constants
extern const char* themePrimary;
extern const char* themeSecondary;
extern const char* themeAccent;
#pragma endregion