#pragma once
#include <SDL.h>
#include <string>
#include <vector>

namespace ui {
	class Button;
}

namespace stolen {
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 768;
}

class Tracker {
public:
	Tracker() = default;

	//	tell a tracker to track a value (do this in update)
	void trackThis(std::string value_, ui::Button* tracker_);

	//	init all "trackers" (shh, theyre buttons)
	void scary();
	//	destroy all trackers
	void unscary() const;
	void render(SDL_Renderer* renderer_) const;

	//	testing
	static int genRanNum(int min_, int max_);

	std::vector<ui::Button*> allTrackers;

	ui::Button* tracker1;
	ui::Button* tracker2;
	ui::Button* tracker3;
	ui::Button* tracker4;
	ui::Button* tracker5;
	ui::Button* tracker6;
	ui::Button* tracker7;
	ui::Button* tracker8;
	//	we skip 9 in this household
	ui::Button* tracker10;
protected:
};
