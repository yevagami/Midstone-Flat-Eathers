#include "Clock.h"

void Clock::Update(float deltaTime){
	timer += deltaTime;
	if (timer >= duration) {
		CallBack();
	}
}
