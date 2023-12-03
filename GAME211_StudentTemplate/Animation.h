#pragma once
#include "SpriteDefs.h"
#include "Clock.h"
using namespace std;


class Animation{
public:
	vector<SDL_Rect> Frames; //The individual sdl_rect of the frames
	SDL_Rect currentFrame; //The current frame in the animation
	int currentFrameIndex = 0; //The index of which frame is used in the sdl_rect
	float interval; //The duration between frames
	bool isLooping; //If the animation loops or not, if not return to the first frame
	int frameDuration; //How many frames are in the animation

	void SetFrames(vector<SDL_Rect> Frames_) { Frames = Frames_; } //Set the frames in the animation
	SDL_Rect GetCurrentFrame() { return currentFrame; }
	vector<SDL_Rect> GetFrames() { return Frames; }

	Animation(vector<SDL_Rect> Frames_, float interval_, int frameDuration_, bool isLooping_ = true) {
		Frames = Frames_;
		interval = interval_;
		frameDuration = frameDuration_;
		isLooping = isLooping_;
	}
};

class AnimationController {
private:
	Clock* update_timer; //The clock to update the animation
	SDL_Rect currentFrame; //The current frame in the animation
	Animation currentAnimation; //The current animation that is being played
	bool isPaused; //If the animation is paused
	int currentFrameIndex = 0; //The index of which frame is used in the sdl_rect

public:
	AnimationController();
	~AnimationController();
	void UpdateAnimationController(float deltaTime);
	void PlayAnimation(Animation newAnimation) { 
		currentAnimation = newAnimation; 
		update_timer->Reset();
		currentFrameIndex = 0;
	} //Set the current animation to a new animation

	//Getters and setters
	SDL_Rect GetCurrentFrame() { return currentFrame; }
	Animation GetCurrentAnimation() { return currentAnimation; }
};

