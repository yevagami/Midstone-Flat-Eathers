#include "Level_Test.h"

bool Level_test::OnCreate(){
	Vec3 tileDistance = parentScene->getInverseMatrix() * Vec3(128.0f, 128.0f, 128.0f);
	for (int i = 0; i < 5; i++) {
		Solid* wall = new Solid(
			this,
			Vec3(1600.0f / 2.0f + (tileDistance.x * i) + 500.0f, 900.0f / 2.0f, 0.0f),
			Vec3(1.0f, 1.0f, 1.0f),
			128.0f,
			128.0f,
			IMG_Load("Textures/programmer_art/block_cap.png")
		);
		levelBodies.push_back(wall);
		wall = nullptr;
	}
	return true;
}

void Level_test::OnDestroy(){
	for (Body* body : levelBodies) {
		if (body->type == 3) {
			body = nullptr;
			continue;
		}
		delete body;
	}
	levelBodies.clear();
}

void Level_test::Update(const float time){
	for(Body* body : levelBodies) {
		//std::cout << body->type << "\n";
		body->Update(time);

		//Collision checks
		for (Body* otherBody : levelBodies) {
			if (otherBody == body) { continue; }
			if (body->getHitbox()->collisionCheck(otherBody->getHitbox())) {
				body->OnCollide(otherBody, time);
			}
		}
	}

	//Bodies that are in queue for spawning will now be placed into the main body vector
	//c++ doesn't like it when you are pushing something to a vector
	//while you are iterating over it
	if (!spawningBodies.empty()) {
		for (Body* spawn : spawningBodies) {
			levelBodies.push_back(spawn);
			spawn = nullptr;
		}
		spawningBodies.clear();
	}

	//Cleanup
	if (trashBodies.empty()) { return; }
	for (Body* trash : trashBodies) {
		auto it = std::find(levelBodies.begin(), levelBodies.end(), trash);
		if (it != levelBodies.end()) {
			levelBodies.erase(it);
		}
		trash->OnDestroy();
		delete trash;
	}
	trashBodies.clear();
}

void Level_test::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){
	for (Body* body : levelBodies) {
		body->Render(renderer_, projectionMatrix_);
		body->RenderHitbox(renderer_);
	}
}

void Level_test::HandleEvents(const SDL_Event& event){
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}
