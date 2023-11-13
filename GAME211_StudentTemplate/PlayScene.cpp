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
	scary();


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

	for (auto tracker : allTrackers) {
		delete tracker;
	}

	player->OnDestroy();
	delete player;
}

void PlayScene::Update(const float time){
	//CameraFollowPlayer(player);
	currentLevel->Update(time);

	std::string important = std::to_string(genRanNum(0, 10));
	std::string notImportant = std::to_string(genRanNum(50, 150));
	std::string somewhatImportant = std::to_string(genRanNum(5000, 6000));

	trackThis(important, tracker1);
	trackThis(notImportant, tracker2);
	trackThis(somewhatImportant, tracker3);
}

void PlayScene::Render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//	render the trackers
	for (const auto tracker : allTrackers) {
		tracker->Render(renderer);
	}


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






void PlayScene::scary() {
	int size = 20;
	tracker1 = new ui::Button(ui::Font{"", size});
	tracker2 = new ui::Button(ui::Font{"", size });
	tracker3 = new ui::Button(ui::Font{"", size });
	allTrackers.emplace_back(tracker1);
	allTrackers.emplace_back(tracker2);
	allTrackers.emplace_back(tracker3);

	for (auto t : allTrackers) {
		t->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		t->textColour = ui::SDL_COLOR_ANTIQUE_WHITE;
		t->offsetPosition(-SCREEN_HEIGHT +400);
	}
	tracker2->setPositionRelativeTo(*tracker1, 25);
	tracker3->setPositionRelativeTo(*tracker2, 25);

}

void PlayScene::trackThis(std::string value_, ui::Button* tracker_) {
	tracker_->text = std::move(value_);
}

int PlayScene::genRanNum(const int min_, const int max_) {
	std::random_device rd;
	std::mt19937 gen(rd()); 

	uniform_int_distribution<> distrib(min_, max_);
	cout << distrib(gen) << endl;
	return distrib(gen);
}