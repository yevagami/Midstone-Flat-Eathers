#pragma once
#ifndef SPRITE_H
#define SPRITE_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"

class Sprite{
private:

	// variables to get class working
	SDL_Renderer* renderer = nullptr; // machine that makes things draw on the screen

public:

	std::vector<SDL_Rect> spriteStorage; // store all individual sprites cut out from big sprites
	//moving these to public so other classes can access it -Adriel
	//Renamed from spriteSheet to texture to avoid confusion - Adriel
	SDL_Texture* texture = nullptr;  // texture from the spriteSheet image 
	SDL_Surface* image = nullptr; // path to the spriteSheet image

	Sprite() {};
	Sprite(const char* file, SDL_Renderer* renderer_); // first parameter = file path to image, second = reference to scene renderer
	~Sprite() {};
	bool autoLoadSprites(); // cut up images into many small rectangles that are 128 x 128; store them into the spriteStorage vector
	bool loadSpriteFromRect(int x_, int y_, int w_, int h_); // give it a specific rectangle so you can get a specific part of the spriteSheet 
	void onDestroy();
};
#endif