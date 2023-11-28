#pragma once
#include <SDL_render.h>
#include <SDL_timer.h>

//	stinky gross iostream
#include <iostream>
using std::cout;
using std::endl;


//	
//	notes from monday night (nov 27th)
//	this sucks.
//	
//	currently I'm trying to render a rectangle over the current scene and fade that in/out
//	chat gpt says its beautiful but clearly something isnt working
//	what works:
//	- it pauses the game for the duration provided
//	- it renders a black box on the screen during this 'paused time' (elapsed time)
//	what doesnt work:
//	- the whole fading aspect (alpha changing)
//	
//	next steps: (to try)
//	- SDL_SetGammaRamp() instead of this method. its different and could work idk
//	- getting good and figruing out why it no fadey fade :(
//

//	with debugging:
//	it doesnt seem to EVER update the alpha value... it sets it once, creates the rectangle, waits the time, then releases the rectangle :thinking:



class FadeTransition {
public:
	//	constructor
	FadeTransition(SDL_Renderer* renderer_, const int screenHeight_, const int screenWidth_, const Uint32 fadeTime_, const bool fadingIn_ = true) :
		renderer(renderer_),
		startTime(0),
		currentProgress(0),
		fadeTime(fadeTime_),
		fadeIn(fadingIn_),
		alpha(fadeIn ? 255 : 0),
		screenHeight(screenHeight_),
		screenWidth(screenWidth_)
	{
		//	set the renderers blend mode to alpha blending
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}


	//	sets the startTime variable to whatever the current time is (time since SDL was initialized, in a 64 bit manner)
	void SetStartTime() {
		startTime = SDL_GetTicks();
		cout << "start time is: " << startTime << endl;
	}


	// returns true if the elapsed time since the start of the fade transition is greater than or equal to the specified fade time; otherwise return false.
	[[nodiscard]] bool isComplete() const {
		return SDL_GetTicks64() - startTime >= fadeTime;
	}

	//	returns the remaining time since the transition has been called
	[[nodiscard]] Uint32 GetRemainingTime() const {
		const Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;

		//	"if elapsed time is greater than or equal to fadeTime, return 0; otherwise, return the progress"
		return elapsedTime >= fadeTime ? 0 : fadeTime - elapsedTime;
	}


	//	updates the alpha value based off current progress
	void UpdateAlpha() {
		cout << "\033[34malpha updating progress: \033[36m" << currentProgress;

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;

		if(elapsedTime >= fadeTime) {
			//	the fade is completed
			alpha = fadeIn ? 255 : 0;
			currentProgress = 1.0f;
		} else {
			// calculate the interpolation factor (currentTime = elapsedTime / fadeTime)
			currentProgress = 
				static_cast<float>(elapsedTime)
			/	static_cast<float>(fadeTime);

			//	lerpify the alpha (professional terminology)
			alpha = 	static_cast<int>(LerpyLerp(fadeIn ? 0 : 255, fadeIn ? 255 : 0, currentProgress));

			cout << "\033[34m | alpha: \033[36m" << alpha << "\033[0m"<< endl;
		}
	}

	void Draw() {
		UpdateAlpha();

		///	we dont clear renderers in this household
		//	clearing would remove the frame before, making it abruptly begin the fade

		//	create a new rectangle based off the screen Width and Height provided in the constructor
		const SDL_Rect rektangle = { 0,0,screenWidth, screenHeight };

		//	draw the fading rectangle (wow rectangles are so cool)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
		SDL_RenderFillRect(renderer, &rektangle);
		SDL_RenderPresent(renderer);

		//	short delay to hopefully maybe in theory (game theory) prevent flickering
		//SDL_Delay(60);
		//SDL_Delay(GetSleepTime(60)); ///60 frames per sec

	}

protected:
	SDL_Renderer* renderer;
	Uint32 startTime;
	float currentProgress;
	Uint32 fadeTime;

	bool fadeIn;
	int alpha;

	int screenHeight;
	int screenWidth;

	static float LerpyLerp(const float a_, const float b_, const float t_) {
		return a_ + t_ * (b_ - a_);
	}
};

