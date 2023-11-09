#include "Level1.h"
#include "Scene.h"

#include <SDL_image.h>

bool Level1::OnCreate(){
	background = SDL_CreateTextureFromSurface(parentScene->getRenderer(), IMG_Load("Textures/programmer_art/himeko.jpg"));
	return true;
}

void Level1::OnDestroy() {
	//clearing bodies that exist in the level
	for (Body* body : levelBodies) {
		body->OnDestroy();
		delete body;
	} levelBodies.clear();

	//trash bin lmao
	for (Body* body : trashBodies) {
		body->OnDestroy();
		delete body;
	} trashBodies.clear();

	//deleting texture
	if (background) {
		SDL_DestroyTexture(background);
		background = nullptr;
	}
}


void Level1::Update(const float time) {

	//Check for collision
	for (Body* body : levelBodies) {
		for (Body* otherBody : levelBodies) {
			if (body == otherBody) { continue; }
			if (body->getHitbox()->collisionCheck(otherBody->getHitbox())) {
				body->OnCollide(otherBody, time);
			}
		}
	}

	//Update the body
	for (Body* body : levelBodies) {
		body->Update(time);
	}

	
	//Delete the bodies that are flagged for deletion
	if (trashBodies.empty()) { return; }
	for (Body* body : trashBodies) {
		delete body;
	}
}

void Level1::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {
	for (Body* body : levelBodies) {
		body->Render(parentScene->getRenderer(), parentScene->getProjectionMatrix());
		body->RenderHitbox(parentScene->getRenderer());
	} 

	if (background == nullptr) {
		std::cout << "Forgot the background stupid" << std::endl;
		return;
	}
	SDL_RenderCopy(parentScene->getRenderer(), background, nullptr, nullptr);
}

void Level1::HandleEvents(const SDL_Event& event) {
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}