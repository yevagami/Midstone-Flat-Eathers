#include "Scene0.h"
using namespace std; 


Scene0::Scene0(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	SDL_GetWindowSize(window, &screenWidth, &screenHeight);

	screenRenderer = nullptr;

	background = new Body(); // use the default values for the constructor
	background->SetTextureFile("textures/forest.jpg");

	car = new Body(Vec3(1.0f, 3.0f, 0.0f), Vec3(), Vec3(), 
						0.0f, "textures/red_car_small.png");

	backgroundTexture = nullptr;
	carTexture = nullptr;
}

bool Scene0::OnCreate() {
	//Create renderer for window
	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!screenRenderer) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize renderer color (black)
	SDL_SetRenderDrawColor(screenRenderer, 0, 0, 0, 255);

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// Load the bodies's textures
	backgroundTexture = loadImage(background->GetTextureFile());
	carTexture = loadImage(car->GetTextureFile());

	return true;
}


void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

}

void Scene0::Update(const float deltaTime) {
	car->Update(deltaTime);
}

Vec3 Scene0::PhysicsSpaceToScreenSpace(Vec3 physicsCoords)
{
	float x = physicsCoords.x * screenWidth / physicsScreenWidth;
	// We need to subtract the y coords from the physicsScreenHeight because
	// in physics space, y = 0 is at the bottom while in screen space,
	// it is at the top
	float y = (physicsScreenHeight - physicsCoords.y) * screenHeight / physicsScreenHeight;
	float z = physicsCoords.z * screenDepth / physicsScreenDepth;
	return Vec3(x, y, z);
}

void Scene0::Render() {
	// Clear the screen
	SDL_RenderClear(screenRenderer);

	// Render the background to the window.
	SDL_RenderCopy(screenRenderer, backgroundTexture, nullptr, nullptr);

	// Render the balloon. We first need to get the SDL coordinates 
	Vec3 screenCoords = PhysicsSpaceToScreenSpace(car->pos);
	// You can scale the texture if you want to. Currently, we just keep
	// everything to its original scale (1.0f)
	SDL_Rect dest = scale(carTexture, screenCoords.x, screenCoords.y, 1.0f);
	SDL_RenderCopy(screenRenderer, carTexture, nullptr, &dest);

	// Update screen
	SDL_RenderPresent(screenRenderer);

}

SDL_Texture* Scene0::loadImage(const char* textureFile)
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

SDL_Rect Scene0::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale) {

	// Get the size of the input texture
	SDL_Point size;
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene0::OnDestroy() {
	// Free loaded images.
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(carTexture);
	backgroundTexture = nullptr;
	carTexture = nullptr;

	// Destroy the renderer.
	if (screenRenderer) {
		SDL_DestroyRenderer(screenRenderer);
		screenRenderer = nullptr;
	}
}

Scene0::~Scene0() {
	cout << "deleting child class: Scene0." << endl;
	delete background;
	delete car; 
}