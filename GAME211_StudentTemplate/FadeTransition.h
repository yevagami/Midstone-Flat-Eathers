#pragma once
#include <SDL_render.h>
#include <SDL_timer.h>


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
		fadeTime(fadeTime_),
		fadeIn(fadingIn_),
		screenHeight(screenHeight_),
		screenWidth(screenWidth_)
	{
		//	sets the initial alpha value based off the fade direction
		alpha = fadeIn ? 255 : 0; 
	}


	//	sets the startTime variable to whatever the current time is (time since SDL was initialized, in a 64 bit manner)
	void Start() {
		startTime = SDL_GetTicks64();
	}


	// returns true if the elapsed time since the start of the fade transition is greater than or equal to the specified fade time; otherwise return false.
	[[nodiscard]] bool isComplete() const {
		return SDL_GetTicks64() - startTime >= fadeTime;
	}

	//	returns the remaining time since the transition has been called
	[[nodiscard]] Uint64 GetRemainingTime() const {
		const Uint64 currentTime = SDL_GetTicks64();
		Uint64 elapsedTime = currentTime - startTime;

		if (elapsedTime >= fadeTime) {
			return 0; 
		} else {
			return fadeTime - elapsedTime;
		}
	}


	//	updates the alpha value
	void Update() {
		const Uint64 currentTime = SDL_GetTicks64();
		Uint64 elapsedTime = currentTime - startTime;

		if(elapsedTime >= fadeTime) {
			//	the fade is completed
			alpha = fadeIn ? 255 : 0; 
		}
		else {
			// calculate the interpolation factor (time = elapsedTime / fadeTime)
			float t = static_cast<float>(elapsedTime) / static_cast<float>(fadeTime);
			if(!fadeIn) {
				t = 1.0f - t;
			}

			//	lerpify the alpha (professional terminology)
			alpha = static_cast<Uint8>(LerpyLerp(fadeIn ? 0 : 255, fadeIn ? 255 : 0, t));
		}

	}

	void Draw() const {
		//	clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//	draw the fading rectangle (wow rectangles are so cool)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
		const SDL_Rect rektangle = { 0,0,screenWidth, screenHeight };
		SDL_RenderFillRect(renderer, &rektangle);

		SDL_RenderPresent(renderer);
	}

protected:
	SDL_Renderer* renderer;
	Uint64 startTime;
	Uint64 fadeTime;

	bool fadeIn;
	Uint8 alpha;

	int screenHeight;
	int screenWidth;

	static float LerpyLerp(const float a_, const float b_, const float t_) {
		return a_ + t_ * (b_ - a_);
	}
};

