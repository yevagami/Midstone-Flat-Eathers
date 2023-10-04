#pragma once
#include <SDL.h>
#include "cmath"
#include <SDL_ttf.h>
#include <string>
#include <functional>


namespace menu {
    extern SDL_Color SDL_COLOR_RED;
    extern SDL_Color SDL_COLOR_GREEN;
    extern SDL_Color SDL_COLOR_BLUE;
    extern SDL_Color SDL_COLOR_YELLOW;
    extern SDL_Color SDL_COLOR_MAGENTA;
    extern SDL_Color SDL_COLOR_CYAN;
    extern SDL_Color SDL_COLOR_ORANGE;
    extern SDL_Color SDL_COLOR_WHITE;
    extern SDL_Color SDL_COLOR_BLACK;
    extern SDL_Color SDL_COLOR_GRAY;


class Button {
public:
    //  renderer, xPos, yPos, width (x100), height (x100), text
    Button(SDL_Renderer* buttRenderer, int x, int y, int width, int height, const std::string& buttText);

    void Render(SDL_Texture* textTexture, TTF_Font* font);  //  renders the 'beauton'
    void SetOnClick(std::function<void()> onClick); //  sets a callback function for when its clicked
    bool IsMouseOver(int mouseX, int mouseY);   //  is the mouse hovering over?
    void HandleEvent(SDL_Event& event); //  handles events (mouse clicks)

protected:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::string text;
    std::function<void()> OnClick; //  holds a function to be executed when the button is clicked

      ///  styling
    SDL_Color backgroundColour;
    SDL_Color textColour;
    SDL_Color borderColour;
    int borderWidth;
    bool roundedCorners;
    bool isTextCentered;

public:
    void SetBackgroundColor(SDL_Color color); // Set background color
    void SetTextColor(SDL_Color color);       // Set text color
    void SetBorderColor(SDL_Color color);     // Set border color
    void SetBorderWidth(int width);           // Set border width
    void SetRoundedCorners(bool rounded);     // Enable or disable rounded corners
    void SetCentered(bool centered);          // Enable or disable centering

};


struct Text {
public:
        //  Constructor: renderer, text string, and the font
    Text(SDL_Renderer* renderer_, const std::string& text_, TTF_Font* font_);
    void setText(const std::string& newText);

        //  render the text at the given position in the given colour
    void Render(int x, int y, SDL_Color textColour);

protected:
    SDL_Renderer* renderer;
    std::string text;

    TTF_Font* font;
};


}