#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <functional>


namespace menu {


#pragma region constants
    extern SDL_Color SDL_COLOR_ALICE_BLUE;
    extern SDL_Color SDL_COLOR_ANTIQUE_WHITE;
    extern SDL_Color SDL_COLOR_AQUA;
    extern SDL_Color SDL_COLOR_AQUAMARINE;
    extern SDL_Color SDL_COLOR_AZURE;
    extern SDL_Color SDL_COLOR_BEIGE;
    extern SDL_Color SDL_COLOR_BISQUE;
    extern SDL_Color SDL_COLOR_BLACK;
    extern SDL_Color SDL_COLOR_BLANCHED_ALMOND;
    extern SDL_Color SDL_COLOR_BLUE;
    extern SDL_Color SDL_COLOR_BLUE_VIOLET;
    extern SDL_Color SDL_COLOR_BROWN;
    extern SDL_Color SDL_COLOR_BURLY_WOOD;
    extern SDL_Color SDL_COLOR_CADET_BLUE;
    extern SDL_Color SDL_COLOR_CHARTREUSE;
    extern SDL_Color SDL_COLOR_CHOCOLATE;
    extern SDL_Color SDL_COLOR_CORAL;
    extern SDL_Color SDL_COLOR_CORNFLOWER_BLUE;
    extern SDL_Color SDL_COLOR_CRIMSON;
    extern SDL_Color SDL_COLOR_CYAN;
    extern SDL_Color SDL_COLOR_DARK_BLUE;
    extern SDL_Color SDL_COLOR_DARK_CYAN;
    extern SDL_Color SDL_COLOR_DARK_GOLDENROD;
    extern SDL_Color SDL_COLOR_DARK_GRAY;
    extern SDL_Color SDL_COLOR_DARK_GREEN;
    extern SDL_Color SDL_COLOR_DARK_KHAKI;
    extern SDL_Color SDL_COLOR_DARK_MAGENTA;
    extern SDL_Color SDL_COLOR_DARK_OLIVE_GREEN;
    extern SDL_Color SDL_COLOR_DARK_ORANGE;
    extern SDL_Color SDL_COLOR_DARK_RED;
    extern SDL_Color SDL_COLOR_DARK_SALMON;
    extern SDL_Color SDL_COLOR_DARK_SEA_GREEN;
    extern SDL_Color SDL_COLOR_DARK_SLATE_BLUE;
    extern SDL_Color SDL_COLOR_DARK_SLATE_GRAY;
    extern SDL_Color SDL_COLOR_DARK_TURQUOISE;
    extern SDL_Color SDL_COLOR_DARK_VIOLET;
    extern SDL_Color SDL_COLOR_DEEP_PINK;
    extern SDL_Color SDL_COLOR_DEEP_SKY_BLUE;
    extern SDL_Color SDL_COLOR_DIM_GRAY;
    extern SDL_Color SDL_COLOR_DODGER_BLUE;
    extern SDL_Color SDL_COLOR_FIREBRICK;
    extern SDL_Color SDL_COLOR_FLORAL_WHITE;
    extern SDL_Color SDL_COLOR_FOREST_GREEN;
    extern SDL_Color SDL_COLOR_FUCHSIA;
    extern SDL_Color SDL_COLOR_GAINSBORO;
    extern SDL_Color SDL_COLOR_GHOST_WHITE;
    extern SDL_Color SDL_COLOR_GOLD;
    extern SDL_Color SDL_COLOR_GOLDENROD;
    extern SDL_Color SDL_COLOR_GRAY;
    extern SDL_Color SDL_COLOR_GREEN;
    extern SDL_Color SDL_COLOR_GREEN_YELLOW;
    extern SDL_Color SDL_COLOR_HONEYDEW;
    extern SDL_Color SDL_COLOR_INDIGO;
    extern SDL_Color SDL_COLOR_IVORY;
    extern SDL_Color SDL_COLOR_KHAKI;
    extern SDL_Color SDL_COLOR_LAVENDER;
    extern SDL_Color SDL_COLOR_LAVENDER_BLUSH;
    extern SDL_Color SDL_COLOR_LEMON_CHIFFON;
    extern SDL_Color SDL_COLOR_LIGHT_BLUE;
    extern SDL_Color SDL_COLOR_LIGHT_CORAL;
    extern SDL_Color SDL_COLOR_LIGHT_CYAN;
    extern SDL_Color SDL_COLOR_LIGHT_GOLDENROD_YELLOW;
    extern SDL_Color SDL_COLOR_LIGHT_GREEN;
    extern SDL_Color SDL_COLOR_LIGHT_GRAY;
    extern SDL_Color SDL_COLOR_LIGHT_PINK;
    extern SDL_Color SDL_COLOR_LIGHT_SALMON;
    extern SDL_Color SDL_COLOR_LIGHT_SEA_GREEN;
    extern SDL_Color SDL_COLOR_LIGHT_SKY_BLUE;
    extern SDL_Color SDL_COLOR_LIGHT_SLATE_GRAY;
    extern SDL_Color SDL_COLOR_LIGHT_STEEL_BLUE;
    extern SDL_Color SDL_COLOR_LIGHT_YELLOW;
    extern SDL_Color SDL_COLOR_LIME;
    extern SDL_Color SDL_COLOR_LIME_GREEN;
    extern SDL_Color SDL_COLOR_LINEN;
    extern SDL_Color SDL_COLOR_MAGENTA;
    extern SDL_Color SDL_COLOR_MAROON;
    extern SDL_Color SDL_COLOR_MEDIUM_AQUAMARINE;
    extern SDL_Color SDL_COLOR_MEDIUM_BLUE;
    extern SDL_Color SDL_COLOR_MEDIUM_ORCHID;
    extern SDL_Color SDL_COLOR_MEDIUM_PURPLE;
    extern SDL_Color SDL_COLOR_MEDIUM_SEA_GREEN;
    extern SDL_Color SDL_COLOR_MEDIUM_SLATE_BLUE;
    extern SDL_Color SDL_COLOR_MEDIUM_SPRING_GREEN;
    extern SDL_Color SDL_COLOR_MEDIUM_TURQUOISE;
    extern SDL_Color SDL_COLOR_MEDIUM_VIOLET_RED;
    extern SDL_Color SDL_COLOR_MIDNIGHT_BLUE;
    extern SDL_Color SDL_COLOR_MINT_CREAM;
    extern SDL_Color SDL_COLOR_MISTY_ROSE;
    extern SDL_Color SDL_COLOR_MOCCASIN;
    extern SDL_Color SDL_COLOR_NAVY;
    extern SDL_Color SDL_COLOR_OLD_LACE;
    extern SDL_Color SDL_COLOR_OLIVE;
    extern SDL_Color SDL_COLOR_OLIVE_DRAB;
    extern SDL_Color SDL_COLOR_ORANGE;
    extern SDL_Color SDL_COLOR_ORANGE_RED;
    extern SDL_Color SDL_COLOR_ORCHID;
    extern SDL_Color SDL_COLOR_PALE_GOLDENROD;
    extern SDL_Color SDL_COLOR_PALE_GREEN;
    extern SDL_Color SDL_COLOR_PALE_TURQUOISE;
    extern SDL_Color SDL_COLOR_PALE_VIOLET_RED;
    extern SDL_Color SDL_COLOR_PAPAYA_WHIP;
    extern SDL_Color SDL_COLOR_PEACH_PUFF;
    extern SDL_Color SDL_COLOR_PERU;
    extern SDL_Color SDL_COLOR_PINK;
    extern SDL_Color SDL_COLOR_PLUM;
    extern SDL_Color SDL_COLOR_POWDER_BLUE;
    extern SDL_Color SDL_COLOR_PURPLE;
    extern SDL_Color SDL_COLOR_RED;
    extern SDL_Color SDL_COLOR_ROSY_BROWN;
    extern SDL_Color SDL_COLOR_ROYAL_BLUE;
    extern SDL_Color SDL_COLOR_SADDLE_BROWN;
    extern SDL_Color SDL_COLOR_SALMON;
    extern SDL_Color SDL_COLOR_SANDY_BROWN;
    extern SDL_Color SDL_COLOR_SEA_GREEN;
    extern SDL_Color SDL_COLOR_SEASHELL;
    extern SDL_Color SDL_COLOR_SIENNA;
    extern SDL_Color SDL_COLOR_SILVER;
    extern SDL_Color SDL_COLOR_SKY_BLUE;
    extern SDL_Color SDL_COLOR_SLATE_BLUE;
    extern SDL_Color SDL_COLOR_SLATE_GRAY;
    extern SDL_Color SDL_COLOR_SNOW;
    extern SDL_Color SDL_COLOR_SPRING_GREEN;
    extern SDL_Color SDL_COLOR_STEEL_BLUE;
    extern SDL_Color SDL_COLOR_TAN;
    extern SDL_Color SDL_COLOR_TEAL;
    extern SDL_Color SDL_COLOR_THISTLE;
    extern SDL_Color SDL_COLOR_TOMATO;
    extern SDL_Color SDL_COLOR_TURQUOISE;
    extern SDL_Color SDL_COLOR_VIOLET;
    extern SDL_Color SDL_COLOR_WHEAT;
    extern SDL_Color SDL_COLOR_WHITE;
    extern SDL_Color SDL_COLOR_YELLOW;
    extern SDL_Color SDL_COLOR_YELLOW_GREEN;
#pragma endregion


