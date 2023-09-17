#include "scene_test.h"
#include "debugFunc.h"
#include "VMath.h"

scene_test::scene_test(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);
	virtualWidth = screenWidth * 2.0f;
	virtualHeight = screenHeight * 2.0f;

	screenRenderer = nullptr;

	background = new Body(); // use the default values for the constructor
	background->SetTextureFile("textures/grass.png");

	player = new Player();
	player->SetTextureFile("textures/heart.png");

	notThePlayer = new Body();
	notThePlayer->SetTextureFile("textures/blue_block.jpg");
	notThePlayer->solid = true;

	bodyObjects.push_back(background);
	bodyObjects.push_back(player);
	bodyObjects.push_back(notThePlayer);
}


bool scene_test::OnCreate() {
	//Reposition the player
	player->pos = Vec3(virtualWidth / 2.0f, virtualDepth / 2.0f, 0.0f);
	notThePlayer->pos = Vec3(virtualWidth / 2.0f + 500.0f, virtualDepth / 2.0f + 500.0f, 0.0f);

	//Create renderer for window
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!screenRenderer) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_RenderSetScale(screenRenderer, 0.5f, 0.5f);
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
	
	//Load the body object's hitbox
	player->LoadHitbox(128.0f, 128.0f);
	notThePlayer->LoadHitbox(225.0f, 225.0f);

	for (Body* body : bodyObjects) {
		body->screenDimensions = Vec3(screenWidth, screenHeight, screenDepth);
		body->virtualDimensions = Vec3(virtualWidth, virtualHeight, virtualDepth);
	}

	return true;
}



void scene_test::HandleEvents(const SDL_Event& sdlEvent) {
	player->playerController(sdlEvent);



}



void scene_test::Update(const float deltaTime) {
	if (player->hitbox.collisionCheck(notThePlayer->hitbox)) {
		player->collisionResponse(deltaTime, notThePlayer);
	}
	
	/*
		I spent days, wondering why the hitboxes won't collide properly
		This is because I failed to understand the fundamental differences between physics space and screen space
		things that look like should be happening in screen space do not actually occur in physics space
		countless hours I pondering why the hitboxes aren't colliding in the place where they are supposed to be
		I even brought out the graphinc calculator to make sure that I'm not going insane
		The math was correct, so why wasn't it working properly???
		That's because everything was a lie
		Screen space is not what's actually happening in the math side
		While things occur in physics space they are being interpertated into screen space
		and that interpertation is what we see in screen space
		so while 2 objects look like THEY SHOULD be colliding in screen space
		they are not actually that close in physics space
		so I have concluded that hitboxes should be checked in screenspace and anything related to motion should be done in physics space
		The hitbox width and height will be represented in screen coords, and when doing collision checks they should be done using the screen coords
	*/
	




#pragma region Save Testing
	SaveManager save;	//	save.isConsoleTextEnabled = false;

	//	loads the save file into the currentSaveData
	save.loadGame();

	//changing values by typing the "variableName" then the "newValue"
	save.replaceValueInCurrentSave("Cat", "meeeeooowwww");
	save.replaceValueInCurrentSave("Dog", "bJork bJorque");

	//	saves the currentSaveData into the save file
	save.saveGame();
#pragma endregion





	notThePlayer->Update(deltaTime);
	player->Update(deltaTime);

}

Vec3 scene_test::PhysicsSpaceToScreenSpace(Vec3 physicsCoords) {
	float x = physicsCoords.x * screenWidth / virtualWidth;
	// We need to subtract the y coords from the physicsScreenHeight because
	// in physics space, y = 0 is at the bottom while in screen space,
	// it is at the top
	float y = (virtualHeight - physicsCoords.y) * screenHeight / virtualHeight;
	float z = physicsCoords.z * screenDepth / virtualDepth;
	return Vec3(x, y, z);
}


void scene_test::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);


	// Render the background to the window.
	SDL_RenderCopy(screenRenderer, background->GetTexture(), nullptr, nullptr);


	//Render the player
	Vec3 screenCoordinates = PhysicsSpaceToScreenSpace(player->pos);
	Vec3 screenDimensions(player->hitbox.w * screenWidth / virtualWidth, player->hitbox.h * screenWidth / virtualWidth, 0.0f);

	//Render the player's texture
	SDL_Rect dest = scale(player->GetTexture(), screenCoordinates.x, screenCoordinates.y, 1.0f);
	SDL_RenderCopy(screenRenderer, player->GetTexture(), nullptr, &dest);

	//Render the player's hitbox
	dest = { (int)player->hitbox.x, (int)player->hitbox.y, (int)player->hitbox.w, (int)player->hitbox.h};
	SDL_SetRenderDrawBlendMode(screenRenderer, SDL_BLENDMODE_ADD);
	SDL_SetRenderDrawColor(screenRenderer, 255, 255, 255, 100);
	SDL_RenderFillRect(screenRenderer, &dest);


	//Render the block
	screenCoordinates = PhysicsSpaceToScreenSpace(notThePlayer->pos);
	screenDimensions = Vec3(notThePlayer->hitbox.w * screenWidth / virtualWidth, notThePlayer->hitbox.h * screenWidth / virtualWidth, 0.0f);

	//Render the block's texture
	dest = scale(notThePlayer->GetTexture(), screenCoordinates.x, screenCoordinates.y, 1.0f);
	SDL_RenderCopy(screenRenderer, notThePlayer->GetTexture(), nullptr, &dest);

	//Render the block's hitbox
	dest = { (int)screenCoordinates.x, (int)screenCoordinates.y, (int)notThePlayer->hitbox.w, (int)notThePlayer->hitbox.h };
	SDL_RenderFillRect(screenRenderer, &dest);


	// Update screen
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
	for (Body* body : bodyObjects) {
		body->OnDestory();
	}

	// Destroy the renderer.
	if (screenRenderer) {
		SDL_DestroyRenderer(screenRenderer);
		screenRenderer = nullptr;
	}
}


scene_test::~scene_test() {
	cout << "deleting child class: " << sceneName << endl;
	for (Body* body : bodyObjects) {
		delete body;
	}
	bodyObjects.clear();
}