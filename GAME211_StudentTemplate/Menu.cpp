#include "Menu.h"
#include <random>
#include <SDL_image.h>
#include "ConsistentConsole.h"

ConsistentConsole ccMenu(false, "Menu.cpp");


namespace ui {
#pragma region Core Methods
	void Button::HandleEvents(const SDL_Event& event_) {
		if (isActive) {

			switch (event_.type) {

				//	hovering events
			case SDL_MOUSEMOTION:
				if (isMouseOver(event_.motion.x, event_.motion.y)) {
					Uint32 currentTime = SDL_GetTicks();
					isHovering = true;

					//	if theres an OnHover method AND its off cooldown
					if (OnHover && currentTime - lastHoverTime >= 1000) {
						OnHover();
						lastHoverTime = currentTime;
					}
				}
				else { isHovering = false; }
				break;

				//	clicking events
			case SDL_MOUSEBUTTONDOWN:
				if (event_.button.button == SDL_BUTTON_LEFT) {
					if (OnLeftClick && hitbox.collisionClickCheck(event_.motion.x, event_.motion.y)) {
						//	this happens when the button is left clicked
						OnLeftClick();
						ccMenu.log(not_error, "button left clicked :l");
						if (isTogglable) { isOn = !isOn; backgroundColour = !backgroundColour;  ccMenu.log(not_error, "button toggled"); std::cout << isOn << std::endl; }
						if (isPrideful) { backgroundColour = ~backgroundColour; textColour = !textColour; ccMenu.log(not_error, "button colour change"); }
						if (isEasilyScared) { isActive = !isActive; }
					}
				}
				else if (event_.button.button == SDL_BUTTON_RIGHT) {
					if (OnRightClick && hitbox.collisionClickCheck(event_.motion.x, event_.motion.y)) {
						//	this happens when the button is right clicked
						OnRightClick();
						ccMenu.log(not_error, "button right clicked :O");
					}
				}
				break;


			case SDL_MOUSEWHEEL:
				//	this happens when the button is scrolled on
				if (OnScroll && isMouseOver(event_.motion.x, event_.motion.y)) {
					OnScroll(event_.wheel.y);
				}
				break;

				//	default;
			default:
				break;
			}
		}
	}


	void Button::Update(float deltaTime_) { }


	void Button::SetOnLeftClick(const std::function<void()>& onClick_) { OnLeftClick = onClick_; }
	void Button::SetOnRightClick(const std::function<void()>& onClick_) { OnRightClick = onClick_; }
	void Button::SetOnHover(const std::function<void()>& onHover_) { OnHover = onHover_; }
	void Button::SetOnScroll(const std::function<void(int scrollInt_)>& onScroll_) { OnScroll = onScroll_; }


#pragma region Rendering
	bool Button::Render(SDL_Renderer* buttonRenderer_) {
		if (isActive) {
			if (rect.w != 0 && rect.h != 0) {		//	if the rectangle exists...
				if (!RenderBackground(buttonRenderer_) || !RenderBorder(buttonRenderer_) || !RenderText(buttonRenderer_)) {	//	render all 3 components
					return false;
				} ClearSDLStuff();	//	no leaks pls
				return true;
			}	//	if the rectangle doesn't exist...
			if (!RenderText(buttonRenderer_)) { //	just render the text
				return false;
			} ClearSDLStuff();	//no	leaks pls
			return true;
		}
		return true; //	inactive buttons matter too.
		//	(returning true because the initial condition checks to see if the button is enabled. a disabled button isnt an error with rendering, so we're return true)
	}

	auto Button::EnableBackgroundImage(const char* fileDirectory_) -> bool {
		if(fileDirectory_ != "") {
			backgroundImageDirectory = fileDirectory_;
		}

		backgroundType = BackgroundType::Image;
		return true;
	}
		
	


	bool Button::RenderBackground(SDL_Renderer* renderer_) const {
		if (rect.w != 0 && rect.h != 0) {
			if (backgroundType == BackgroundType::SolidColour) {
				//	if isHovering, backgroundColour is divided by the onHoveringBackgroundColour
				const SDL_Color renderColour =
					isHovering ? (backgroundColour / onHoveringBackgroundColour) : backgroundColour; //	isHovering checker. If true, colour is bkgCol / onHovBkg. If false, colour is bkgCol.

				SDL_SetRenderDrawColor(renderer_, renderColour.r, renderColour.g, renderColour.b, renderColour.a);
				SDL_RenderFillRect(renderer_, &rect);

				return true;
			}


			if (backgroundType == BackgroundType::Image) {
				SDL_Surface* backgroundImageSurface = IMG_Load(backgroundImageDirectory);

				if(backgroundImageSurface != nullptr) {
					SDL_Texture* renderedTexture = SDL_CreateTextureFromSurface(renderer_, backgroundImageSurface);

					if (renderedTexture != nullptr) {
						SDL_Point center = { 0, 0 };
						SDL_RendererFlip flip = SDL_FLIP_NONE;

						SDL_RenderCopyEx(renderer_, renderedTexture, nullptr, &rect, backgroundImageRotationAngle, &center, flip);
					
						SDL_DestroyTexture(renderedTexture);
					}
					SDL_FreeSurface(backgroundImageSurface);
				}
				return true;
			}
		}
		return true;
	}

	bool Button::RenderBorder(SDL_Renderer* renderer_) const {
		if (isButtonBordered) { // if borders are enabled...
			const SDL_Color renderColour =
				isHovering ? !backgroundColour : buttonBorderColour;	//	isHovering checker. If true, colour is inverted bkgCol. If false, colour is borderCol.

			for (int i = 0; i < buttonBorderSize; i++) {
				SDL_Rect paddedRect = {
					rect.x + i,
					rect.y + i,
					rect.w - 2 * i,
					rect.h - 2 * i
				};
				SDL_SetRenderDrawColor(renderer_, renderColour.r, renderColour.g, renderColour.b, renderColour.a);
				SDL_RenderDrawRect(renderer_, &paddedRect);
			}
			return true;
		}
		return true;
	}

