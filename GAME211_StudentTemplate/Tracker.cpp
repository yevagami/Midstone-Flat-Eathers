#include "Tracker.h"
#include <random>
#include "Menu.h"

void Tracker::trackThis(std::string value_, ui::Button* tracker_) {
	tracker_->text = std::move(value_);
}

void Tracker::scary() {
	using namespace ui; using namespace stolen;

	constexpr int fontSize = 20;

	//	setting up the trackers with default values
	tracker1 = new Button(Font{ "", fontSize });
	tracker2 = new Button(Font{ "", fontSize });
	tracker3 = new Button(Font{ "", fontSize });
	tracker4 = new Button(Font{ "", fontSize });
	tracker5 = new Button(Font{ "", fontSize });

	//	into the vector they go
	allTrackers.emplace_back(tracker1);
	allTrackers.emplace_back(tracker2);
	allTrackers.emplace_back(tracker3);
	allTrackers.emplace_back(tracker4);
	allTrackers.emplace_back(tracker5);


	for (const auto tracker : allTrackers) {
		tracker->isTextBordered = true;
		tracker->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
		tracker->textColour = SDL_COLOR_ANTIQUE_WHITE;
		tracker->offsetPosition(-SCREEN_HEIGHT + 400);
	}
	tracker2->setPositionRelativeTo(*tracker1, 25);
	tracker3->setPositionRelativeTo(*tracker2, 25);
	tracker4->setPositionRelativeTo(*tracker3, 25);
	tracker5->setPositionRelativeTo(*tracker4, 25);


}

void Tracker::unscary() {
	for (const auto tracker : allTrackers) {
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
