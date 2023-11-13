#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include <stdio.h>
#include <vector>
#include "SDL.h"
#include "GameManager.h"
class Sprite
{
private:

	SDL_Surface* image = nullptr; // path to the spriteSheet image
	SDL_Texture* spriteSheet = nullptr;  // texture from the spriteSheet image
	SDL_Renderer* renderer = nullptr; // machine that makes things draw on the screen

public:

	std::vector<SDL_Rect> spriteStorage; // store all individual sprites cut out from big sprites

	Sprite() {};
	Sprite(const char* file, SDL_Renderer* renderer_);
	~Sprite() {};
	bool autoLoadSprites();
	bool loadSpriteFromRect(int x_, int y_, int w_, int h_);

};
#endif