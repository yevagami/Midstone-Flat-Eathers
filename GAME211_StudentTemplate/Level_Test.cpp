#include "Level_Test.h"

//I might have to reorder the methods for organizing purposes

bool Level_test::OnCreate(){
	
	//Creating the background
	background = SDL_CreateTextureFromSurface(parentScene->getRenderer(), IMG_Load("Textures/programmer_art/background.png"));
	
	//Note:
	//I made the screen size and the physics size the same because it's much easier to use when constructing levels
#pragma region Creating Level geometry
	//Creating the floor
	floor = new Body(this, Vec3((1366.0f / 2.0f), 768.0f / 2.0f, 0.0f), Vec3(10.0f, 10.0f, 10.0f), 1.0f, 1.0f, IMG_Load("Textures/programmer_art/tile_floor_red.png"));


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
	//Accent to make the wall look nicer, also by default bodies don't have collision
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
	//Accent
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
	//Accent
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

	Drop* healthPacks = new Drop(
		this,
		Vec3(1366 / 2 + 500.0f, 768.0f / 2, 0.0f),
		Vec3(0.3f, 0.3f, 0.3f),
		128 * 0.3f, 128 * 0.3f,
		Drop::DropType::HEALTH
	);
	levelBodies.push_back(healthPacks);
	healthPacks = nullptr;

	Drop* points = new Drop(
		this,
		Vec3(1366 / 2 - 500.0f, 768.0f / 2, 0.0f),
		Vec3(0.3f, 0.3f, 0.3f),
		128 * 0.3f, 128 * 0.3f,
		Drop::DropType::POINTS
	);
	levelBodies.push_back(points);
	points = nullptr;

	return true;
}


void Level_test::OnDestroy(){
	//Destroys everything except the player
	for (Body* body : levelBodies) {
		if (body->type == body->PLAYER) {
			body = nullptr;
			continue;
		}
		body->OnDestroy();
		delete body;
	} 
	levelBodies.clear();

	if (background) {
		SDL_DestroyTexture(background);
		background = nullptr;
	}
	delete background;

	floor->OnDestroy();
	delete floor;
}


void Level_test::Update(const float time){
	newMobSpawner->waveSpawner(3);


	if (newMobSpawner->levelWon) {
		canSwitchTheScene = true;
		cc.log(update, "level is finished");
	}

	//Updates the level bodies
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
	if (trashBodies.empty()) { return; } //Exit early if there are no necessary cleanups
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
	SDL_RenderCopy(parentScene->getRenderer(), background, nullptr, nullptr); //render the background
	floor->Render(renderer_, projectionMatrix_); //render the floor

	for (Body* body : levelBodies) {
		body->Render(renderer_, projectionMatrix_);
		body->RenderHitbox(renderer_);		//	[DEBUG] renders all body hitboxes 
	}
}

void Level_test::HandleEvents(const SDL_Event& event){
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}
