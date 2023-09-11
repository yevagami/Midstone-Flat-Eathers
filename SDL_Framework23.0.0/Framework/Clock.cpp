#include "Clock.h"

Clock::Clock(){
	duration = 5;
}

Clock::Clock(float duration_, bool isLooping_) {
	duration = duration_;
	isLooping = isLooping_;
}


void Clock::Update(float deltaTime){
	if (!completed) {
		timer += deltaTime;

		if (timer >= duration) {
			completed = true;
			callback();


			if (isLooping) {
				Reset();
			}
		}
	}
}


void Clock::Reset() {
	timer = 0;
	completed = false;

}


void Clock::OnDestroy() {
}