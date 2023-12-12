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
		ouch = 12,
		health = 13,
		points = 14,
		portal = 15
	};

	enum PlayerWalking {
		Player_Down = 0,
		Player_Up = 1,
		Player_Left = 2,
		Player_Right = 3
	};
	
	enum PlayerAttacks {
		Gun  = 0,
		Shield = 4,
		Sword = 5,
		Bullet = 10
	};

#endif