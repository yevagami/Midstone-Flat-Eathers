#include "Clock.h"

Clock::Clock(){
	duration = 5;
}

Clock::Clock(float duration_) {
	duration = duration_;
}

void Clock::Update(float deltaTime){
	if (!completed) {
		timer += deltaTime;

		if (timer >= duration) {
			completed = true;
			callback();
		}
	}
}


void Clock::Reset() {
	timer = 0;
	completed = false;
}


void Clock::OnDestroy() {
}