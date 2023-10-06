#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


/// Constants 
namespace ui {
    //  converter
    Uint8* SDLColorToUint8(SDL_Color color);

#pragma region shapes
    extern SDL_Rect SDL_Rectangle;
    extern SDL_Rect SDL_Testangle;
    extern SDL_Rect SDL_Wide_Rectangle;
    extern SDL_Rect SDL_Tall_Rectangle;
    extern SDL_Rect SDL_Square;
#pragma endregion
#pragma region colour constants
#pragma region colours
    extern SDL_Color SDL_COLOR_ALICE_BLUE;
    extern SDL_Color SDL_COLOR_AMETHYST;
    extern SDL_Color SDL_COLOR_ANTIQUE_WHITE;
    extern SDL_Color SDL_COLOR_APPLE_GREEN;
    extern SDL_Color SDL_COLOR_APRICOT;
    extern SDL_Color SDL_COLOR_AQUA;
    extern SDL_Color SDL_COLOR_AQUAMARINE;
    extern SDL_Color SDL_COLOR_AZURE;
    extern SDL_Color SDL_COLOR_AZURE_MIST;
    extern SDL_Color SDL_COLOR_BALL_BLUE;
    extern SDL_Color SDL_COLOR_BANANA_YELLOW;
    extern SDL_Color SDL_COLOR_BATTLESHIP_GREY;
    extern SDL_Color SDL_COLOR_BEIGE;
    extern SDL_Color SDL_COLOR_BISQUE;
    extern SDL_Color SDL_COLOR_BLACK;
    extern SDL_Color SDL_COLOR_BLANCHED_ALMOND;
    extern SDL_Color SDL_COLOR_BLUE;
    extern SDL_Color SDL_COLOR_BLUE_VIOLET;
    extern SDL_Color SDL_COLOR_BROWN;
    extern SDL_Color SDL_COLOR_BUBBLES;
    extern SDL_Color SDL_COLOR_BURLY_WOOD;
    extern SDL_Color SDL_COLOR_BURNT_ORANGE;
    extern SDL_Color SDL_COLOR_CADET_BLUE;
    extern SDL_Color SDL_COLOR_CAMEL;
    extern SDL_Color SDL_COLOR_CANDY_PINK;
    extern SDL_Color SDL_COLOR_CARMINE;
    extern SDL_Color SDL_COLOR_CHARCOAL;
    extern SDL_Color SDL_COLOR_CHARTREUSE;
    extern SDL_Color SDL_COLOR_CHERRY;
    extern SDL_Color SDL_COLOR_CHOCOLATE;
    extern SDL_Color SDL_COLOR_CITRINE;
    extern SDL_Color SDL_COLOR_COBALT_BLUE;
    extern SDL_Color SDL_COLOR_COCOA_BROWN;
    extern SDL_Color SDL_COLOR_CORAL;
    extern SDL_Color SDL_COLOR_CORNFLOWER_BLUE;
    extern SDL_Color SDL_COLOR_CRIMSON;
    extern SDL_Color SDL_COLOR_CRIMSON_RED;
    extern SDL_Color SDL_COLOR_CREAM;
    extern SDL_Color SDL_COLOR_CYAN;
    extern SDL_Color SDL_COLOR_DARK_BLUE;
    extern SDL_Color SDL_COLOR_DARK_CYAN;
    extern SDL_Color SDL_COLOR_DARK_GOLDENROD;
    extern SDL_Color SDL_COLOR_DARK_GRAY;
    extern SDL_Color SDL_COLOR_DARK_GREEN;
    extern SDL_Color SDL_COLOR_DARK_KHAKI;
    extern SDL_Color SDL_COLOR_DARK_LAVENDER;
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
    extern SDL_Color SDL_COLOR_DEEP_LILAC;
    extern SDL_Color SDL_COLOR_DEEP_PINK;
    extern SDL_Color SDL_COLOR_DEEP_SKY_BLUE;
    extern SDL_Color SDL_COLOR_DIM_GRAY;
    extern SDL_Color SDL_COLOR_DODGER_BLUE;
    extern SDL_Color SDL_COLOR_DUSK_PINK;
    extern SDL_Color SDL_COLOR_EGGPLANT_PURPLE;
    extern SDL_Color SDL_COLOR_EMERALD_GREEN;
    extern SDL_Color SDL_COLOR_FAWN;
    extern SDL_Color SDL_COLOR_FIREBRICK;
    extern SDL_Color SDL_COLOR_FLORAL_WHITE;
    extern SDL_Color SDL_COLOR_FOREST_BROWN;
    extern SDL_Color SDL_COLOR_FOREST_GREEN;
    extern SDL_Color SDL_COLOR_FROST;
    extern SDL_Color SDL_COLOR_FUCHSIA;
    extern SDL_Color SDL_COLOR_FUCHSIA_PINK;
    extern SDL_Color SDL_COLOR_GAINSBORO;
    extern SDL_Color SDL_COLOR_GHOST_WHITE;
    extern SDL_Color SDL_COLOR_GOLD;
    extern SDL_Color SDL_COLOR_GOLDEN_YELLOW;
    extern SDL_Color SDL_COLOR_GOLDENROD;
    extern SDL_Color SDL_COLOR_GRAPE_PURPLE;
    extern SDL_Color SDL_COLOR_GRAY;
    extern SDL_Color SDL_COLOR_GREEN;
    extern SDL_Color SDL_COLOR_GREEN_YELLOW;
    extern SDL_Color SDL_COLOR_HONEYDEW;
    extern SDL_Color SDL_COLOR_HONEY_BROWN;
    extern SDL_Color SDL_COLOR_HOT_PINK;
    extern SDL_Color SDL_COLOR_INDIGO;
    extern SDL_Color SDL_COLOR_INDIGO_BLUE;
    extern SDL_Color SDL_COLOR_IVORY;
    extern SDL_Color SDL_COLOR_JADE_GREEN;
    extern SDL_Color SDL_COLOR_KHAKI;
    extern SDL_Color SDL_COLOR_LAVENDER;
    extern SDL_Color SDL_COLOR_LAVENDER_BLUSH;
    extern SDL_Color SDL_COLOR_LAVENDER_PURPLE;
    extern SDL_Color SDL_COLOR_LEMONADE;
    extern SDL_Color SDL_COLOR_LEMON_CHIFFON;
    extern SDL_Color SDL_COLOR_LIGHT_BRONZE;
    extern SDL_Color SDL_COLOR_LIGHT_BLUE;
    extern SDL_Color SDL_COLOR_LIGHT_CORAL;
    extern SDL_Color SDL_COLOR_LIGHT_CYAN;
    extern SDL_Color SDL_COLOR_LIGHT_GOLDENROD_YELLOW;
    extern SDL_Color SDL_COLOR_LIGHT_GREEN;
    extern SDL_Color SDL_COLOR_LIGHT_GRAY;
    extern SDL_Color SDL_COLOR_LIGHT_JASMINE;
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
    extern SDL_Color SDL_COLOR_MARIGOLD;
    extern SDL_Color SDL_COLOR_MAROON;
    extern SDL_Color SDL_COLOR_MAUVE;
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
    extern SDL_Color SDL_COLOR_MIDNIGHT_PURPLE;
    extern SDL_Color SDL_COLOR_MINT_CREAM;
    extern SDL_Color SDL_COLOR_MOCCASIN;
    extern SDL_Color SDL_COLOR_MOSS_GREEN;
    extern SDL_Color SDL_COLOR_MULBERRY;
    extern SDL_Color SDL_COLOR_MUSTARD_YELLOW;
    extern SDL_Color SDL_COLOR_NIGHT_BLUE;
    extern SDL_Color SDL_COLOR_NAVY;
    extern SDL_Color SDL_COLOR_OCEAN_BLUE;
    extern SDL_Color SDL_COLOR_OLD_LACE;
    extern SDL_Color SDL_COLOR_OLIVE;
    extern SDL_Color SDL_COLOR_OLIVE_DRAB;
    extern SDL_Color SDL_COLOR_ORANGE;
    extern SDL_Color SDL_COLOR_ORANGE_PEEL;
    extern SDL_Color SDL_COLOR_ORANGE_RED;
    extern SDL_Color SDL_COLOR_ORCHID;
    extern SDL_Color SDL_COLOR_PALE_GOLDENROD;
    extern SDL_Color SDL_COLOR_PALE_GREEN;
    extern SDL_Color SDL_COLOR_PALE_LAVENDER;
    extern SDL_Color SDL_COLOR_PALE_TURQUOISE;
    extern SDL_Color SDL_COLOR_PALE_VIOLET_RED;
    extern SDL_Color SDL_COLOR_PAPAYA_WHIP;
    extern SDL_Color SDL_COLOR_PEACH_PUFF;
    extern SDL_Color SDL_COLOR_PEACHY_PINK;
    extern SDL_Color SDL_COLOR_PERU;
    extern SDL_Color SDL_COLOR_PERSIMMON;
    extern SDL_Color SDL_COLOR_PINE_GREEN;
    extern SDL_Color SDL_COLOR_PINEAPPLE_YELLOW;
    extern SDL_Color SDL_COLOR_WARM_STREAM;
    extern SDL_Color SDL_COLOR_COOL_STREAM;
    extern SDL_Color SDL_COLOR_AMBER_STREAM;
    extern SDL_Color SDL_COLOR_GOLDEN_STREAM;
    extern SDL_Color SDL_COLOR_BOOGER_GREEN;
    extern SDL_Color SDL_COLOR_PLUM;
    extern SDL_Color SDL_COLOR_POWDER_BLUE;
    extern SDL_Color SDL_COLOR_PUMPKIN_ORANGE;
    extern SDL_Color SDL_COLOR_RASPBERRY;
    extern SDL_Color SDL_COLOR_RED;
    extern SDL_Color SDL_COLOR_ROBIN_EGG_BLUE;
    extern SDL_Color SDL_COLOR_ROSIE_BROWN;
    extern SDL_Color SDL_COLOR_ROSY_BROWN;
    extern SDL_Color SDL_COLOR_ROYAL_BLUE;
    extern SDL_Color SDL_COLOR_SADDLE_BROWN;
    extern SDL_Color SDL_COLOR_POOPSTAIN;
    extern SDL_Color SDL_COLOR_LAWN_GREEN;
    extern SDL_Color SDL_COLOR_SALAMANDER;
    extern SDL_Color SDL_COLOR_SALMON;
    extern SDL_Color SDL_COLOR_SANDY_BROWN;
    extern SDL_Color SDL_COLOR_SCARLET_RED;
    extern SDL_Color SDL_COLOR_SEAFOAM_GREEN;
    extern SDL_Color SDL_COLOR_SEA_GREEN;
    extern SDL_Color SDL_COLOR_SEASHELL;
    extern SDL_Color SDL_COLOR_SILVER;
    extern SDL_Color SDL_COLOR_SILVER_GREY;
    extern SDL_Color SDL_COLOR_SKY_BLUE;
    extern SDL_Color SDL_COLOR_SKY_GREY;
    extern SDL_Color SDL_COLOR_SLATE_BLUE;
    extern SDL_Color SDL_COLOR_SLATE_GRAY;
    extern SDL_Color SDL_COLOR_SNOW;
    extern SDL_Color SDL_COLOR_SPRING_GREEN;
    extern SDL_Color SDL_COLOR_SPRUCE;
    extern SDL_Color SDL_COLOR_STEEL_BLUE;
    extern SDL_Color SDL_COLOR_STORMY_GREY;
    extern SDL_Color SDL_COLOR_SUNFLOWER_YELLOW;
    extern SDL_Color SDL_COLOR_TANGERINE;
    extern SDL_Color SDL_COLOR_TAN;
    extern SDL_Color SDL_COLOR_TEAL;
    extern SDL_Color SDL_COLOR_TERRACOTTA;
    extern SDL_Color SDL_COLOR_THISTLE;
    extern SDL_Color SDL_COLOR_TITANIUM;
    extern SDL_Color SDL_COLOR_TOMATO;
    extern SDL_Color SDL_COLOR_TOMATO_RED;
    extern SDL_Color SDL_COLOR_TULIP_PINK;
    extern SDL_Color SDL_COLOR_TURQUOISE;
    extern SDL_Color SDL_COLOR_TURQUOISE_BLUE;
    extern SDL_Color SDL_COLOR_TWILIGHT_BLUE;
    extern SDL_Color SDL_COLOR_VERMILLION;
    extern SDL_Color SDL_COLOR_VIOLET;
    extern SDL_Color SDL_COLOR_VIOLET_RED;
    extern SDL_Color SDL_COLOR_WHEAT;
    extern SDL_Color SDL_COLOR_WHITE;
    extern SDL_Color SDL_COLOR_WINTER_GREY;
    extern SDL_Color SDL_COLOR_XANADU;
    extern SDL_Color SDL_COLOR_YELLOW;
    extern SDL_Color SDL_COLOR_YELLOW_GREEN;
    extern SDL_Color SDL_COLOR_ZAFFRE;
    extern SDL_Color SDL_COLOR_ZINNWALDITE;
    extern SDL_Color SDL_COLOR_ZUCCHINI;
    extern SDL_Color SDL_COLOR_MARINE_BLUE;
    extern SDL_Color SDL_COLOR_LAVENDER_BLUSH;
    extern SDL_Color SDL_COLOR_PEACH;
    extern SDL_Color SDL_COLOR_STARRY_NIGHT;
    extern SDL_Color SDL_COLOR_EMERALD;
    extern SDL_Color SDL_COLOR_COTTON_CANDY;
    extern SDL_Color SDL_COLOR_OCEAN;
    extern SDL_Color SDL_COLOR_GOLDEN_SUNSET;
    extern SDL_Color SDL_COLOR_RUBY_RED;
    extern SDL_Color SDL_COLOR_MIDNIGHT_SKY;
    extern SDL_Color SDL_COLOR_LUSH_GREEN;
    extern SDL_Color SDL_COLOR_TROPICAL_ORANGE;
    extern SDL_Color SDL_COLOR_SILVER_MIST;
    extern SDL_Color SDL_COLOR_MYSTIC_PURPLE;
    extern SDL_Color SDL_COLOR_TEAL_BLUE;
    extern SDL_Color SDL_COLOR_BUBBLES;
    extern SDL_Color SDL_COLOR_BUBBLEGUM;
#pragma endregion
#pragma region appliances dlc
    extern SDL_Color SDL_COLOR_MUG;
    extern SDL_Color SDL_COLOR_TOASTER;
    extern SDL_Color SDL_COLOR_SOFA;
    extern SDL_Color SDL_COLOR_BOOKSHELF;
    extern SDL_Color SDL_COLOR_TELEVISION;
    extern SDL_Color SDL_COLOR_PLANT_POT;
    extern SDL_Color SDL_COLOR_LAMP;
    extern SDL_Color SDL_COLOR_COMPUTER;
    extern SDL_Color SDL_COLOR_BED;
    extern SDL_Color SDL_COLOR_WARDROBE;
    extern SDL_Color SDL_COLOR_CHAIR;
    extern SDL_Color SDL_COLOR_FRIDGE;
    extern SDL_Color SDL_COLOR_OVEN;
    extern SDL_Color SDL_COLOR_MICROWAVE;
    extern SDL_Color SDL_COLOR_CUTLERY;
    extern SDL_Color SDL_COLOR_PLATE;
    extern SDL_Color SDL_COLOR_CANDLE;
    extern SDL_Color SDL_COLOR_VASE;
    extern SDL_Color SDL_COLOR_BLINDS;
    extern SDL_Color SDL_COLOR_CARPET;
    extern SDL_Color SDL_COLOR_SHOES;
    extern SDL_Color SDL_COLOR_FRAME;
    extern SDL_Color SDL_COLOR_RADIO;
    extern SDL_Color SDL_COLOR_HEADPHONES;
    extern SDL_Color SDL_COLOR_BRUSH;
    extern SDL_Color SDL_COLOR_HAIR_DRYER;
    extern SDL_Color SDL_COLOR_TOOTHBRUSH;
    extern SDL_Color SDL_COLOR_WASHING_MACHINE;
#pragma endregion
#pragma region minecraft blocks dlc
    extern SDL_Color SDL_COLOR_ANVIL;
    extern SDL_Color SDL_COLOR_BARREL;
    extern SDL_Color SDL_COLOR_BAMBOO;
    extern SDL_Color SDL_COLOR_BEDROCK;
    extern SDL_Color SDL_COLOR_BEEHIVE;
    extern SDL_Color SDL_COLOR_BEE_NEST;
    extern SDL_Color SDL_COLOR_BELL;
    extern SDL_Color SDL_COLOR_BLAST_FURNACE;
    extern SDL_Color SDL_COLOR_CAMPFIRE;
    extern SDL_Color SDL_COLOR_CHEST;
    extern SDL_Color SDL_COLOR_COAL_ORE;
    extern SDL_Color SDL_COLOR_COBBLESTONE;
    extern SDL_Color SDL_COLOR_COMPOSTER;
    extern SDL_Color SDL_COLOR_CRAFTING_TABLE;
    extern SDL_Color SDL_COLOR_DIRT;
    extern SDL_Color SDL_COLOR_DISPENSER;
    extern SDL_Color SDL_COLOR_ENCHANTING_TABLE;
    extern SDL_Color SDL_COLOR_END_PORTAL_FRAME;
    extern SDL_Color SDL_COLOR_FLETCHING_TABLE;
    extern SDL_Color SDL_COLOR_FURNACE;
    extern SDL_Color SDL_COLOR_GOLD_ORE;
    extern SDL_Color SDL_COLOR_GLASS;
    extern SDL_Color SDL_COLOR_GRAVEL;
    extern SDL_Color SDL_COLOR_GRASS_BLOCK;
    extern SDL_Color SDL_COLOR_GRASS_PATH;
    extern SDL_Color SDL_COLOR_GRINDSTONE;
    extern SDL_Color SDL_COLOR_IRON_ORE;
    extern SDL_Color SDL_COLOR_ICE;
    extern SDL_Color SDL_COLOR_JUKEBOX;
    extern SDL_Color SDL_COLOR_LADDER;
    extern SDL_Color SDL_COLOR_LAPIS_LAZULI_ORE;
    extern SDL_Color SDL_COLOR_LAVA;
    extern SDL_Color SDL_COLOR_LILAC;
    extern SDL_Color SDL_COLOR_LOOM;
    extern SDL_Color SDL_COLOR_NOTEBLOCK;
    extern SDL_Color SDL_COLOR_OAK_LEAVES;
    extern SDL_Color SDL_COLOR_OAK_LOG;
    extern SDL_Color SDL_COLOR_OBSIDIAN;
    extern SDL_Color SDL_COLOR_PACKED_ICE;
    extern SDL_Color SDL_COLOR_PEONY;
    extern SDL_Color SDL_COLOR_RED_TULIP;
    extern SDL_Color SDL_COLOR_ROSE_BUSH;
    extern SDL_Color SDL_COLOR_SAND;
    extern SDL_Color SDL_COLOR_SANDSTONE;
    extern SDL_Color SDL_COLOR_SCAFFOLDING;
    extern SDL_Color SDL_COLOR_SEAGRASS;
    extern SDL_Color SDL_COLOR_SMITHING_TABLE;
    extern SDL_Color SDL_COLOR_SOUL_CAMPFIRE;
    extern SDL_Color SDL_COLOR_STONE;
    extern SDL_Color SDL_COLOR_STONECUTTER;
    extern SDL_Color SDL_COLOR_TALL_GRASS;
    extern SDL_Color SDL_COLOR_TALL_SEAGRASS;
    extern SDL_Color SDL_COLOR_TORCH;
    extern SDL_Color SDL_COLOR_WATER;
    extern SDL_Color SDL_COLOR_WET_SPONGE;
#pragma endregion 
#pragma region overwat dlc
    // Tank Heroes
    extern SDL_Color SDL_COLOR_DVA;
    extern SDL_Color SDL_COLOR_DOOMFIST;
    extern SDL_Color SDL_COLOR_JUNKER_QUEEN;
    extern SDL_Color SDL_COLOR_ORISA;
    extern SDL_Color SDL_COLOR_RAMATTRA;
    extern SDL_Color SDL_COLOR_REINHARDT;
    extern SDL_Color SDL_COLOR_ROADHOG;
    extern SDL_Color SDL_COLOR_SIGMA;
    extern SDL_Color SDL_COLOR_WINSTON;
    extern SDL_Color SDL_COLOR_WRECKING_BALL;
    extern SDL_Color SDL_COLOR_ZARYA;