	bool Button::RenderText(SDL_Renderer* renderer_) {
		if (text.empty()) { return false; }

		//	1. set up a font
		buttonTextFont = TTF_OpenFont(fontItself, fontSize);
		if (!buttonTextFont) { return false; }

		//	if isHovering, textColour tints
		const SDL_Color renderColour =
			isHovering ? (textColour * onHoveringTextColour) : textColour;	//	isHovering checker. If true, colour is txtCol / onHovTxt. If false, colour is txtCol.

		//	2. set up a surface image with some text
		buttonTextSurface = TTF_RenderText_Solid(buttonTextFont, text.c_str(), renderColour);
		if (!buttonTextSurface) { return false; }

		// 3. set up a texture for the surface
		buttonTextTexture = SDL_CreateTextureFromSurface(renderer_, buttonTextSurface);
		if (!buttonTextSurface && !buttonTextFont && !buttonTextTexture) { return false; }

		int textWidth, textHeight;
		SDL_QueryTexture(buttonTextTexture, nullptr, nullptr, &textWidth, &textHeight);
		//	aesthetic: text centering

		//	centering, check if its centered
		int x, y;	
		if (isTextCentered) {
			x = rect.x + (rect.w - textWidth) / 2;
			y = rect.y + (rect.h - textHeight) / 2;
		} else {
			x = rect.x;
			y = rect.y;
		}
		//	make a rect based off the centered text
		SDL_Rect textRect = { x, y, textWidth, textHeight }; 
		textRect.x += fontOffsetX;		//	offset the text based off the font offset
		textRect.y += fontOffsetY;		//	offset the text based off the font offset

		//	4. set up text borders (if enabled)
#pragma region text borders
		if (isTextBordered) {
			SDL_Surface* borderTextSurface = TTF_RenderText_Solid(buttonTextFont, text.c_str(), textBorderColour);
			SDL_Texture* borderTextTexture = SDL_CreateTextureFromSurface(renderer_, borderTextSurface);

			//	render multiple copies of the border in different directions. +x, -x, +y, -y, +xy, -xy, +x-y, -x+y
			// render +x border
			SDL_Rect borderTextRectPlusX = {
				textRect.x + textBorderSize,
				textRect.y,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectPlusX, fontRotation, nullptr, SDL_FLIP_NONE);

			// render -x border
			SDL_Rect borderTextRectMinusX = {
				textRect.x - textBorderSize,
				textRect.y,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectMinusX, fontRotation, nullptr, SDL_FLIP_NONE);

			// render +y border
			SDL_Rect borderTextRectPlusY = {
				textRect.x,
				textRect.y + textBorderSize,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectPlusY, fontRotation, nullptr, SDL_FLIP_NONE);

			// render -y border
			SDL_Rect borderTextRectMinusY = {
				textRect.x,
				textRect.y - textBorderSize,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectMinusY, fontRotation, nullptr, SDL_FLIP_NONE);

			//	render +x+y border
			SDL_Rect borderTextRectPlusXY = {
			textRect.x + textBorderSize,
			textRect.y + textBorderSize,
			textWidth,
			textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectPlusXY, fontRotation, nullptr, SDL_FLIP_NONE);

			//	render -x-y border
			SDL_Rect borderTextRectMinuxXY = {
			textRect.x - textBorderSize,
			textRect.y - textBorderSize,
			textWidth,
			textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectMinuxXY, fontRotation, nullptr, SDL_FLIP_NONE);

			// render +x-y border
			SDL_Rect borderTextRectPlusYX = {
				textRect.x + textBorderSize,
				textRect.y - textBorderSize,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectPlusYX, fontRotation, nullptr, SDL_FLIP_NONE);

			// render -x+y border
			SDL_Rect borderTextRectMinusYX = {
				textRect.x - textBorderSize,
				textRect.y + textBorderSize,
				textWidth,
				textHeight
			};
			SDL_RenderCopyEx(renderer_, borderTextTexture, nullptr, &borderTextRectMinusYX, fontRotation, nullptr, SDL_FLIP_NONE);

			//	clean up
			SDL_FreeSurface(borderTextSurface);
			SDL_DestroyTexture(borderTextTexture);
		}
#pragma endregion


		SDL_RenderCopyEx(renderer_, buttonTextTexture, nullptr, &textRect, fontRotation, nullptr, SDL_FLIP_NONE);
		return true;
	}
#pragma endregion
#pragma endregion
#pragma region aesthetics
	bool Button::isMouseOver(int mouseX_, int mouseY_) const {
		return mouseX_ >= rect.x && mouseX_ <= (rect.x + rect.w) &&
			mouseY_ >= rect.y && mouseY_ <= (rect.y + rect.h);
	}


	void Button::centerPosition(const int screenWidth_, const int screenHeight_) {
		rect.x = (screenWidth_ - rect.w) / 2;
		rect.y = (screenHeight_ - rect.h) / 2;
	}

	bool Button::SetBackgroundImage(const char* fileDirectory_, SDL_Renderer* renderer_) {
		//	loading the image as a texture
		SDL_Surface* imageSurface = IMG_Load(fileDirectory_);
		if (!imageSurface) return false;

		//	freeing up previous textures if they exist (if a button changes background types during an active scene, this is useful)
		if (backgroundImageTexture) { SDL_DestroyTexture(backgroundImageTexture); }

		backgroundImageTexture = SDL_CreateTextureFromSurface(renderer_, imageSurface);
		SDL_FreeSurface(imageSurface); //	its no longer needed, so let it go

		return true;
	}


	void Button::setPosition(const float newRectY_, const float newRectX_) {
		rect.x = newRectX_;
		rect.y = newRectY_;
	}

	void Button::setPositionRelativeTo(const Button& papaButton_, const float yOffset_, const float xOffset_) {
		const float newY = papaButton_.getY() + yOffset_;
		const float newX = papaButton_.getX() + xOffset_;

		setPosition(newY, newX);
	}


	void Button::offsetPosition(const int newRectYOffset_, const int newRectXOffset_) {
		rect.x += newRectXOffset_;
		rect.y += newRectYOffset_;
	}


	void Button::setDimensions(const int newRectHeight_, const int newRectWidth_) {
		rect.w = newRectWidth_;
		rect.h = newRectHeight_;
	}


	void Button::setDimensions(const SDL_Rect& rect_) {
		rect.w = rect_.w;
		rect.h = rect_.h;
		rect.x = rect_.x;
		rect.y = rect_.y;
	}


	void Button::scaleDimensionsIndividually(const int newRectHeightScaler_, const int newRectWidthScaler_) {
		rect.h = rect.h * newRectHeightScaler_;
		rect.w = rect.w * newRectWidthScaler_;
	}


	void Button::scaleDimensions(const int scaler_) {
		rect.w = rect.w * scaler_;
		rect.h = rect.h * scaler_;
	}
#pragma endregion
}

//  Constants
namespace ui {
	template <typename  T>
	T Clamp(const T value_, const T min_, const T max_) {
		if (value_ < min_) {
			return static_cast<T>(min_);
		}
		if (value_ < max_) {
			return static_cast<T>(max_);
		}
		return static_cast<T>(value_);
	}


