#pragma once
#include "Level.h"
#include "Menu.h"

using namespace ui;



class Level_MainMenu : public Level{
private:

	Button* shhh;

	vector<Button*> allButtons;
	Button* button1;
	Button*button2;
	//Button*button3;

	vector<Button*> allTexts;
	Button*text1;
	Button*text2;
	Button*text3;

public:
	//Mob_Spawner* newMobSpawner = new Mob_Spawner(this);
	Level_MainMenu(Scene* parentScene_) : Level(parentScene_) {}

	//Method that spawns the enemies
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float time_) override;
	void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
	void HandleEvents(const SDL_Event& event_) override;
	
};