    // Damage Heroes
    extern SDL_Color SDL_COLOR_ASHE;
    extern SDL_Color SDL_COLOR_BASTION;
    extern SDL_Color SDL_COLOR_CASSIDY;
    extern SDL_Color SDL_COLOR_ECHO;
    extern SDL_Color SDL_COLOR_GENJI;
    extern SDL_Color SDL_COLOR_HANZO;
    extern SDL_Color SDL_COLOR_JUNKRAT;
    extern SDL_Color SDL_COLOR_MEI;
    extern SDL_Color SDL_COLOR_PHARAH;
    extern SDL_Color SDL_COLOR_REAPER;
    extern SDL_Color SDL_COLOR_SOJOURN;
    extern SDL_Color SDL_COLOR_SOLDIER_76;
    extern SDL_Color SDL_COLOR_SOMBRA;
    extern SDL_Color SDL_COLOR_SYMMETRA;
    extern SDL_Color SDL_COLOR_TORBJORN;
    extern SDL_Color SDL_COLOR_TRACER;
    extern SDL_Color SDL_COLOR_WIDOWMAKER;

    // Support Heroes
    extern SDL_Color SDL_COLOR_ANA;
    extern SDL_Color SDL_COLOR_BAPTISTE;
    extern SDL_Color SDL_COLOR_BRIGITTE;
    extern SDL_Color SDL_COLOR_ILLARI;
    extern SDL_Color SDL_COLOR_KIRIKO;
    extern SDL_Color SDL_COLOR_LIFEWEAVER;
    extern SDL_Color SDL_COLOR_LUCIO;
    extern SDL_Color SDL_COLOR_MERCY;
    extern SDL_Color SDL_COLOR_MOIRA;
    extern SDL_Color SDL_COLOR_ZENYATTA;
#pragma endregion
#pragma region jail dlc
    extern SDL_Color SDL_COLOR_ROSE_TOY;
    extern SDL_Color SDL_COLOR_BAD_DRAGON;
#pragma endregion
#pragma endregion
}