	SDL_Color operator+(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		SDL_Color result;

		result.r = static_cast<uint8_t>(Clamp(colourA_.r + colourB_.r, 0, 255));
		result.g = static_cast<uint8_t>(Clamp(colourA_.g + colourB_.g, 0, 255));
		result.b = static_cast<uint8_t>(Clamp(colourA_.b + colourB_.b, 0, 255));
		result.a = static_cast<uint8_t>(Clamp(colourA_.a + colourB_.a, 0, 255));

		return result;
	}


	SDL_Color operator-(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		SDL_Color result;

		result.r = static_cast<uint8_t>(Clamp(colourA_.r - colourB_.r, 0, 255));
		result.g = static_cast<uint8_t>(Clamp(colourA_.g - colourB_.g, 0, 255));
		result.b = static_cast<uint8_t>(Clamp(colourA_.b - colourB_.b, 0, 255));
		result.a = static_cast<uint8_t>(Clamp(colourA_.a - colourB_.a, 0, 255));

		return result;
	}


	SDL_Color operator*(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		SDL_Color result;

		result.r = (colourA_.r * colourB_.r) / 255;
		result.g = (colourA_.g * colourB_.g) / 255;
		result.b = (colourA_.b * colourB_.b) / 255;
		result.a = (colourA_.a * colourB_.a) / 255;

		return result;
	}


	SDL_Color operator/(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		SDL_Color result;

		result.r = (colourA_.r / 2 + colourB_.r / 2) < 255 ? (colourA_.r / 2 + colourB_.r / 2) : 255;
		result.g = (colourA_.g / 2 + colourB_.g / 2) < 255 ? (colourA_.g / 2 + colourB_.g / 2) : 255;
		result.b = (colourA_.b / 2 + colourB_.b / 2) < 255 ? (colourA_.b / 2 + colourB_.b / 2) : 255;
		result.a = (colourA_.a / 2 + colourB_.a / 2) < 255 ? (colourA_.a / 2 + colourB_.a / 2) : 255;

		return result;
	}


	SDL_Color operator!(const SDL_Color& colour_) {
		SDL_Color contrastingColor;

		contrastingColor.r = 255 - colour_.r;
		contrastingColor.g = 255 - colour_.g;
		contrastingColor.b = 255 - colour_.b;
		contrastingColor.a = colour_.a;

		return contrastingColor;
	}


	SDL_Color operator~(const SDL_Color& colour_) {
		///chatgpt helped here (random devices)
		std::random_device randDev;
		std::mt19937 randGen(randDev());
		std::uniform_int_distribution<int> dis(0, 255);

		return {
			static_cast<Uint8>(colour_.r + dis(randGen) % 256),
			static_cast<Uint8>(colour_.g + dis(randGen) % 256),
			static_cast<Uint8>(colour_.b + dis(randGen) % 256),
			colour_.a
		};
	}


