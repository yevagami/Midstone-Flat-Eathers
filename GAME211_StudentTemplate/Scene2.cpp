#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene2::~Scene2(){}

bool Scene2::OnCreate(){
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	name = "scene2";
	
	block = new Body();
	block->setPos(Vec3(xAxis * 0.5f + 5.0f, yAxis * 0.5f, 0.0f));
	block->setImage(IMG_Load("Textures/blue_block.jpg"));
	block->setTexture(SDL_CreateTextureFromSurface(renderer, block->getImage()));
	block->LoadHitbox(225.0f, 225.0f);

	game->getPlayer()->LoadHitbox(542.0f * 0.1f, 571.0f * 0.1f);
	return true;
}

void Scene2::OnDestroy(){}

void Scene2::Update(const float time){
	game->getPlayer()->getHitbox().collisionCheck(block->getHitbox());
	block->Update(time);
	game->getPlayer()->Update(time);
}

void Scene2::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	block->Render(renderer, projectionMatrix);
	game->RenderPlayer(0.1f);

	Hitbox playerHitbox = game->getPlayer()->getHitbox();
	Vec3 hitboxPos = projectionMatrix * Vec3(playerHitbox.x, playerHitbox.y, 0.0f);

	SDL_Rect box{ hitboxPos.x - 0.5f * playerHitbox.w, hitboxPos.y - 0.5f * playerHitbox.h, playerHitbox.w, playerHitbox.h };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &box);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event){
	game->getPlayer()->HandleEvents(event);
}
