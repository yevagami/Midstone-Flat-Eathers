#include "Animation.h"

void Animation::NextFrame() {
	currentFrameIndex++;
	if(currentFrameIndex > Frames.size() - 1){
		currentFrameIndex = 0;
	}
	currentFrame = Frames[currentFrameIndex];
}

void Animation::PlayAnimation(float deltaTime) {

}
