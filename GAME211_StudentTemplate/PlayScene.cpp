#include "PlayScene.h"

#include <random>
#include <utility>



PlayScene::PlayScene(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 1600.0f;
	yAxis = 900.0f;

	player = nullptr;
	currentLevel = nullptr;
}

bool PlayScene::OnCreate(){
	//SDL window stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	//Set the name of the scene for organizing purposes
	name = "Play Scene";

	//	load trackers
	tracker.scary();


	//Creating the level
	currentLevel = new Level_test(this);
	if (!currentLevel->OnCreate()) {
		std::cout << "Something went wrong with the Level\n";
	}

	//Creating the player body
	player = new PlayerBody(
		this,
		Vec3(xAxis * 0.5f, yAxis * 0.5f, 0.0f),
		Vec3(1.0f, 1.0f, 1.0f),
		128.0f,
		128.0f
	);
	if (!player->OnCreate()) {
		std::cout << "Something went wrong with the Player object\n";
		return false;
	};
	player->setParentLevel(currentLevel);
	currentLevel->levelBodies.push_back(player);

	return true;
}

void PlayScene::OnDestroy(){
	currentLevel->OnDestroy();
	delete currentLevel;

	tracker.unscary();

	player->OnDestroy();
	delete player;
}

void PlayScene::Update(const float time){
	//CameraFollowPlayer(player);
	currentLevel->Update(time);

	std::string important = std::to_string(Tracker::genRanNum(0, 10));
	std::string notImportant = std::to_string(Tracker::genRanNum(50, 150));
	std::string somewhatImportant = std::to_string(Tracker::genRanNum(5000, 6000));


	tracker.trackThis(important, tracker.tracker1);
	tracker.trackThis(notImportant, tracker.tracker2);
	tracker.trackThis(somewhatImportant, tracker.tracker3);
}

void PlayScene::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//	render the trackers
	tracker.render(renderer);

	currentLevel->Render(renderer, projectionMatrix);

	SDL_RenderPresent(renderer);
}



void PlayScene::HandleEvents(const SDL_Event& event){
	player->HandleEvents(event);
}


void PlayScene::CameraFollowPlayer(PlayerBody* p){
	//guard clause to make sure the player exists
	if (p == nullptr) {
		return;
		std::cout << "Player doesn't exist\n";
	}

	//move the camera  update
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);

	float left = p->getPos().x - xAxis / 2.0f;
	float right = p->getPos().x + xAxis / 2.0f;
	float top = p->getPos().y - yAxis / 2.0f;
	float bottom = p->getPos().y + yAxis / 2.0f;

	Matrix4 ortho = MMath::orthographic(left, right, top, bottom, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);
}


