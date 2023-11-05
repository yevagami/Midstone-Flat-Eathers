#include "Scene2.h"
using namespace ui;


Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1600.0f;
	yAxis = 900.0f;

	scene2Button = new Button(Font{ "Adriel World", 100 });
	scene2Button->textColour = SDL_COLOR_DEEP_PINK << SDL_White50;
	scene2Button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT); scene2Button->offsetPosition(-300);
	allButtons.emplace_back(scene2Button);

}

Scene2::~Scene2(){
}

bool Scene2::OnCreate(){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	name = "scene2";


	//Create the body
	Body* block = new Solid();
	block->setPos(Vec3(xAxis * 0.5f + 400.0f, yAxis * 0.5f, 0.0f));
	block->setImage(IMG_Load("Textures/programmer_art/block_cap.png"));
	block->setTexture(SDL_CreateTextureFromSurface(renderer, block->getImage()));
	block->LoadHitbox(
		128.0f,
		128.0f
	);

	//Load the body's hitbox
	game->getPlayer()->LoadHitbox(
		128.0f,
		128.0f
	);

	//Add the objects to the list
	sceneObjects.push_back(block);
	sceneObjects.push_back(game->getPlayer());
	for (Body* body : sceneObjects) {
		body->setParentScene(this);
	}

	return true;
}

void Scene2::OnDestroy() {
	for (auto* button : allButtons) {
		delete button;
	}

	for (Body* body : sceneObjects) {
		body->OnDestroy();
		delete body;
	}
	sceneObjects.clear();
}

void Scene2::Update(const float time){
	//move the camera  update
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);

	float left = game->getPlayer()->getPos().x - xAxis / 2.0f;
	float right = game->getPlayer()->getPos().x + xAxis / 2.0f;
	float top = game->getPlayer()->getPos().y - yAxis / 2.0f;
	float bottom = game->getPlayer()->getPos().y + yAxis / 2.0f;

	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);//
	projectionMatrix = ndc * ortho;

	//Check for collision
	for (Body* body : sceneObjects) {
		for (Body* otherBody : sceneObjects) {
			if (body == otherBody) { continue; }
			if (body->getHitbox().collisionCheck(otherBody->getHitbox())) {
				body->OnCollide(otherBody, time);
			}
		}
	}

	//Update the body
	for (Body* body : sceneObjects) {
		body->Update(time);
	}

	//Delete the bodies that are flagged for deletion
	if (flaggedObjects.empty()) { return; }
	for (Body* body : flaggedObjects) {
		body->OnDestroy();
		delete body;
	}
}

void Scene2::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (Body* body : sceneObjects) {
		body->Render(renderer, projectionMatrix, 1.0f);
		body->RenderHitbox(renderer);
	}

	for(auto* button : allButtons) {
		button->Render(renderer);
	}

	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event){
	for (Body* body : sceneObjects) {
		body->HandleEvents(event);
	}
}
