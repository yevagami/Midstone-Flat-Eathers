#pragma once
#include "Body.h";
#include <vector>
class Level{
private:
	std::vector<Body*>LevelObjects;
	std::vector<Body*>Entity;

public:
	bool debug = false;
	void LoadLevel();
	void Update(float deltaTime);
	void OnDestroy();
};