	SDL_Color operator<<(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		return { colourA_.r, colourA_.g, colourA_.b, colourB_.a };
	}
#pragma region shapes
	SDL_Rect SDL_Testangle = { 0, 0, 425, 75 };
	SDL_Rect SDL_Rectangle = { 0, 0, 3, 1 };
	SDL_Rect SDL_Wide_Rectangle = { 0, 0, 6, 1 };
	SDL_Rect SDL_Tall_Rectangle = { 0, 0, 1, 3 };
	SDL_Rect SDL_Square = { 0, 0, 2, 2 };
#pragma endregion
	//273 preset colour variables - fri 6 2023
#pragma region pride
#pragma region transparency
	SDL_Color SDL_White100 = { 255, 255, 255, 255 };
	SDL_Color SDL_White90 = { 255, 255, 255, 230 };
	SDL_Color SDL_White75 = { 255, 255, 255, 191 };
	SDL_Color SDL_White50 = { 255, 255, 255, 128 };
	SDL_Color SDL_White25 = { 255, 255, 255, 64 };
	SDL_Color SDL_White10 = { 255, 255, 255, 26 };
#pragma endregion
#pragma region colours
	SDL_Color SDL_COLOR_NULL = { 0,0,0,0 };
	SDL_Color SDL_COLOR_ALICE_BLUE = { 240, 248, 255, 255 };
	SDL_Color SDL_COLOR_ANTIQUE_WHITE = { 250, 235, 215, 255 };
	SDL_Color SDL_COLOR_AQUA = { 0, 255, 255, 255 };
	SDL_Color SDL_COLOR_AQUAMARINE = { 127, 255, 212, 255 };
	SDL_Color SDL_COLOR_AZURE = { 240, 255, 255, 255 };
	SDL_Color SDL_COLOR_BEIGE = { 245, 245, 220, 255 };
	SDL_Color SDL_COLOR_BISQUE = { 255, 228, 196, 255 };
	SDL_Color SDL_COLOR_BLACK = { 0, 0, 0, 255 };
	SDL_Color SDL_COLOR_BLANCHED_ALMOND = { 255, 235, 205, 255 };
	SDL_Color SDL_COLOR_BLUE = { 0, 0, 255, 255 };
	SDL_Color SDL_COLOR_BLUE_VIOLET = { 138, 43, 226, 255 };
	SDL_Color SDL_COLOR_BROWN = { 165, 42, 42, 255 };
	SDL_Color SDL_COLOR_BURLY_WOOD = { 222, 184, 135, 255 };
	SDL_Color SDL_COLOR_CADET_BLUE = { 95, 158, 160, 255 };
	SDL_Color SDL_COLOR_CHARTREUSE = { 127, 255, 0, 255 };
	SDL_Color SDL_COLOR_CHOCOLATE = { 210, 105, 30, 255 };
	SDL_Color SDL_COLOR_CORAL = { 255, 127, 80, 255 };
	SDL_Color SDL_COLOR_CORNFLOWER_BLUE = { 100, 149, 237, 255 };
	SDL_Color SDL_COLOR_CRIMSON = { 220, 20, 60, 255 };
	SDL_Color SDL_COLOR_CYAN = { 0, 255, 255, 255 };
	SDL_Color SDL_COLOR_DARK_BLUE = { 0, 0, 139, 255 };
	SDL_Color SDL_COLOR_DARK_CYAN = { 0, 139, 139, 255 };
	SDL_Color SDL_COLOR_DARK_GOLDENROD = { 184, 134, 11, 255 };
	SDL_Color SDL_COLOR_DARK_GRAY = { 169, 169, 169, 255 };
	SDL_Color SDL_COLOR_DARK_GREEN = { 0, 100, 0, 255 };
	SDL_Color SDL_COLOR_DARK_KHAKI = { 189, 183, 107, 255 };
	SDL_Color SDL_COLOR_DARK_MAGENTA = { 139, 0, 139, 255 };
	SDL_Color SDL_COLOR_DARK_OLIVE_GREEN = { 85, 107, 47, 255 };
	SDL_Color SDL_COLOR_DARK_ORANGE = { 255, 140, 0, 255 };
	SDL_Color SDL_COLOR_DARK_RED = { 139, 0, 0, 255 };
	SDL_Color SDL_COLOR_DARK_SALMON = { 233, 150, 122, 255 };
	SDL_Color SDL_COLOR_DARK_SEA_GREEN = { 143, 188, 139, 255 };
	SDL_Color SDL_COLOR_DARK_SLATE_BLUE = { 72, 61, 139, 255 };
	SDL_Color SDL_COLOR_DARK_SLATE_GRAY = { 47, 79, 79, 255 };
	SDL_Color SDL_COLOR_DARK_TURQUOISE = { 0, 206, 209, 255 };
	SDL_Color SDL_COLOR_DARK_VIOLET = { 148, 0, 211, 255 };
	SDL_Color SDL_COLOR_DEEP_PINK = { 255, 20, 147, 255 };
	SDL_Color SDL_COLOR_DEEP_SKY_BLUE = { 0, 191, 255, 255 };
	SDL_Color SDL_COLOR_DIM_GRAY = { 105, 105, 105, 255 };
	SDL_Color SDL_COLOR_DODGER_BLUE = { 30, 144, 255, 255 };
	SDL_Color SDL_COLOR_FIREBRICK = { 178, 34, 34, 255 };
	SDL_Color SDL_COLOR_FLORAL_WHITE = { 255, 250, 240, 255 };
	SDL_Color SDL_COLOR_FOREST_GREEN = { 34, 139, 34, 255 };
	SDL_Color SDL_COLOR_FUCHSIA = { 255, 0, 255, 255 };
	SDL_Color SDL_COLOR_GAINSBORO = { 220, 220, 220, 255 };
	SDL_Color SDL_COLOR_GHOST_WHITE = { 248, 248, 255, 255 };
	SDL_Color SDL_COLOR_GOLD = { 255, 215, 0, 255 };
	SDL_Color SDL_COLOR_GOLDENROD = { 218, 165, 32, 255 };
	SDL_Color SDL_COLOR_GRAY = { 128, 128, 128, 255 };
	SDL_Color SDL_COLOR_GREEN = { 0, 128, 0, 255 };
	SDL_Color SDL_COLOR_GREEN_YELLOW = { 173, 255, 47, 255 };
	SDL_Color SDL_COLOR_HONEYDEW = { 240, 255, 240, 255 };
	SDL_Color SDL_COLOR_INDIGO = { 75, 0, 130, 255 };
	SDL_Color SDL_COLOR_IVORY = { 255, 255, 240, 255 };
	SDL_Color SDL_COLOR_KHAKI = { 240, 230, 140, 255 };
	SDL_Color SDL_COLOR_LAVENDER = { 230, 230, 250, 255 };
	SDL_Color SDL_COLOR_LAVENDER_BLUSH = { 255, 240, 245, 255 };
	SDL_Color SDL_COLOR_LEMON_CHIFFON = { 255, 250, 205, 255 };
	SDL_Color SDL_COLOR_LIGHT_BLUE = { 173, 216, 230, 255 };
	SDL_Color SDL_COLOR_LIGHT_CORAL = { 240, 128, 128, 255 };
	SDL_Color SDL_COLOR_LIGHT_CYAN = { 224, 255, 255, 255 };
	SDL_Color SDL_COLOR_LIGHT_GOLDENROD_YELLOW = { 250, 250, 210, 255 };
	SDL_Color SDL_COLOR_LIGHT_GREEN = { 144, 238, 144, 255 };
	SDL_Color SDL_COLOR_LIGHT_GRAY = { 211, 211, 211, 255 };
	SDL_Color SDL_COLOR_LIGHT_PINK = { 255, 182, 193, 255 };
	SDL_Color SDL_COLOR_LIGHT_SALMON = { 255, 160, 122, 255 };
	SDL_Color SDL_COLOR_LIGHT_SEA_GREEN = { 32, 178, 170, 255 };
	SDL_Color SDL_COLOR_LIGHT_SKY_BLUE = { 135, 206, 250, 255 };
	SDL_Color SDL_COLOR_LIGHT_SLATE_GRAY = { 119, 136, 153, 255 };
	SDL_Color SDL_COLOR_LIGHT_STEEL_BLUE = { 176, 196, 222, 255 };
	SDL_Color SDL_COLOR_LIGHT_YELLOW = { 255, 255, 224, 255 };
	SDL_Color SDL_COLOR_LIME = { 0, 255, 0, 255 };
	SDL_Color SDL_COLOR_LIME_GREEN = { 50, 205, 50, 255 };
	SDL_Color SDL_COLOR_LINEN = { 250, 240, 230, 255 };
	SDL_Color SDL_COLOR_MAGENTA = { 255, 0, 255, 255 };
	SDL_Color SDL_COLOR_MAROON = { 128, 0, 0, 255 };
	SDL_Color SDL_COLOR_MEDIUM_AQUAMARINE = { 102, 205, 170, 255 };
	SDL_Color SDL_COLOR_MEDIUM_BLUE = { 0, 0, 205, 255 };
	SDL_Color SDL_COLOR_MEDIUM_ORCHID = { 186, 85, 211, 255 };
	SDL_Color SDL_COLOR_MEDIUM_PURPLE = { 147, 112, 219, 255 };
	SDL_Color SDL_COLOR_MEDIUM_SEA_GREEN = { 60, 179, 113, 255 };
	SDL_Color SDL_COLOR_MEDIUM_SLATE_BLUE = { 123, 104, 238, 255 };
	SDL_Color SDL_COLOR_MEDIUM_SPRING_GREEN = { 0, 250, 154, 255 };
	SDL_Color SDL_COLOR_MEDIUM_TURQUOISE = { 72, 209, 204, 255 };
	SDL_Color SDL_COLOR_MEDIUM_VIOLET_RED = { 199, 21, 133, 255 };
	SDL_Color SDL_COLOR_MIDNIGHT_BLUE = { 25, 25, 112, 255 };
	SDL_Color SDL_COLOR_MINT_CREAM = { 245, 255, 250, 255 };
	SDL_Color SDL_COLOR_MISTY_ROSE = { 255, 228, 225, 255 };
	SDL_Color SDL_COLOR_MOCCASIN = { 255, 228, 181, 255 };
	SDL_Color SDL_COLOR_NAVY = { 0, 0, 128, 255 };
	SDL_Color SDL_COLOR_OLD_LACE = { 253, 245, 230, 255 };
	SDL_Color SDL_COLOR_OLIVE = { 128, 128, 0, 255 };
	SDL_Color SDL_COLOR_OLIVE_DRAB = { 107, 142, 35, 255 };
	SDL_Color SDL_COLOR_ORANGE = { 255, 165, 0, 255 };
	SDL_Color SDL_COLOR_ORANGE_RED = { 255, 69, 0, 255 };
	SDL_Color SDL_COLOR_ORCHID = { 218, 112, 214, 255 };
	SDL_Color SDL_COLOR_PALE_GOLDENROD = { 238, 232, 170, 255 };
	SDL_Color SDL_COLOR_PALE_GREEN = { 152, 251, 152, 255 };
	SDL_Color SDL_COLOR_PALE_TURQUOISE = { 175, 238, 238, 255 };
	SDL_Color SDL_COLOR_PALE_VIOLET_RED = { 219, 112, 147, 255 };
	SDL_Color SDL_COLOR_PAPAYA_WHIP = { 255, 239, 213, 255 };
	SDL_Color SDL_COLOR_PEACH_PUFF = { 255, 218, 185, 255 };
	SDL_Color SDL_COLOR_PERU = { 205, 133, 63, 255 };
	SDL_Color SDL_COLOR_PINK = { 255, 192, 203, 255 };
	SDL_Color SDL_COLOR_PLUM = { 221, 160, 221, 255 };
	SDL_Color SDL_COLOR_POWDER_BLUE = { 176, 224, 230, 255 };
	SDL_Color SDL_COLOR_PURPLE = { 128, 0, 128, 255 };
	SDL_Color SDL_COLOR_RED = { 255, 0, 0, 255 };
	SDL_Color SDL_COLOR_ROSY_BROWN = { 188, 143, 143, 255 };
	SDL_Color SDL_COLOR_ROYAL_BLUE = { 65, 105, 225, 255 };
	SDL_Color SDL_COLOR_SADDLE_BROWN = { 139, 69, 19, 255 };
	SDL_Color SDL_COLOR_SALMON = { 250, 128, 114, 255 };
	SDL_Color SDL_COLOR_SANDY_BROWN = { 244, 164, 96, 255 };
	SDL_Color SDL_COLOR_SEA_GREEN = { 46, 139, 87, 255 };
	SDL_Color SDL_COLOR_SEASHELL = { 255, 245, 238, 255 };
	SDL_Color SDL_COLOR_SIENNA = { 160, 82, 45, 255 };
	SDL_Color SDL_COLOR_SILVER = { 192, 192, 192, 255 };
	SDL_Color SDL_COLOR_SKY_BLUE = { 135, 206, 235, 255 };
	SDL_Color SDL_COLOR_SLATE_BLUE = { 106, 90, 205, 255 };
	SDL_Color SDL_COLOR_SLATE_GRAY = { 112, 128, 144, 255 };
	SDL_Color SDL_COLOR_SNOW = { 255, 250, 250, 255 };
	SDL_Color SDL_COLOR_SPRING_GREEN = { 0, 255, 127, 255 };
	SDL_Color SDL_COLOR_STEEL_BLUE = { 70, 130, 180, 255 };
	SDL_Color SDL_COLOR_TAN = { 210, 180, 140, 255 };
	SDL_Color SDL_COLOR_TEAL = { 0, 128, 128, 255 };
	SDL_Color SDL_COLOR_THISTLE = { 216, 191, 216, 255 };
	SDL_Color SDL_COLOR_TOMATO = { 255, 99, 71, 255 };
	SDL_Color SDL_COLOR_TURQUOISE = { 64, 224, 208, 255 };
	SDL_Color SDL_COLOR_VIOLET = { 238, 130, 238, 255 };
	SDL_Color SDL_COLOR_WHEAT = { 245, 222, 179, 255 };
	SDL_Color SDL_COLOR_WHITE = { 255, 255, 255, 255 };
	SDL_Color SDL_COLOR_YELLOW = { 255, 255, 0, 255 };
	SDL_Color SDL_COLOR_YELLOW_GREEN = { 154, 205, 50, 255 };
	SDL_Color SDL_COLOR_AMETHYST = { 155, 89, 182, 255 };
	SDL_Color SDL_COLOR_APPLE_GREEN = { 141, 182, 0, 255 };
	SDL_Color SDL_COLOR_APRICOT = { 255, 177, 109, 255 };
	SDL_Color SDL_COLOR_AZURE_MIST = { 240, 255, 255, 255 };
	SDL_Color SDL_COLOR_BALL_BLUE = { 33, 171, 205, 255 };
	SDL_Color SDL_COLOR_BANANA_YELLOW = { 255, 225, 53, 255 };
	SDL_Color SDL_COLOR_BATTLESHIP_GREY = { 132, 132, 130, 255 };
	SDL_Color SDL_COLOR_BUBBLES = { 231, 254, 255, 255 };
	SDL_Color SDL_COLOR_BUBBLEGUM = { 255, 105, 180, 255 };
	SDL_Color SDL_COLOR_BURNT_ORANGE = { 204, 85, 0, 255 };
	SDL_Color SDL_COLOR_CAMEL = { 193, 154, 107, 255 };
	SDL_Color SDL_COLOR_CANDY_PINK = { 255, 99, 147, 255 };
	SDL_Color SDL_COLOR_CHARCOAL = { 54, 69, 79, 255 };
	SDL_Color SDL_COLOR_CHERRY = { 222, 49, 99, 255 };
	SDL_Color SDL_COLOR_CITRINE = { 147, 168, 0, 255 };
	SDL_Color SDL_COLOR_COBALT_BLUE = { 0, 71, 171, 255 };
	SDL_Color SDL_COLOR_COCOA_BROWN = { 210, 105, 30, 255 };
	SDL_Color SDL_COLOR_CORN = { 251, 236, 93, 255 };
	SDL_Color SDL_COLOR_CRIMSON_RED = { 220, 20, 60, 255 };
	SDL_Color SDL_COLOR_CREAM = { 255, 253, 208, 255 };
	SDL_Color SDL_COLOR_DARK_LAVENDER = { 115, 79, 150, 255 };
	SDL_Color SDL_COLOR_DEEP_LILAC = { 153, 85, 187, 255 };
	SDL_Color SDL_COLOR_DUSK_PINK = { 204, 122, 139, 255 };
	SDL_Color SDL_COLOR_EGGPLANT_PURPLE = { 97, 64, 81, 255 };
	SDL_Color SDL_COLOR_EMERALD_GREEN = { 46, 139, 87, 255 };
	SDL_Color SDL_COLOR_FAWN = { 229, 170, 112, 255 };
	SDL_Color SDL_COLOR_FOREST_BROWN = { 139, 105, 20, 255 };
	SDL_Color SDL_COLOR_FROST = { 240, 255, 255, 255 };
	SDL_Color SDL_COLOR_FUCHSIA_PINK = { 255, 0, 128, 255 };
	SDL_Color SDL_COLOR_GOLDEN_YELLOW = { 255, 223, 0, 255 };
	SDL_Color SDL_COLOR_GRAPE_PURPLE = { 68, 27, 81, 255 };
	SDL_Color SDL_COLOR_HEATHER_GREY = { 183, 164, 162, 255 };
	SDL_Color SDL_COLOR_HONEY_BROWN = { 177, 114, 21, 255 };
	SDL_Color SDL_COLOR_HOT_PINK = { 255, 0, 102, 255 };
	SDL_Color SDL_COLOR_INDIGO_BLUE = { 24, 50, 115, 255 };
	SDL_Color SDL_COLOR_JADE_GREEN = { 0, 168, 107, 255 };
	SDL_Color SDL_COLOR_LAVENDER_PURPLE = { 180, 164, 217, 255 };
	SDL_Color SDL_COLOR_LEMONADE = { 248, 232, 104, 255 };
	SDL_Color SDL_COLOR_LIGHT_BRONZE = { 205, 127, 50, 255 };
	SDL_Color SDL_COLOR_LIGHT_JASMINE = { 248, 222, 126, 255 };
	SDL_Color SDL_COLOR_MAIZE_YELLOW = { 251, 236, 93, 255 };
	SDL_Color SDL_COLOR_MANGO = { 255, 130, 67, 255 };
	SDL_Color SDL_COLOR_MARIGOLD = { 255, 194, 14, 255 };
	SDL_Color SDL_COLOR_MAUVE = { 224, 176, 255, 255 };
	SDL_Color SDL_COLOR_MIDNIGHT_PURPLE = { 40, 30, 55, 255 };
	SDL_Color SDL_COLOR_MOSS_GREEN = { 138, 154, 91, 255 };
	SDL_Color SDL_COLOR_MULBERRY = { 197, 75, 140, 255 };
	SDL_Color SDL_COLOR_MUSTARD_YELLOW = { 255, 173, 1, 255 };
	SDL_Color SDL_COLOR_NIGHT_BLUE = { 0, 0, 102, 255 };
	SDL_Color SDL_COLOR_OCEAN_BLUE = { 0, 56, 168, 255 };
	SDL_Color SDL_COLOR_ORANGE_PEEL = { 255, 159, 0, 255 };
	SDL_Color SDL_COLOR_PALE_LAVENDER = { 220, 208, 255, 255 };
	SDL_Color SDL_COLOR_PEAR_GREEN = { 151, 186, 1, 255 };
	SDL_Color SDL_COLOR_PEACHY_PINK = { 255, 153, 102, 255 };
	SDL_Color SDL_COLOR_PERSIMMON = { 255, 77, 77, 255 };
	SDL_Color SDL_COLOR_PINE_GREEN = { 21, 128, 120, 255 };
	SDL_Color SDL_COLOR_PUMPKIN_ORANGE = { 255, 117, 24, 255 };
	SDL_Color SDL_COLOR_RASPBERRY = { 135, 38, 87, 255 };
	SDL_Color SDL_COLOR_RICH_GOLD = { 212, 175, 55, 255 };
	SDL_Color SDL_COLOR_ROBIN_EGG_BLUE = { 0, 204, 204, 255 };
	SDL_Color SDL_COLOR_RUST_BROWN = { 139, 37, 0, 255 };
	SDL_Color SDL_COLOR_SALAMANDER = { 0, 113, 115, 255 };
	SDL_Color SDL_COLOR_SAPPHIRE_BLUE = { 8, 37, 103, 255 };
	SDL_Color SDL_COLOR_SCARLET_RED = { 255, 36, 0, 255 };
	SDL_Color SDL_COLOR_SEAFOAM_GREEN = { 120, 212, 168, 255 };
	SDL_Color SDL_COLOR_SILVER_GREY = { 192, 192, 192, 255 };
	SDL_Color SDL_COLOR_SKY_GREY = { 128, 128, 128, 255 };
	SDL_Color SDL_COLOR_SPRUCE = { 0, 128, 128, 255 };
	SDL_Color SDL_COLOR_STORMY_GREY = { 112, 128, 144, 255 };
	SDL_Color SDL_COLOR_SUNFLOWER_YELLOW = { 255, 212, 0, 255 };
	SDL_Color SDL_COLOR_TANGERINE = { 255, 148, 77, 255 };
	SDL_Color SDL_COLOR_TERRACOTTA = { 204, 78, 92, 255 };
	SDL_Color SDL_COLOR_TITANIUM = { 135, 134, 129, 255 };
	SDL_Color SDL_COLOR_TOMATO_RED = { 255, 99, 71, 255 };
	SDL_Color SDL_COLOR_TULIP_PINK = { 255, 135, 148, 255 };
	SDL_Color SDL_COLOR_TURQUOISE_BLUE = { 0, 199, 140, 255 };
	SDL_Color SDL_COLOR_TWILIGHT_BLUE = { 78, 81, 128, 255 };
	SDL_Color SDL_COLOR_VERMILLION = { 227, 66, 52, 255 };
	SDL_Color SDL_COLOR_VIOLET_RED = { 208, 32, 144, 255 };
	SDL_Color SDL_COLOR_WARM_STREAM = { 255, 219, 88, 255 };
	SDL_Color SDL_COLOR_COOL_STREAM = { 204, 204, 0, 255 };
	SDL_Color SDL_COLOR_AMBER_STREAM = { 255, 140, 0, 255 };
	SDL_Color SDL_COLOR_GOLDEN_STREAM = { 255, 215, 0, 255 };
	SDL_Color SDL_COLOR_WINTER_GREY = { 153, 153, 153, 255 };
	SDL_Color SDL_COLOR_XANADU = { 115, 134, 120, 255 };
	SDL_Color SDL_COLOR_ZAFFRE = { 0, 20, 168, 255 };
	SDL_Color SDL_COLOR_ZINNWALDITE = { 44, 53, 57, 255 };
	SDL_Color SDL_COLOR_ZUCCHINI = { 33, 66, 12, 255 };
	SDL_Color SDL_COLOR_LAWN_GREEN = { 124, 252, 0, 255 };
	SDL_Color SDL_COLOR_PINEAPPLE_YELLOW = { 255, 223, 0, 255 };
	SDL_Color SDL_COLOR_BOOGER_GREEN = { 168, 226, 9, 255 };
	SDL_Color SDL_COLOR_MARINE_BLUE = { 0, 41, 98, 255 };
	SDL_Color SDL_COLOR_PEACH = { 255, 218, 185, 255 };
	SDL_Color SDL_COLOR_STARRY_NIGHT = { 25, 25, 112, 255 };
	SDL_Color SDL_COLOR_EMERALD = { 46, 204, 113, 255 };
	SDL_Color SDL_COLOR_COTTON_CANDY = { 255, 188, 217, 255 };
	SDL_Color SDL_COLOR_OCEAN = { 0, 105, 148, 255 };
	SDL_Color SDL_COLOR_GOLDEN_SUNSET = { 253, 94, 83, 255 };
	SDL_Color SDL_COLOR_RUBY_RED = { 206, 17, 38, 255 };
	SDL_Color SDL_COLOR_MIDNIGHT_SKY = { 0, 3, 61, 255 };
	SDL_Color SDL_COLOR_LUSH_GREEN = { 0, 128, 64, 255 };
	SDL_Color SDL_COLOR_TROPICAL_ORANGE = { 255, 128, 0, 255 };
	SDL_Color SDL_COLOR_SILVER_MIST = { 214, 219, 223, 255 };
	SDL_Color SDL_COLOR_MYSTIC_PURPLE = { 128, 0, 128, 255 };
	SDL_Color SDL_COLOR_TEAL_BLUE = { 0, 128, 128, 255 };
	SDL_Color SDL_COLOR_POOPSTAIN = { 139, 69, 19, 255 };
#pragma endregion
#pragma region appliances dlc
	SDL_Color SDL_COLOR_MUG = { 139, 69, 19, 255 };
	SDL_Color SDL_COLOR_TOASTER = { 255, 140, 0, 255 };
	SDL_Color SDL_COLOR_SOFA = { 255, 228, 181, 255 };
	SDL_Color SDL_COLOR_BOOKSHELF = { 139, 69, 19, 255 };
	SDL_Color SDL_COLOR_TELEVISION = { 0, 0, 128, 255 };
	SDL_Color SDL_COLOR_PLANT_POT = { 0, 128, 0, 255 };
	SDL_Color SDL_COLOR_LAMP = { 255, 255, 0, 255 };
	SDL_Color SDL_COLOR_COMPUTER = { 0, 102, 204, 255 };
	SDL_Color SDL_COLOR_BED = { 128, 0, 0, 255 };
	SDL_Color SDL_COLOR_WARDROBE = { 128, 0, 128, 255 };
	SDL_Color SDL_COLOR_CHAIR = { 255, 0, 0, 255 };
	SDL_Color SDL_COLOR_FRIDGE = { 173, 216, 230, 255 };
	SDL_Color SDL_COLOR_OVEN = { 210, 105, 30, 255 };
	SDL_Color SDL_COLOR_MICROWAVE = { 255, 223, 186, 255 };
	SDL_Color SDL_COLOR_CUTLERY = { 192, 192, 192, 255 };
	SDL_Color SDL_COLOR_PLATE = { 255, 255, 0, 255 };
	SDL_Color SDL_COLOR_CANDLE = { 255, 0, 0, 255 };
	SDL_Color SDL_COLOR_VASE = { 0, 128, 128, 255 };
	SDL_Color SDL_COLOR_BLINDS = { 255, 255, 224, 255 };
	SDL_Color SDL_COLOR_CARPET = { 128, 0, 0, 255 };
	SDL_Color SDL_COLOR_SHOES = { 0, 0, 0, 255 };
	SDL_Color SDL_COLOR_FRAME = { 255, 215, 0, 255 };
	SDL_Color SDL_COLOR_RADIO = { 255, 99, 71, 255 };
	SDL_Color SDL_COLOR_HEADPHONES = { 0, 0, 128, 255 };
	SDL_Color SDL_COLOR_BRUSH = { 160, 82, 45, 255 };
	SDL_Color SDL_COLOR_HAIR_DRYER = { 255, 105, 180, 255 };
	SDL_Color SDL_COLOR_TOOTHBRUSH = { 0, 255, 0, 255 };
	SDL_Color SDL_COLOR_WASHING_MACHINE = { 173, 216, 230, 255 };
#pragma endregion
#pragma region minecraft blocks dlc
	SDL_Color SDL_COLOR_ANVIL = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_BARREL = { 107, 67, 35, 255 };
	SDL_Color SDL_COLOR_BAMBOO = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_BEDROCK = { 68, 68, 68, 255 };
	SDL_Color SDL_COLOR_BEEHIVE = { 170, 85, 0, 255 };
	SDL_Color SDL_COLOR_BEE_NEST = { 170, 85, 0, 255 };
	SDL_Color SDL_COLOR_BELL = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_BLAST_FURNACE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_CAMPFIRE = { 170, 85, 0, 255 };
	SDL_Color SDL_COLOR_CHEST = { 127, 89, 62, 255 };
	SDL_Color SDL_COLOR_COAL_ORE = { 35, 35, 35, 255 };
	SDL_Color SDL_COLOR_COBBLESTONE = { 105, 105, 105, 255 };
	SDL_Color SDL_COLOR_COMPOSTER = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_CRAFTING_TABLE = { 170, 85, 0, 255 };
	SDL_Color SDL_COLOR_DIRT = { 134, 96, 67, 255 };
	SDL_Color SDL_COLOR_DISPENSER = { 80, 80, 80, 255 };
	SDL_Color SDL_COLOR_ENCHANTING_TABLE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_END_PORTAL_FRAME = { 38, 23, 34, 255 };
	SDL_Color SDL_COLOR_FLETCHING_TABLE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_FURNACE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_GOLD_ORE = { 229, 188, 0, 255 };
	SDL_Color SDL_COLOR_GLASS = { 186, 210, 214, 128 };
	SDL_Color SDL_COLOR_GRAVEL = { 136, 126, 126, 255 };
	SDL_Color SDL_COLOR_GRASS_BLOCK = { 96, 128, 24, 255 };
	SDL_Color SDL_COLOR_GRASS_PATH = { 170, 191, 100, 255 };
	SDL_Color SDL_COLOR_GRINDSTONE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_IRON_ORE = { 136, 136, 136, 255 };
	SDL_Color SDL_COLOR_ICE = { 125, 202, 239, 128 };
	SDL_Color SDL_COLOR_JUKEBOX = { 85, 45, 45, 255 };
	SDL_Color SDL_COLOR_LADDER = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_LAPIS_LAZULI_ORE = { 37, 79, 161, 255 };
	SDL_Color SDL_COLOR_LAVA = { 255, 50, 0, 255 };
	SDL_Color SDL_COLOR_LILAC = { 194, 117, 194, 255 };
	SDL_Color SDL_COLOR_LOOM = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_NOTEBLOCK = { 166, 113, 60, 255 };
	SDL_Color SDL_COLOR_OAK_LEAVES = { 81, 179, 80, 255 };
	SDL_Color SDL_COLOR_OAK_LOG = { 85, 64, 14, 255 };
	SDL_Color SDL_COLOR_OBSIDIAN = { 8, 0, 29, 255 };
	SDL_Color SDL_COLOR_PACKED_ICE = { 148, 203, 234, 255 };
	SDL_Color SDL_COLOR_PEONY = { 238, 149, 167, 255 };
	SDL_Color SDL_COLOR_RED_TULIP = { 245, 63, 47, 255 };
	SDL_Color SDL_COLOR_ROSE_BUSH = { 255, 0, 0, 255 };
	SDL_Color SDL_COLOR_SAND = { 219, 190, 116, 255 };
	SDL_Color SDL_COLOR_SANDSTONE = { 218, 211, 169, 255 };
	SDL_Color SDL_COLOR_SCAFFOLDING = { 85, 85, 85, 128 };
	SDL_Color SDL_COLOR_SEAGRASS = { 48, 171, 0, 128 };
	SDL_Color SDL_COLOR_SMITHING_TABLE = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_SOUL_CAMPFIRE = { 85, 0, 170, 255 };
	SDL_Color SDL_COLOR_STONE = { 125, 125, 125, 255 };
	SDL_Color SDL_COLOR_STONECUTTER = { 85, 85, 85, 255 };
	SDL_Color SDL_COLOR_TALL_GRASS = { 170, 191, 100, 255 };
	SDL_Color SDL_COLOR_TALL_SEAGRASS = { 48, 171, 0, 255 };
	SDL_Color SDL_COLOR_TORCH = { 255, 236, 85, 255 };
	SDL_Color SDL_COLOR_WATER = { 40, 40, 170, 255 };
	SDL_Color SDL_COLOR_WET_SPONGE = { 133, 133, 133, 255 };
#pragma endregion
#pragma region overwat dlc
	// Tank Heroes
	SDL_Color SDL_COLOR_DVA = { 255, 0, 255, 255 }; // D.Va (Magenta)
	SDL_Color SDL_COLOR_DOOMFIST = { 128, 64, 0, 255 }; // Doomfist (Brown)
	SDL_Color SDL_COLOR_JUNKER_QUEEN = { 255, 128, 0, 255 }; // Junker Queen (Orange)
	SDL_Color SDL_COLOR_ORISA = { 0, 255, 0, 255 }; // Orisa (Green)
	SDL_Color SDL_COLOR_RAMATTRA = { 128, 0, 128, 255 }; // Ramattra (Purple)
	SDL_Color SDL_COLOR_REINHARDT = { 77, 85, 86, 255 }; // Reinhardt
	SDL_Color SDL_COLOR_ROADHOG = { 128, 64, 64, 255 }; // Roadhog (Dark Red)
	SDL_Color SDL_COLOR_SIGMA = { 128, 128, 128, 255 }; // Sigma (Gray)
	SDL_Color SDL_COLOR_WINSTON = { 0, 0, 255, 255 }; // Winston (Blue)
	SDL_Color SDL_COLOR_WRECKING_BALL = { 255, 192, 0, 255 }; // Wrecking Ball (Gold)
	SDL_Color SDL_COLOR_ZARYA = { 255, 192, 192, 255 }; // Zarya (Light Pink)