/// Main Classes
namespace ui {
    /// Font Map
    static const std::unordered_map<const char*, const char*> fontMap = {
    {"comic sans", "fonts/COMIC.TTF"},
    {"open sans", "fonts/OpenSans-Regular.ttf"},
    {"gothic", "fonts/DelaGothicOne-Regular.ttf"},
    {"heebo", "fonts/Heebo-Regular.ttf"},
    {"roboto", "fonts/Roboto-Regular.ttf"},
    {"", ""},
    };

    /// Font Modifier Object
    struct FontModifier {
        int size;
        int offsetX;
        int offsetY;
        double rotation;

        // Constructor with default values
        FontModifier(int size_ = 45, int x = 0, int y = 0, double rot = 0.0)
            : size(size_), offsetX(x), offsetY(y), rotation(rot) {}
    };


//  to do:
//  - visibility
//  - background image support (uh oh)
//  - gradients
//  [DONE] - many colours
//  - colour map... (will break ui)
//  - fonts other than... my beloved...
//  [H/DONE] - diff shaped buttons
//  - text as a component, then icon support
// [DONE] - rendering as a component
//
//
//class goals
// - simple, but powerful.
// - default values
// - ability for a one line full creator (minus render)
// - performance optimized
// - important functions start with Caps();
// - other functions start with lowercase();
// - !!attributes are public!!
//  
class Button {
public:
        /// Constructors
    //  default consstructor
    Button() : buttonRenderer(nullptr), rect({ 0,0,0,0 }), backgroundColour(SDL_COLOR_WHITE) {
        text = ""; font = ""; fontSize = 0; fontOffsetX = 0; fontOffsetY = 0; fontRotation = 0; isTextCentered = true; isButtonCentered = false; textColour = SDL_COLOR_WHITE; borderColour = SDL_COLOR_WHITE;
        buttonTextFont = nullptr; buttonTextTexture = nullptr; buttonTextSurface = nullptr;  }

