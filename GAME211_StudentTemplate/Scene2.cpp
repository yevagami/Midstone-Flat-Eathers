#include "Scene2.h"

Scene2::Scene2(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1366.0f;
	yAxis = 768.0f;
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
	
	Vec3 hitbox = Vec3(225.0f, 225.0f, 0.0f);
	block = new Body();
	block->setPos(Vec3(xAxis * 0.5f + 50.0f, yAxis * 0.5f, 0.0f));
	block->setImage(IMG_Load("Textures/blue_block.jpg"));
	block->setTexture(SDL_CreateTextureFromSurface(renderer, block->getImage()));
	block->LoadHitbox(hitbox.x, hitbox.y);

	hitbox = Vec3(542.0f * 0.1f, 571.0f * 0.1f, 0.0f);
	game->getPlayer()->LoadHitbox(hitbox.x, hitbox.y);
	return true;
}

void Scene2::OnDestroy(){}

void Scene2::Update(const float time){
	if (game->getPlayer()->getHitbox().collisionCheck(block->getHitbox())) {
		std::cout << "Collided\n";
	};

	block->Update(time);
	game->getPlayer()->Update(time);
}

void Scene2::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	block->Render(renderer, projectionMatrix);
	game->RenderPlayer(0.1f);

	game->getPlayer()->RenderHitbox(renderer, projectionMatrix, 0.1f);
	block->RenderHitbox(renderer, projectionMatrix, 1.0f);
	
	SDL_RenderPresent(renderer);
}

void Scene2::HandleEvents(const SDL_Event& event){
	game->getPlayer()->HandleEvents(event);
}
