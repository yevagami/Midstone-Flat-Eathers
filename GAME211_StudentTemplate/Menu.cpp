#include "Menu.h"

namespace menu {

    SDL_Color SDL_COLOR_RED = { 255, 0, 0, 255 };
    SDL_Color SDL_COLOR_GREEN = { 0, 255, 0, 255 };
    SDL_Color SDL_COLOR_BLUE = { 0, 0, 255, 255 };
    SDL_Color SDL_COLOR_YELLOW = { 255, 255, 0, 255 };
    SDL_Color SDL_COLOR_MAGENTA = { 255, 0, 255, 255 };
    SDL_Color SDL_COLOR_CYAN = { 0, 255, 255, 255 };
    SDL_Color SDL_COLOR_ORANGE = { 255, 165, 0, 255 };
    SDL_Color SDL_COLOR_WHITE = { 255, 255, 255, 255 };
    SDL_Color SDL_COLOR_BLACK = { 0, 0, 0, 255 };
    SDL_Color SDL_COLOR_GRAY = { 128, 128, 128, 255 };


    menu::Button::Button(SDL_Renderer* buttRenderer, int x, int y, int width, int height, const std::string& buttText)
        : renderer(buttRenderer), rect({ x, y, width, height }), text(buttText), borderWidth(2), isTextCentered(false) {
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


void Button::SetOnClick(std::function<void()> onClick) {
    onClick = onClick;
}


bool Button::IsMouseOver(int mouseX, int mouseY) {
    return mouseX >= rect.x && mouseX <= (rect.x + rect.w) &&
        mouseY >= rect.y && mouseY <= (rect.y + rect.h);
}


void Button::HandleEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN && IsMouseOver(event.button.x, event.button.y)) {
        if (OnClick) {
            OnClick();
        }
    }

}

void Button::SetBackgroundColor(SDL_Color color) {
    backgroundColour = color;

}

void Button::SetTextColor(SDL_Color color) {
    textColour = color;

}

void Button::SetBorderColor(SDL_Color color){
    borderColour = color;

}

void Button::SetBorderWidth(int width) {
    borderWidth = width;

}

void Button::SetRoundedCorners(bool rounded) {
    //not without sdl_gfx

}

void Button::SetCentered(bool centered) {
    isTextCentered = centered;
}






Text::Text(SDL_Renderer* textRenderer, const std::string& textText, TTF_Font* textFont) 
    : renderer(textRenderer), text(textText), font(textFont)  {}


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