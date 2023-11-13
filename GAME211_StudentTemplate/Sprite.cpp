#include "Sprite.h"
#include "Math.h"

// adds file and renderer to create a texture and a surface

Sprite::Sprite(const char* file, SDL_Renderer* renderer_)
{
	renderer = renderer_;
	image = IMG_Load(file);
	spriteSheet = SDL_CreateTextureFromSurface(renderer, image);
}

// assume 128 x 128 textures/images, and cut up

bool Sprite::autoLoadSprites()
{
	if (image == nullptr) {
		std::cout << "The image has been missing or broken." << "\n";
		return false;
	}

	if (spriteSheet == nullptr) {
		std::cout << "The texture has been missing or broken." << "\n";
		return false;
	}

	int row = floor(image->h / 128); // floor means "rounding down"
	int column = floor(image->w / 128);

	for (int y = 0; y < row; y++) {
		for (int x = 0; x < column; x++) {
			SDL_Rect r1;
			r1.x = x * 128;
			r1.y = y * 128;
			r1.w = 128;
			r1.h = 128;
			spriteStorage.push_back(r1);
		}
	}

	return true;
}

// given x, y, w, h, cut up

bool Sprite::loadSpriteFromRect(int x_, int y_, int w_, int h_)
{
	if (image == nullptr) {
		std::cout << "The image has been missing or broken." << "\n";
		return false;
	}

	if (spriteSheet == nullptr) {
		std::cout << "The texture has been missing or broken." << "\n";
		return false;
	}

	SDL_Rect r2;
	r2.x = x_;
	r2.y = y_;
	r2.w = w_;
	r2.h = h_;
	spriteStorage.push_back(r2);

	return true;
}
