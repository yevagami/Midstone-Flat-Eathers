#include "Menu.h"

#include "ConsistentConsole.h"
ConsistentConsole ccMenu;

namespace menu {
#pragma region pride
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
SDL_Color SDL_COLOR_DARK_SEA_GREEN = { 143, 188, 143, 255 };
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
#pragma endregion


	menu::Button::Button(SDL_Renderer* buttRenderer, int x, int y, int width, int height, bool centered)
		: renderer(buttRenderer), rect({ x, y, width, height }), isTextCentered(centered) {
		backgroundColour = SDL_COLOR_GRAY;     // Default background color
		textColour = SDL_COLOR_BLACK;              // Default text color
		borderColour = SDL_COLOR_BLACK;          // Default border color
	}


	void Button::Render(SDL_Texture* textTexture, TTF_Font* font) {
		// render the button background
		SDL_SetRenderDrawColor(renderer, backgroundColour.r, backgroundColour.g, backgroundColour.b, backgroundColour.a);
		SDL_RenderFillRect(renderer, &rect);
		//  set text colour
		SDL_Color textColour = this->textColour;

		if (textTexture && font) {
			// get the dimensions of the text texture
			int textWidth, textHeight;
			SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);


			int textX = rect.x, textY = rect.y;
			if (isTextCentered) {
				textX += (rect.w - rect.x) / 2 - rect.w / 4; // Adjust based on your text size
				textY += (rect.h - rect.y) / 2 - rect.h / 4; // Adjust based on your text size
			}

			int x = rect.x + (rect.w - textWidth) / 2;
			int y = rect.y + (rect.h - textHeight) / 2;

			SDL_Rect textRect = { x, y, textWidth, textHeight };

			SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		}

	}


	void Button::HandleEvent(SDL_Event& event) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			if (isMouseOver(event.button.x, event.button.y)) {
				if (OnClick) { ccMenu.consoleManager(safe, "button clicked");  OnClick(); }
			}

			break;

		}

	}


	bool Button::isMouseOver(int mouseX, int mouseY) {
		return mouseX >= rect.x && mouseX <= (rect.x + rect.w) &&
			mouseY >= rect.y && mouseY <= (rect.y + rect.h);
	}


	void Button::SetOnClick(std::function<void()> onClick) {
		OnClick = onClick;
	}


#pragma region setters
	void Button::setBackgroundColor(SDL_Color color) {
		backgroundColour = color;

	}


	void Button::setTextColor(SDL_Color color) {
		textColour = color;

	}


	void Button::setBorderColor(SDL_Color color) {
		borderColour = color;

	}


	void Button::setRoundedCorners(bool rounded) {
		//not without sdl_gfx

	}


	void Button::setCentered(bool centered) {
		isTextCentered = centered;
	}


	void Button::setScreenDimensions(int screenWidth_, int screenHeight_, bool centered) {
		this->screenHeight_b = screenHeight_;
		this->screenWidth_b = screenWidth_;

		if (centered) {
			rect.x = (screenWidth_ - rect.w) / 2;
			rect.y = (screenHeight_ - rect.h) / 2;
		}

	}
#pragma endregion





	Text::Text(SDL_Renderer* textRenderer, const std::string& textText, TTF_Font* textFont)
		: renderer(textRenderer), text(textText), font(textFont)
	{}


	void Text::Render(int x, int y, SDL_Color textColour) {
		if (font) {
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);

			if (textSurface) {
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

				if (textTexture) {
					SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
					SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

					SDL_DestroyTexture(textTexture);
				}

				SDL_FreeSurface(textSurface);
			}
		}
	}


	void Text::setText(const std::string& newText) {
		text = newText;
	}


}