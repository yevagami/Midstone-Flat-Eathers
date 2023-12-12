#include "Level_3.h"

//I might have to reorder the methods for organizing purposes

bool Level_3::OnCreate() {

	name = "Level_3";

	//Creating the background
	background = SDL_CreateTextureFromSurface(parentScene->getRenderer(), IMG_Load("Textures/programmer_art/background.png"));

	//Note:
	//I made the screen size and the physics size the same because it's much easier to use when constructing levels
#pragma region Creating Level geometry
	//Creating the floor
	floor = new Body(this, Vec3((1366.0f / 2.0f), 768.0f / 2.0f, 0.0f), Vec3(60.0f, 30.0f, 10.0f), 1.0f, 1.0f, IMG_Load("Textures/programmer_art/tile_floor_level_3.png"));


	//creating the walls
	// UP RIGHT BOX
	//top 
	//Accent to make the wall look nicer, also by default bodies don't have collision
	Body* tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f), 768.0f / 2.0f + 128 * 5.5 - 100, 0.0f),
		Vec3(17.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	Solid* wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f), 768.0f / 2.0f + 128 * 5.5, 0.0f),
		Vec3(17.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	

	//right
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) + 1025.0f, 768.0f / 2.0f + 128 * 5.5 - 400, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) + 1025.0f, 768.0f / 2.0f + 128 * 5.5 - 300, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	

	//left
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1025.0f, 768.0f / 2.0f + 128 * 5.5 - 400, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1025.0f, 768.0f / 2.0f + 128 * 5.5 - 300, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);



	//bottom
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 720, 768.0f / 2.0f + 110, 0.0f),
		Vec3(4.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);
	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 720, 768.0f / 2.0f + 210, 0.0f),
		Vec3(4.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	//bottom
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) + 600, 768.0f / 2.0f + 110, 0.0f),
		Vec3(6.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) + 600, 768.0f / 2.0f + 210, 0.0f),
		Vec3(6.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	//UP LEFT BOX
	//top
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1900.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 400, 0.0f),
		Vec3(13.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);
	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1900.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 300, 0.0f),
		Vec3(13.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	//left
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 2670.0f, 768.0f / 2.0f + 128 * 5.5 - 545, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 2670.0f, 768.0f / 2.0f + 128 * 5.5 - 445, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);


	
	//bottom
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 2400.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 870, 0.0f),
		Vec3(5.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 2400.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 770, 0.0f),
		Vec3(5.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	//right
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1670.0f, 768.0f / 2.0f + 128 * 5.5 - 545, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1670.0f, 768.0f / 2.0f + 128 * 5.5 - 445, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	// right hallway

	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 2400.0f, 768.0f / 2.0f + 128 * 5.5 - 1000, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 2400.0f, 768.0f / 2.0f + 128 * 5.5 - 900, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	//BOTTOM BOX

	//bottom1
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 2100.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1328, 0.0f),
		Vec3(4.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);
	

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 2100.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1228, 0.0f),
		Vec3(4.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	// left

	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1910.0f, 768.0f / 2.0f + 128 * 5.5 - 1400, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1910.0f, 768.0f / 2.0f + 128 * 5.5 - 1300, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	//lowest bottom
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1215.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1725, 0.0f),
		Vec3(10.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1215.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1625, 0.0f),
		Vec3(10.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	//right

	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 520.0f, 768.0f / 2.0f + 128 * 5.5 - 1400, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	tiles = new Body( //rendering here bcause otherwise not pretty overlap of textures 
		this,
		Vec3((1366.0f / 2.0f) + 70.0f, 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1300, 0.0f),
		Vec3(10.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 520.0f, 768.0f / 2.0f + 128 * 5.5 - 1300, 0.0f),
		Vec3(1.0f, 4.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);
	
	//LEFT BOTTOM BOX
	//right
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) + 650.0f, 768.0f / 2.0f + 128 * 5.5 - 900, 0.0f),
		Vec3(1.0f, 5.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) + 650.0f, 768.0f / 2.0f + 128 * 5.5 - 800, 0.0f),
		Vec3(1.0f, 5.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	//bottom
	

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) + 70.0f , 768.0f - 500.0f / 2.0f + 128 * 5.5 - 1200, 0.0f),
		Vec3(10.0f, 1.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	//MIDDLE 
	tiles = new Body(
		this,
		Vec3((1366.0f / 2.0f) - 1100.0f, 768.0f / 2.0f + 128 * 5.5 - 1100, 0.0f),
		Vec3(1.0f, 2.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_bottom_level_3.png")
	);
	levelBodies.push_back(tiles);

	wall = new Solid(
		this,
		Vec3((1366.0f / 2.0f) - 1100.0f, 768.0f / 2.0f + 128 * 5.5 - 1000, 0.0f),
		Vec3(1.0f, 2.0f, 1.0f),
		128,
		128,
		IMG_Load("Textures/programmer_art/tile_roof_level_3.png")
	);
	levelBodies.push_back(wall);

	wall = nullptr;

#pragma endregion*/
	return true;
}


void Level_3::OnDestroy() {
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


void Level_3::Update(const float time) {

	newMobSpawner->waveSpawner(3);

	if (newMobSpawner->levelWon) {
		canSwitchTheScene = true;
		cc.log(update, "level is finished");
	}

	//Updates the level bodies
	for (Body* body : levelBodies) {
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

void Level_3::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {
	SDL_RenderCopy(parentScene->getRenderer(), background, nullptr, nullptr); //render the background
	floor->Render(renderer_, projectionMatrix_); //render the floor

	for (Body* body : levelBodies) {
		body->Render(renderer_, projectionMatrix_);
		body->RenderHitbox(renderer_);		//	[DEBUG] renders all body hitboxes 
	}
}

void Level_3::HandleEvents(const SDL_Event& event) {
	for (Body* body : levelBodies) {
		body->HandleEvents(event);
	}
}
