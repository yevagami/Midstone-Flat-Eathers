#include "Tracker.h"

#include <random>

#include "Menu.h"

void Tracker::trackThis(std::string value_, ui::Button* tracker_) {
	tracker_->text = std::move(value_);
}
void Tracker::scary() {
	int size = 20;
	tracker1 = new ui::Button(ui::Font{ "", size });
	tracker2 = new ui::Button(ui::Font{ "", size });
	tracker3 = new ui::Button(ui::Font{ "", size });
	tracker4 = new ui::Button(ui::Font{ "", size });
	tracker5 = new ui::Button(ui::Font{ "", size });
	allTrackers.emplace_back(tracker1);
	allTrackers.emplace_back(tracker2);
	allTrackers.emplace_back(tracker3);
	allTrackers.emplace_back(tracker4);
	allTrackers.emplace_back(tracker5);

	for (auto t : allTrackers) {
		t->centerPosition(stolen::SCREEN_WIDTH, stolen::SCREEN_HEIGHT);
		t->textColour = ui::SDL_COLOR_ANTIQUE_WHITE;
		t->offsetPosition(-stolen::SCREEN_HEIGHT + 400);
	}
	tracker2->setPositionRelativeTo(*tracker1, 25);
	tracker3->setPositionRelativeTo(*tracker2, 25);
	tracker4->setPositionRelativeTo(*tracker3, 25);
	tracker5->setPositionRelativeTo(*tracker4, 25);


}

void Tracker::unscary() {
	for (auto tracker : allTrackers) {
		delete tracker;
	}
}

void Tracker::render(SDL_Renderer* renderer_) {
	for (auto tracker : allTrackers) {
		tracker->Render(renderer_);
	}
}

int Tracker::genRanNum(int min_, int max_) {
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(min_, max_);
	//std::cout << distrib(gen) << std::endl;
	return distrib(gen);
}