    //  main constructor
    Button(
        SDL_Renderer* buttonRenderer_,
        const char* text_ = "sad button",
        SDL_Rect rect_ = { 0, 0, 0, 0 },
        SDL_Color backgroundColour_ = SDL_COLOR_MYSTIC_PURPLE,
        const char* font_ = ui::fontMap.at("comic sans"),
        const FontModifier& fontModifier_ = FontModifier(),
        SDL_Color textColour_ = SDL_COLOR_SOUL_CAMPFIRE
    ) :
        buttonRenderer(buttonRenderer_), text(text_), rect(rect_),
        backgroundColour(backgroundColour_),
        font(font_), fontModifier(fontModifier_), textColour(textColour_)
    {
        isTextCentered = true; isButtonCentered = false;
        //useGradientBackground = false; isGradientVertical = false; gradientEnd = SDL_COLOR_MYSTIC_PURPLE; gradientStart = SDL_COLOR_BLACK;
        borderColour = SDL_COLOR_BLACK;

        fontSize = fontModifier_.size;
        fontOffsetX = fontModifier_.offsetX;
        fontOffsetY = fontModifier_.offsetY;
        fontRotation = fontModifier_.rotation;

        buttonTextFont = nullptr; buttonTextTexture = nullptr; buttonTextSurface = nullptr;
    }

