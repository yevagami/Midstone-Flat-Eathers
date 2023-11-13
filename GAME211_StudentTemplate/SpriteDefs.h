#pragma once
#ifndef SPRITEDEFS_H
#define SPRITEDEFS_H
#include <unordered_map>
#include <string>
#include "Sprite.h"

	enum SpriteDefinitions{
		Missing = 0,
		Player = 1,
		Enemy_flash = 2,
		Enemy_strong = 3,
		Enemy_miracle = 4,
		Tile_top_red = 5,
		Tile_wall_red = 6,
		Tile_top_gray = 7,
		Tile_wall_gray = 8,
		projectile = 9,
		melee_strike = 10
	};

#endif