	// Damage Heroes
	SDL_Color SDL_COLOR_ASHE = { 192, 192, 192, 255 }; // Ashe (Silver)
	SDL_Color SDL_COLOR_BASTION = { 0, 128, 0, 255 }; // Bastion (Dark Green)
	SDL_Color SDL_COLOR_CASSIDY = { 192, 64, 0, 255 }; // Cassidy (Rust)
	SDL_Color SDL_COLOR_ECHO = { 0, 192, 192, 255 }; // Echo (Turquoise)
	SDL_Color SDL_COLOR_GENJI = { 0, 192, 0, 255 }; // Genji (Lime)
	SDL_Color SDL_COLOR_HANZO = { 64, 64, 64, 255 }; // Hanzo (Black)
	SDL_Color SDL_COLOR_JUNKRAT = { 192, 192, 0, 255 }; // Junkrat (Yellow)
	SDL_Color SDL_COLOR_MEI = { 128, 128, 255, 255 }; // Mei (Light Blue)
	SDL_Color SDL_COLOR_PHARAH = { 64, 64, 192, 255 }; // Pharah (Indigo)
	SDL_Color SDL_COLOR_REAPER = { 128, 0, 0, 255 }; // Reaper (Maroon)
	SDL_Color SDL_COLOR_SOJOURN = { 128, 128, 128, 255 }; // Sojourn (Gray)
	SDL_Color SDL_COLOR_SOLDIER_76 = { 192, 192, 192, 255 }; // Soldier:76 (Silver)
	SDL_Color SDL_COLOR_SOMBRA = { 128, 0, 128, 255 }; // Sombra (Purple)
	SDL_Color SDL_COLOR_SYMMETRA = { 64, 64, 192, 255 }; // Symmetra (Indigo)
	SDL_Color SDL_COLOR_TORBJORN = { 192, 64, 0, 255 }; // Torbjörn (Rust)
	SDL_Color SDL_COLOR_TRACER = { 227, 105, 7, 255 }; // Tracer
	SDL_Color SDL_COLOR_WIDOWMAKER = { 64, 0, 128, 255 }; // Widowmaker (Violet)

