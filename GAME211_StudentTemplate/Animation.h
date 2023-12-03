#pragma once
#include "SpriteDefs.h"
#include "Clock.h"

using namespace std;
class Animation{
	vector<SDL_Rect> Frames;
	SDL_Rect currentFrame;
	int currentFrameIndex = 0;
	float interval;
	float isLooping;
	float isPaused;
	Clock* interval_timer;

	void SetFrames(vector<SDL_Rect> Frames_) { Frames = Frames_; }
	SDL_Rect GetCurrentFrames() { return currentFrame; }
	vector<SDL_Rect> GetFrames() { return Frames; }
	void NextFrame();
	void PlayAnimation(float deltaTime);
	void PauseAimation();
	void RestartAnimation();
	void RenderAnimation();
};