    ~Button() 
    {
        if (buttonTextFont) {
            TTF_CloseFont(buttonTextFont);
            buttonTextFont = nullptr;
        }

        if (buttonTextTexture) {
            SDL_DestroyTexture(buttonTextTexture);
            buttonTextTexture = nullptr;
        }
        if (buttonTextSurface) {
            SDL_FreeSurface(buttonTextSurface);
            buttonTextSurface = nullptr;
        }

    }


        /// Public Methods
    //  renders the 'beauton' components (its ironic theres a text class and yet the renderer takes the components needed to make text)
    bool Render();
    //  handles events (mouse clicks and hovering)
    void HandleEvent(SDL_Event& event);
    //  for animations, hover effects, and live-things
    void Update(float deltaTime);
    //  sets a callback function for when its clicked
    void SetOnClick(std::function<void()> onClick);
    //  is the mouse hovering over the button's dimensions? [true/false]
    bool isMouseOver(int mouseX, int mouseY);
protected:

        /// Private Methods
    //  renders the background component
    bool RenderBackground();
    //  renders the borders component
    bool RenderBorder();
    //  renders the text component
    bool RenderText();

        /// Private Variables
     //  a "the renderer"(tm)
    SDL_Renderer* buttonRenderer;
    //  a rectangle
    SDL_Rect rect;
    FontModifier fontModifier;
    TTF_Font* buttonTextFont;
    SDL_Texture* buttonTextTexture;
    SDL_Surface* buttonTextSurface;

