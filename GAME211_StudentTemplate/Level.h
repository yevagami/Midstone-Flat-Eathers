#pragma once
#include "Body.h";
#include <vector>
class Level{
private:
	std::vector<Body*>LevelObjects;
	std::vector<Body*>Entities;
	
public:
	bool debug = false;
	void LoadLevel();
	void Update(float deltaTime);
	void HandleEvents();
	void OnDestroy();
};

