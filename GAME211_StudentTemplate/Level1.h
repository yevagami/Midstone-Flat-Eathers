#ifndef LEVEL1_H
#define LEVEL1_H


#include "BaseLevel.h"
#include "Solid.h"
#include "PlayerBody.h"

class Level1 : public BaseLevel{
private: 
	SDL_Texture* background = nullptr;
public:


	//Scene objects
	std::vector<Body*>sceneObjects;
	std::vector<Body*>trashObjects;

	//Constructor
	Level1(Scene* currentScene);
	~Level1();

	//Fundamental methods (create, update, render, handle input, destroy)
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time) override;
	void Render() override;
	void HandleEvents(const SDL_Event& event) override;

	//getters and setters

};
#endif