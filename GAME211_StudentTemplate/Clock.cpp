#include "Clock.h"


Clock::Clock(float duration_, bool isLooping_) {
	duration = duration_;
	isLooping = isLooping_;
	callback = nullptr;
}

Clock::Clock(float duration_, bool isLooping_, std::function<void()> callback_) {
	duration = duration_;
	isLooping = isLooping_;
	callback = callback_;
}


void Clock::Start() {
	//if the clock has not started, start it
	if (!hasStarted) { hasStarted = true; }
}

void Clock::Update(float deltaTime){
	//if the clock has started and is not finished, start it
	if (!completed && hasStarted) {
		timer += deltaTime;

		//if the timer has elapsed through the duration then it is finished
		if (timer >= duration) {
			completed = true;
			if (callback != nullptr) { callback(); }

			//if the timer is a continuously looping one, reset the timer and start over
			if (isLooping) {
				Reset();
				Start();
			}
		}
	}
}


//resets everything in the time
void Clock::Reset() {
	timer = 0;
	completed = false;
	hasStarted = false;
}


void Clock::OnDestroy() {

}