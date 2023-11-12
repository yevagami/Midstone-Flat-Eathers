#pragma once
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <string>
#include <vector>
#include "Vector.h"
#include "ConsistentConsole.h"
#include "EntityMap.h"


//	printing to the console... but pretty
class PrettyPrinting {
public:
	PrettyPrinting(const char* primary_ = pink, const char* secondary_ = purple, const char* accent_ = cyan);

	static void printXYZ(MATH::Vec3 v);
	static void printXY(MATH::Vec3 v);
	static void printXY(MATH::Vec2 v);

	static void printVS(std::vector<std::string> vString);
	static void printS(std::string string);
	static void printCC(const char* constChar);

	static void printEM(EntityMap& entityMap);

	static void printMouseCoords(const SDL_Event& event_);

private:
	class EntityMap* eMap;

};

#pragma region constants
extern const char* themePrimary;
extern const char* themeSecondary;
extern const char* themeAccent;
#pragma endregion