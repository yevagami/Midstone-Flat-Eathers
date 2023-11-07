#include "Level1.h"

Level1::Level1(SDL_Window* sdlWindow_, GameManager* game_) { 
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1600.0f;
	yAxis = 900.0f;

}
Level1::~Level1() {}

bool Level1::OnCreate()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	//Create the body
	/*
	block = new Solid(
		this,
		Vec3(xAxis * 0.5f + 400.0f, yAxis * 0.5f, 0.0f),
		Vec3(1.0f, 1.0f, 1.0f),
		128.0f,
		128.0f,
		IMG_Load("Textures/programmer_art/block_cap.png")
	);
	*/

	//Load the body's hitbox


	//Add the objects to the list
	
	//sceneObjects.push_back(block);

	return true;
}

void Level1::OnDestroy() {
	/*
	for (Body* body : sceneObjects) {
		body->OnDestroy();
		delete body;
	}
	*/
	sceneObjects.clear();

	
}


void Level1::Update(const float time) {

	

	//Check for collision
	for (Body* body : sceneObjects) {
		for (Body* otherBody : sceneObjects) {
			if (body == otherBody) { continue; }
			if (body->getHitbox()->collisionCheck(otherBody->getHitbox())) {
				body->OnCollide(otherBody, time);
			}
		}
	}

	//Update the body
	for (Body* body : sceneObjects) {
		body->Update(time);
	}

	/*
	//Delete the bodies that are flagged for deletion
	if (trashObjects.empty()) { return; }
	for (Body* body : trashObjects) {
		delete body;
	}
	*/
}

void Level1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (Body* body : sceneObjects) {
		body->Render(renderer, projectionMatrix);
		body->RenderHitbox(renderer);
	}
	SDL_RenderPresent(renderer);
}

void Level1::HandleEvents(const SDL_Event& event) {
	for (Body* body : sceneObjects) {
		body->HandleEvents(event);
	}
}