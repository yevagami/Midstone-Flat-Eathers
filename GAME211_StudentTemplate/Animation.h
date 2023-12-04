#pragma once
#include "SpriteDefs.h"
#include "Clock.h"
using namespace std;


class Animation{
public:
	vector<SDL_Rect> Frames; //The individual sdl_rect of the frames
	int currentFrameIndex = 0; //The index of which frame is used in the sdl_rect
	float interval; //The duration between frames
	bool isLooping; //If the animation loops or not
	int frameDuration; //How many frames are in the animation
	const char* name;

	void SetFrames(vector<SDL_Rect> Frames_) { Frames = Frames_; } //Set the frames in the animation
	vector<SDL_Rect> GetFrames() { return Frames; }
	Animation() {};

	Animation(const char* name_, vector<SDL_Rect> Frames_, float interval_, int frameDuration_, bool isLooping_ = true) {
		Frames = Frames_;
		interval = interval_;
		frameDuration = frameDuration_;
		isLooping = isLooping_;
		name = name_;
	}

	Animation(const char* name_, SDL_Rect Frame_, float interval_, int frameDuration_, bool isLooping_ = true) {
		Frames.push_back(Frame_);
		interval = interval_;
		frameDuration = frameDuration_;
		isLooping = isLooping_;
		name = name_;
	}

	//For organizing purposes
	bool operator==(const Animation &other) const {
		return this->name == other.name;
	}
};

class AnimationController {
private:
	Clock* update_timer; //The clock to update the animation
	SDL_Rect* currentFrame; //The current frame in the animation
	Animation currentAnimation; //The current animation that is being played
	bool isPaused = false; //If the animation is paused
	int currentFrameIndex = 0; //The index of which frame is used in the sdl_rect

public:
	AnimationController();
	~AnimationController();
	void UpdateAnimationController(float deltaTime);
	void PlayAnimation(Animation newAnimation); //Set the current animation to a new animation
	void Pause() { isPaused = true; }
	void Play() { isPaused = false; }

	//Getters and setters
	SDL_Rect* GetCurrentFrame() { return currentFrame; }
	Animation GetCurrentAnimation() { return currentAnimation; }
};

