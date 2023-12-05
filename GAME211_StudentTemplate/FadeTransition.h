#pragma once
#include <SDL_render.h>
#include <SDL_timer.h>

//	stinky gross iostream
#include <functional>
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
//	- getting good and figruing out why it no fadey fade :(
//
//	with debugging:
//	it doesnt seem to EVER update the alpha value... it sets it once, creates the rectangle, waits the time, then releases the rectangle :thinking:


//	dec 1
//	it works now lol amazing hahahhahahha im so good at programming


class FadeTransition {
public:
	//	constructor
	FadeTransition(SDL_Renderer* renderer_, const int currentFPS_, const int screenHeight_, const int screenWidth_, const Uint32 fadeTime_, const bool fadingIn_ = true, const std::function<void()>&callback_ = nullptr) :
		renderer(renderer_),
		currentFPS(currentFPS_),
		startTime(0),
		currentProgress(0),
		fadeTime(fadeTime_),
		fadeIn(fadingIn_),
		alpha(fadeIn ? MaxAlpha : MinAlpha),
		screenHeight(screenHeight_),
		screenWidth(screenWidth_),
		callbackFunction(callback_)
	{
		//	set the renderers blend mode to alpha blending
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	}

	//	sets the startTime variable to whatever the current time is (time since SDL was initialized, in a 64 bit manner)
	void SetStartTime() {
		startTime = SDL_GetTicks();
		cout << "\033[34mfade time is: \033[36m" << fadeTime << "\033[34m SDL ticks " << "\033[0m" << endl;
		cout << "\033[34mstart time is: \033[36m" << startTime << "\033[34m SDL ticks " << "\033[0m" << endl;
		cout << "\033[34mfade frame rate is: \033[36m" << currentFPS << "\033[34m fps" << "\033[0m" << endl;
		if (callbackFunction) { cout << "\033[31mcallbackFunction provided" << "\033[0m" << endl; }
		else if (!callbackFunction) { cout << "\033[31mno callbackFunction provided" << "\033[0m" << endl; }
	}

	// returns true if the elapsed time since the start of the fade transition is greater than or equal to the specified fade time; otherwise return false.
	[[nodiscard]] bool isComplete() const {
		cout << "\033[34mcurrent progress: \033[36m" << currentProgress * 100 << "%\033[0m" << endl;
		constexpr float epsilon = 0.001f; // Adjust the epsilon based on your precision requirements
		return currentProgress + epsilon >= 1.0f;
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
		cout << "\033[34malpha updating progress: \033[36m" << currentProgress * 100 << "% ";

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;

		if (elapsedTime >= fadeTime) {
			// the fade is completed
			alpha = fadeIn ? MaxAlpha : MinAlpha;
			currentProgress = 1.0f;
		}
		else {
			// Calculate the interpolation factor (currentTime = elapsedTime / fadeTime)
			currentProgress = static_cast<float>(elapsedTime) / static_cast<float>(fadeTime);
			// Interpolate the alpha directly
			alpha = static_cast<int>(MinAlpha + currentProgress * (MaxAlpha - MinAlpha));

			cout << "\033[34m| alpha: \033[36m" << alpha << "\033[0m" << endl;
		}
	}

	void Draw() {
		while (!isComplete()) {
			UpdateAlpha();

			// create a new rectangle based off the screen Width and Height provided in the constructor
			const SDL_Rect getREKTangle = { 0, 0, screenWidth, screenHeight };

			// draw the fading rectangle
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
			SDL_RenderFillRect(renderer, &getREKTangle);
			SDL_RenderPresent(renderer);

			// wait for a short duration to control the animation speed
			SDL_Delay(currentFPS);
		}

		// Ensure that the callback is called after the animation is complete
		if (callbackFunction) {
			cout << "\033[31mcallbackFunction called" << "\033[0m" << endl;
			callbackFunction();
			callbackFunction = nullptr;
		}
	}

protected:
	SDL_Renderer* renderer;
	Uint32 startTime;
	float currentProgress;
	Uint32 fadeTime;

	std::function<void()> callbackFunction;

	bool fadeIn;
	int alpha;

	static const int MaxAlpha = 255;
	static const int MinAlpha = 0;

	int screenHeight;
	int screenWidth;

	int currentFPS;
	int smoothness = 5;

	static float LerpyLerp(const float a_, const float b_, const float t_) {
		return a_ + t_ * (b_ - a_);
	}
};

