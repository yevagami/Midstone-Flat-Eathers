#include "scene_test.h"
#include "debugFunc.h"
#include "VMath.h"
using namespace std;

void printStuff() {
	cout << "Tick Tock" << endl;
}

scene_test::scene_test(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);

	screenRenderer = nullptr;

	background = new Body(); // use the default values for the constructor
	background->SetTextureFile("textures/grass.png");

	player = new Player();
	player->SetTextureFile("textures/heart.png");

	notThePlayer = new Body();
	notThePlayer->SetTextureFile("textures/blue_block.jpg");

}


bool scene_test::OnCreate() {
	//Reposition the player
	player->pos = Vec3(5.0f, 5.0f, 0.0f);
	notThePlayer->pos = Vec3(10.0f, 10.0f, 0.0f);

	//Create renderer for window
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!screenRenderer) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	cout << "creating " << sceneName << endl;

	//Initialize renderer color (black)
	SDL_SetRenderDrawColor(screenRenderer, 0, 0, 0, 255);

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// Load the bodies's textures
	background->SetTexture(loadImage(background->GetTextureFile()));
	player->SetTexture(loadImage(player->GetTextureFile()));
	notThePlayer->SetTexture(loadImage(notThePlayer->GetTextureFile()));
	
	//Load the bodie's hitbox
	player->LoadHitbox();
	notThePlayer->LoadHitbox();

	return true;
}


void scene_test::HandleEvents(const SDL_Event& sdlEvent) {
	player->playerController(sdlEvent);
	//Limiting the player's speed 
	//speed = sqrt(x^2 + y^2) | x = y (they both have inputs)
	//speed = sqrt(2x^2)
	//speed^2 = 2x^2
	//x = sqrt(speed^2/2)
}

void scene_test::Update(const float deltaTime) {
	
	player->Update(deltaTime);

	if (player->collisionCheck(notThePlayer->hitbox)) {
		//cout << "Colliding\n";
	}

	Vec3 playerPos = PhysicsSpaceToScreenSpace(player->pos);
	
	//cout << "Player pos( " << playerPos.x << ", " << playerPos.y << ")\n";

}


Vec3 scene_test::PhysicsSpaceToScreenSpace(Vec3 physicsCoords){
	float x = physicsCoords.x * screenWidth / physicsScreenWidth;
	// We need to subtract the y coords from the physicsScreenHeight because
	// in physics space, y = 0 is at the bottom while in screen space,
	// it is at the top
	float y = (physicsScreenHeight - physicsCoords.y) * screenHeight / physicsScreenHeight;
	float z = physicsCoords.z * screenDepth / physicsScreenDepth;
	return Vec3(x, y, z);
}


void scene_test::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);

	// Render the background to the window.
	SDL_RenderCopy(screenRenderer, background->GetTexture(), nullptr, nullptr);
	Vec3 destCoords = PhysicsSpaceToScreenSpace(player->pos);
	SDL_Rect dest = scale(player->GetTexture(), destCoords.x, destCoords.y, 1.0f);
	SDL_RenderCopy(screenRenderer, player->GetTexture(), nullptr, &dest);
	//Draw the player's hitbox
	/*
	SDL_SetRenderDrawBlendMode(screenRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(screenRenderer, 255, 255, 255, 100);
	SDL_RenderFillRect(screenRenderer, &dest);
	*/
	
	destCoords = PhysicsSpaceToScreenSpace(notThePlayer->pos);
	dest = scale(notThePlayer->GetTexture(), destCoords.x, destCoords.y, 1.0f);
	SDL_RenderCopy(screenRenderer, notThePlayer->GetTexture(), nullptr, &dest);

	// Update screen
	SDL_RenderSetScale(screenRenderer, 0.5f, 0.5f);
	SDL_RenderPresent(screenRenderer);
}

SDL_Texture* scene_test::loadImage(const char* textureFile)
{
	// The following is a typical chunk of code for creating 
	// a texture in SDL

	// The final texture
	SDL_Texture* newTexture = nullptr;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(textureFile);
	if (!loadedSurface)
	{
		cout << "Unable to load image " << textureFile <<
			"! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(screenRenderer, loadedSurface);
		if (!newTexture)
		{
			cout << "Unable to create texture " << textureFile <<
				"! SDL Error: " << SDL_GetError() << endl;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
SDL_Rect scene_test::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}


void scene_test::OnDestroy() {
	// Free loaded images.
	background->OnDestory();
	player->OnDestory();
	notThePlayer->OnDestory();
	printTime->OnDestroy();

	// Destroy the renderer.
	if (screenRenderer) {
		SDL_DestroyRenderer(screenRenderer);
		screenRenderer = nullptr;
	}
}


scene_test::~scene_test() {
	cout << "deleting child class: " << sceneName << endl;
	delete printTime;
	delete background;
	delete player;
	delete notThePlayer;
}