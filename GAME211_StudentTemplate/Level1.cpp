#include "Level1.h"

Level1::Level1(Scene* currentScene) { 
	setParentScene(currentScene);
}
Level1::~Level1() {}

bool Level1::OnCreate()
{
	background = SDL_CreateTextureFromSurface(getParentScene()->getRenderer(), IMG_Load("Textures/programmer_art/void_cat.png"));
	return true;
}

void Level1::OnDestroy() {
	for (Body* body : levelBodies) {
		body->OnDestroy();
		delete body;
	}
	for (Body* body : trashBodies) {
		body->OnDestroy();
		delete body;
	}
	delete background;
	levelBodies.clear();
	trashBodies.clear();
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

void Level1::Render() {
	for (Body* body : levelBodies) {
		body->Render(getParentScene()->getRenderer(), getParentScene()->getProjectionMatrix());
		body->RenderHitbox(getParentScene()->getRenderer());
	} 
	SDL_RenderCopy(getParentScene()->getRenderer(), background, nullptr, nullptr);
}

void Level1::HandleEvents(const SDL_Event& event) {
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}