    //  a function as a variable
    std::function<void()> OnClick;


#pragma region styling [tw: aesthetic]
public:
        /// Editable Attributes [ public variables lmao ]
    //  button's text
    const char* text;
    //  button's font
    const char* font;

    int fontSize;
    double fontRotation;
    int fontOffsetX;
    int fontOffsetY;

    bool isTextCentered;     //  centered text flag
    bool isButtonCentered;    //  centered button flag
    SDL_Color backgroundColour;    //  button's background colour
    SDL_Color borderColour;    //  button's boarder colour
    SDL_Color textColour;    //  button's text colour

private:    ///  indev stuff
    //bool useGradientBackground;
    //bool isGradientVertical;
    //SDL_Color gradientStart;
    //SDL_Color gradientEnd;

    public: 
        /// Modifier Methods 
        int getX() { return rect.x; };
        int getY() { return rect.y; };
        int getH() { return rect.h; };
        int getW() { return rect.w; };

        //  set position (absolutely transform)
    void setPosition(int newRectY = 0, int newRectX = 0);
        //  offset position (relative transform)
    void offsetPosition(int newRectYOffset = 0, int newRectXOffset = 0);
        //  set the dimensions
    void setDimensions(int newRectHeight, int newRectWidth);
        //  scale the dimensions
    void scaleDimensionsIndividually(int newRectHeightScaler = 1, int newRectWidthScaler = 1);
        //  scale the dimensions
    void scaleDimensions(int scaler = 1);
        //  center to screen
    void centerPosition(int screenWidth_, int screenHeight_);
#pragma endregion
};

struct Text {
public:
    Text(SDL_Renderer* textRenderer, const std::string& textText, TTF_Font* textFont)
        : buttonRenderer(textRenderer), text(textText), font(textFont)
    {}

    //  render the text at the given position in the given colour
    void Render(int x, int y, SDL_Color textColour);

    std::string text;

protected:
    SDL_Renderer* buttonRenderer;
    TTF_Font* font;
};

}