    class MenuInterface {
    public:

        //  shouldn't need any private/protected members

    };


class Button {
public:
    //  renderer, xPos, yPos, width, height, text
    Button(SDL_Renderer* buttRenderer, int x, int y, int width, int height, const std::string& buttText);

    void Render(SDL_Texture* textTexture, TTF_Font* font);  //  renders the 'beauton'
    void HandleEvent(SDL_Event& event); //  handles events (mouse clicks)
    void SetOnClick(std::function<void()> onClick); //  sets a callback function for when its clicked
          //  to use this lambda function, do this (without comments): 
          //     create myButton(*parameters*);
          //     myButton.SetOnClick ([]) () 
          //    {
          // 
          //         std::cout << "the code to execute goes here (not a cout but yknow)" << endl;
          // 
          //    }

    bool isMouseOver(int mouseX, int mouseY);   //  is the mouse hovering over?

protected:
    SDL_Renderer* renderer;
    SDL_Rect rect;
    std::string text;

    std::function<void()> OnClick; //  holds a function to be executed when the button is clicked
#pragma region style
      ///  styling
    SDL_Color backgroundColour;
    SDL_Color textColour;
    SDL_Color borderColour;
    bool roundedCorners;
    bool isTextCentered;

public:
    void setBackgroundColor(SDL_Color color); // Set background color
    void setTextColor(SDL_Color color);       // Set text color
    void setBorderColor(SDL_Color color);     // Set border color
    void setBorderWidth(int width);           // Set border width
    void setRoundedCorners(bool rounded);     // Enable or disable rounded corners
    void setCentered(bool centered);          // Enable or disable centering
#pragma endregion
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