	// Support Heroes
	SDL_Color SDL_COLOR_ANA = { 100, 162, 216, 255 }; // Ana 
	SDL_Color SDL_COLOR_BAPTISTE = { 42, 139, 141, 255 }; // Baptiste 
	SDL_Color SDL_COLOR_BRIGITTE = { 192, 96, 96, 255 }; // Brigitte (Salmon)
	SDL_Color SDL_COLOR_ILLARI = { 254, 225, 65, 255 }; // Illari 
	SDL_Color SDL_COLOR_KIRIKO = { 177, 58, 69, 255 }; // Kiriko
	SDL_Color SDL_COLOR_LIFEWEAVER = { 0, 192, 0, 255 }; // Lifeweaver (Lime)
	SDL_Color SDL_COLOR_LUCIO = { 119, 190, 9, 255 }; // Lúcio
	SDL_Color SDL_COLOR_MERCY = { 255, 255, 0, 255 }; // Mercy (Yellow)
	SDL_Color SDL_COLOR_MOIRA = { 128, 0, 128, 255 }; // Moira (Purple)
	SDL_Color SDL_COLOR_ZENYATTA = { 192, 192, 0, 255 }; // Zenyatta (Yellow)
#pragma endregion
#pragma region jail dlc
	SDL_Color SDL_COLOR_ROSE_TOY = { 213, 45, 78, 255 };
	SDL_Color SDL_COLOR_BAD_DRAGON = { 148, 0, 211, 255 };
#pragma endregion
#pragma endregion
}