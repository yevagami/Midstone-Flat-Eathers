#include "Level_Test.h"

bool Level_test::OnCreate(){
	Enemy* ghost = new Enemy(this, Vec3((1600.0f / 2.0f) - 1000 + 500.0f, 900.0f / 2.0f, 0.0f), Enemy::flash);
	levelBodies.push_back(ghost);
	ghost = nullptr;

	//Creating the background
	background = SDL_CreateTextureFromSurface(parentScene->getRenderer(), IMG_Load("Textures/programmer_art/background.png"));

	//Creating the floor
	floor = new Body(this, Vec3((1366.0f / 2.0f), 768.0f / 2.0f, 0.0f), Vec3(10.0f, 10.0f, 10.0f), 1.0f, 1.0f, IMG_Load("Textures/programmer_art/tile_floor_red.png"));

#pragma region Creating Walls
	//creating the walls
	//Top wall
	Solid* wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f), 768.0f / 2.0f + 128 * 5.5, 0.0f),
		Vec3(12.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_red.png")
	);
	levelBodies.push_back(wall);
	//Accent to make the wall look tall
	Body* tiles= new Body(
		this,
		Vec3((1366.0f / 2.0f), 768.0f / 2.0f + 128 * 4.5, 0.0f),
		Vec3(11.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_red.png")
	);
	levelBodies.push_back(tiles);


	//Right wall
	 wall = new Solid(
		this,
		Vec3(1366.0f / 2.0f + 128 * 5.5, 768.0f / 2.0f + 128 * 0.5, 0.0f),
		Vec3(1.0f, 9.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_red.png")
	);
	levelBodies.push_back(wall);

	tiles = new Body(
		this,
		Vec3(1366.0f / 2.0f + 128 * 5.5, 768.0f / 2.0f - 128 * 7, 0.0f),
		Vec3(1.0f, 6.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_red.png")
	);
	levelBodies.push_back(tiles);

	//Left wall
	wall = new Solid(
		this,
		Vec3(1366.0f / 2.0f - 128 * 5.5, 768.0f / 2.0f + 128 * 0.5, 0.0f),
		Vec3(1.0f, 9.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_red.png")
	);
	levelBodies.push_back(wall);

	tiles = new Body(
		this,
		Vec3(1366.0f / 2.0f - 128 * 5.5, 768.0f / 2.0f - 128 * 7, 0.0f),
		Vec3(1.0f, 6.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_red.png")
	);
	levelBodies.push_back(tiles);

	//Bottom wall
	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f), 768.0f / 2.0f - 128 * 7.5, 0.0f),
		Vec3(10.0f, 5.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_red.png")
	);
	levelBodies.push_back(wall);

	wall = nullptr;

#pragma endregion

	return true;
}

void Level_test::OnDestroy(){
	for (Body* body : levelBodies) {
		if (body->type == body->PLAYER) {
			body = nullptr;
			continue;
		}
		delete body;
	}
	levelBodies.clear();

	if (background) {
		SDL_DestroyTexture(background);
		delete background;
	}

	floor->OnDestroy();
	delete floor;
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
		//Go through the levelBodies vector and find the trash object that still has a  reference in it
		//https://www.youtube.com/watch?v=SgcHcbQ0RCQ
		//it uses an iterator 
		//if the iterator finds the trash object then it will remove it from the levelBodies vector
		//only then will it be cleared for deletion
		//if it is not found in the levelBodies, then safe to assume that it's not there anymore
		//so we can delete it
		std::vector<Body*>::iterator it = std::find(levelBodies.begin(), levelBodies.end(), trash);
		if (it != levelBodies.end()) {
			levelBodies.erase(it);
		}
		trash->OnDestroy();
		delete trash;
	}
	trashBodies.clear();
}

void Level_test::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){
	//render the background
	SDL_RenderCopy(parentScene->getRenderer(), background, nullptr, nullptr);
	floor->Render(renderer_, projectionMatrix_);

	for (Body* body : levelBodies) {
		body->Render(renderer_, projectionMatrix_);
		//body->RenderHitbox(renderer_);
	}
}

void Level_test::HandleEvents(const SDL_Event& event){
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}
