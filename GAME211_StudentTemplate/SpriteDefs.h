#pragma once
#ifndef SPRITEDEFS_H
#define SPRITEDEFS_H
//#include <unordered_map>
//#include <string>
#include "Sprite.h"
	//These are just enums that I've defined so you don't have to go around lookg through the sprite sheet
	//To see which index belongs to which sprite
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
		melee_strike = 10,
		boom = 11,
		ouch = 12
	};

	enum PlayerTest {
		Player_Neutral = 0,
		Player_Left = 6,
		Player_Right = 12,
		Player_Up = 18,
		Player_Down = 24
	};

#endif