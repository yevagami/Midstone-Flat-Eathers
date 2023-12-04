#include "Animation.h"
AnimationController::AnimationController() {
	update_timer = new Clock(0.1f, true, [this](){
		currentFrameIndex = (currentFrameIndex + 1 > currentAnimation.frameDuration) ? 0 : currentFrameIndex + 1;
		currentFrame = &currentAnimation.Frames[currentFrameIndex];
		cout << "Next frame\n";
	});
}

AnimationController::~AnimationController() {
	delete update_timer;
}

void AnimationController::UpdateAnimationController(float deltaTime) {
	if (isPaused) {
		update_timer->Update(deltaTime);
		cout << update_timer->timer << endl;
	}
}


void AnimationController::PlayAnimation(Animation newAnimation) {
	//Reset some of the values
	currentAnimation = newAnimation;
	update_timer->Reset();
	currentFrameIndex = 0;

	//After reseting, set the new values
	update_timer->isLooping = newAnimation.isLooping;
	update_timer->duration = currentAnimation.interval;
	update_timer->Start();

	//Set the current frame
	currentFrame = &currentAnimation.Frames[currentFrameIndex];
}