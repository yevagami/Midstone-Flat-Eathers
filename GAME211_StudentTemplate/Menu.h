#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <functional>

#include "Hitbox.h"

//	any class that utilizes the button, add the forward reference here, then tell the class itself that your class is a 'friend' of ui::Button
class Tracker;

/// SDL Menu Constants [scary | recommend hiding]
namespace ui {
	//	general colour clamping
	template <typename T>
	T Clamp(T value_, T min_, T max_);

	//	add 2 colours (straight up adds the components)
	SDL_Color operator+(const SDL_Color& colourA_, const SDL_Color& colourB_);
	//	subtracts 2 colours (straight up subtracts the components)
	SDL_Color operator-(const SDL_Color& colourA_, const SDL_Color& colourB_);
	//	blends 2 colours
	SDL_Color operator*(const SDL_Color& colourA_, const SDL_Color& colourB_);
	//	blends and darkens 2 colours
	SDL_Color operator/(const SDL_Color& colourA_, const SDL_Color& colourB_);
	//	inverts the colour
	SDL_Color operator!(const SDL_Color& colour_);
	//	randomizes the r,g,b values relative to the starting colour
	SDL_Color operator~(const SDL_Color& colour_);
	//	steals the transparency from the second colour
	SDL_Color operator<<(const SDL_Color& colourA_, const SDL_Color& colourB_);
	//SDL_Color operator|(const SDL_Color& colourA_, const SDL_Color& colourB_);


#pragma region shapes
	extern SDL_Rect SDL_Testangle;

	extern SDL_Rect SDL_Rectangle;
	extern SDL_Rect SDL_Wide_Rectangle;
	extern SDL_Rect SDL_Tall_Rectangle;
	extern SDL_Rect SDL_Square;
#pragma endregion
#pragma region colour constants
	///	Most Colour Constants are courtesy of GPT-3.5
#pragma region transparency
	extern SDL_Color SDL_White100;
	extern SDL_Color SDL_White90;
	extern SDL_Color SDL_White75;
	extern SDL_Color SDL_White50;
	extern SDL_Color SDL_White25;
	extern SDL_Color SDL_White10;
#pragma endregion
	///	"Give me a big list of SDL_Colors"
#pragma region colours
	extern SDL_Color SDL_COLOR_NULL;
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
	extern SDL_Color SDL_COLOR_PINK;
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
	extern SDL_Color SDL_COLOR_BUBBLEGUM;
#pragma endregion
	///	"Give me a list of SDL_Colors based off appliances"
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
	///	"Give me a list of SDL_Colors based off Minecraft blocks"
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
	///	"Give me a list of SDL_Colors based off Overwatch characters"
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


///  Main Class
namespace ui {
	///	this namespace handles font, buttons, text, and many constants. all under the "ui" namespace.
	///	font map: holds all fonts usable by the button class
	///	Font struct: purely for the constructor. allows the constructor to be called simply but with more power if needed
	///	Colour struct: purely for the constructor. ^
	///	Background Type enum class: literally just an enum.
	///	Button class: everything else. 

	// all the availible fonts
	static const std::unordered_map<const char*, const char*> fontMap = {
			{"comic sans", "fonts/COMIC.TTF"},
			{"open sans", "fonts/OpenSans-Regular.ttf"},
			{"gothic", "fonts/DelaGothicOne-Regular.ttf"},
			{"heebo", "fonts/Heebo-Regular.ttf"},
			{"roboto", "fonts/Roboto-Regular.ttf"},
			{"ubuntu", "fonts/Ubuntu-Regular.ttf"},
			{"verdana", "fonts/verdana.ttf"},
			{"wingdings", "fonts/Wingdings-Regular-Font.ttf"},
			{"lobster", "fonts/Lobster-Regular.ttf"},
			{"ransom", "fonts/ransom.ttf"},
			{"comic serif", "fonts/Comic_Serif_Pro.otf"},
			{"helvetica roman", "fonts/Helvetica Roman.ttf"},
			{"helvetica neue", "fonts/Helvetica Neue Medium.ttf"},

	};

	// Font Constructor Object
	struct Font {
		std::string fontText;
		int size;
		const char* font;
		int offsetX;
		int offsetY;
		double rotation;

		Font(
			std::string fontText_ = "", 
			const int size_ = 45,
			const char* font_ = fontMap.at("helvetica neue"),
			const int x_ = 0, 
			const int y_ = 0, 
			const double rot_ = 0.0)
			: fontText(std::move(fontText_)), size(size_), font(font_), offsetX(x_), offsetY(y_), rotation(rot_) { }

	};

	///	Colour Constructor Object
	struct Colour {
		SDL_Color background;
		SDL_Color text;
		SDL_Color border;
		SDL_Color textBorder;
		SDL_Color onHoverBackground;
		SDL_Color onHoverText;
		SDL_Color onHoverBorder;

		Colour(
			const SDL_Color background_ = SDL_COLOR_BLACK, 
			const SDL_Color text_ = SDL_COLOR_ANTIQUE_WHITE, 
			const SDL_Color border_ = SDL_COLOR_ANTIQUE_WHITE, 
			const SDL_Color textBorder_ = SDL_COLOR_BLACK,
			const SDL_Color onHoverBkg_ = SDL_COLOR_BLACK, 
			const SDL_Color onHoverTxt_ = SDL_COLOR_ANTIQUE_WHITE, 
			const SDL_Color onHoverBorder_ = SDL_COLOR_ANTIQUE_WHITE)
			: background(background_), text(text_), border(border_), textBorder(textBorder_),	onHoverBackground(onHoverBkg_), onHoverText(onHoverTxt_), onHoverBorder(onHoverBorder_) { }

	};

	///	Background Type storage enum
	enum class BackgroundType {
		SolidColour,
		Image
	};


	class Button {
	public:
		/// Constructors
		//	 the Constructor Objects change the way it's called. its scary at first, but powerful (i promise)
		Button(
			const Font& font_ = Font{},
			const SDL_Rect& rect_ = { 0, 0, 0, 0 },
			const Colour& colour_ = Colour{},
			const int borderThickness_ = 4
		) :
			rect(rect_), font(font_), colour(colour_), buttonBorderSize(borderThickness_) {

			hitbox = { 0,0,0,0 };
			backgroundType = BackgroundType::SolidColour; //		default is SolidColour (changed with SetBackgroundImage)
			backgroundImageDirectory = "";

			isTextCentered = true;
			isActive = true;
			isEasilyScared = false;
			isTogglable = false;
			isOn = false;
			isHovering = false;
			isPrideful = false;
			isButtonBordered = true;
			isTextBordered = false;
			isSensitiveToHovering = true;
			isHandlingEvents = true;
			textBorderSize = 2;
			backgroundImageRotationAngle = 0.0;

			//	colour shenegans
			backgroundColour = colour_.background;
			textColour = colour_.text;
			buttonBorderColour = colour_.border;
			textBorderColour = colour_.textBorder;
			onHoveringBackgroundColour = colour_.onHoverBackground;
			onHoveringTextColour = colour_.onHoverText;

			//	font shenegans
			text = font_.fontText;
			fontSize = font_.size;
			fontItself = font_.font;
			fontOffsetX = font_.offsetX;
			fontOffsetY = font_.offsetY;
			fontRotation = font_.rotation;

			//	po*nters
			buttonTextFont = nullptr;
			buttonTextTexture = nullptr;
			buttonTextSurface = nullptr;
			backgroundImageTexture = nullptr;
			//backgroundImageSurface = nullptr;
		}

		~Button() { ClearSDLStuff(); }

		/// Public Methods
		 //	handles events (mouse clicks and hovering)
		void HandleEvents(const SDL_Event& event_);
		//		for animations, hover effects, and live-things
		void Update(float deltaTime_);

		//		event callbacks
		void SetOnInteractionCallback(const std::function<void()>& onInteract_);
		void SetOnLeftClick(const std::function<void()>& onClick_);
		void SetOnRightClick(const std::function<void()>& onClick_);
		void SetOnScroll(const std::function<void(int scrollInt_)>& onScroll_);
		void SetOnHover(const std::function<void()>& onHover_);

		friend class ::Tracker;

		//		renders the 'beauton' components (its ironic theres a text class and yet the renderer takes the components needed to make text)
		bool Render(SDL_Renderer* renderer_);
	protected:
		/// Private Methods
		//		renders the background component
		bool RenderBackground(SDL_Renderer* renderer_) const;
		//		renders the borders component
		bool RenderBorder(SDL_Renderer* renderer_) const;
		//		renders the text component
		bool RenderText(SDL_Renderer* renderer_);

		bool SetBackgroundImage(const char* fileDirectory_, SDL_Renderer* renderer_);


		/// Private Variables
		//  a rectangle
		SDL_Rect rect;
		Hitbox hitbox;		//	  a hitbox
		Font font;				//  Font Constructor Container
		Colour colour;		//	  Colour Constructor Container

		TTF_Font* buttonTextFont;
		SDL_Texture* buttonTextTexture;
		SDL_Surface* buttonTextSurface;

		BackgroundType backgroundType;					//	button's background type (solid | image)
		SDL_Texture* backgroundImageTexture;

		//  a function as variables
		std::function<void()> OnInteractionCallback;
		std::function<void()> OnLeftClick;
		std::function<void()> OnRightClick;
		std::function<void()> OnHover;
		std::function<void(int scrollInt_)> OnScroll;
		Uint32 lastHoverTime = 0;

#pragma region styling [tw: aesthetic]
	public:
		/// Editable Attributes [ public variables lmao ]
		SDL_Color buttonBorderColour;						//  button's boarder colour
		SDL_Color textBorderColour;
		SDL_Color backgroundColour;							//  button's background colour
		SDL_Color onHoveringBackgroundColour;			//  button's hover background colour
		SDL_Color textColour;										//  button's text colour
		SDL_Color onHoveringTextColour;					//  button's hovering text colour
		const char* backgroundImageDirectory;			//	  link to the background image path
		double backgroundImageRotationAngle;			//	  the background image's rotation angle ( default : 0.0)

		float fontSize;														//	button's font size (default : 45)
		double fontRotation;										//	font rotation (default : 0.0)
		int fontOffsetX;												//	offset x (default : 0)
		int fontOffsetY;												//	offset y (default : 0)
		std::string text;												// button's text (default : "")
		const char* fontItself;									// button's font (default : )

		bool isActive;													//	is button active flag (default : true)
		bool isTogglable;												//	change to be a switch-style button (default : false)
		bool isOn;															//	when togglable, this is true when toggled (default : false*)
		bool isTextCentered;										//  is text centered flag (default : true)
		bool isPrideful;													//	change colour on click (default : false)
		bool isEasilyScared;											//	causes the button to become inactive on click (default : false)
		bool isSensitiveToHovering;								//	does the button care when its being hovered over (default : true)
		bool isHandlingEvents;										//	does the button handle events (default : true)

		bool isButtonBordered;									// enables/disables the button border (default : true)
		bool isTextBordered;										//	enables/disables the text border (default : false)
		int buttonBorderSize;										//	how thick is the border? (default : 4)
		int textBorderSize;											//	how thick is the text border (default : 2)

	protected:
		///	Uneditable Attributes
		bool isHovering;												//	is the mouse hovering over the button

	public:
		/// Modifier Methods 
		[[nodiscard]] float getX() const { return rect.x; }
		[[nodiscard]] float getY() const { return rect.y; }
		[[nodiscard]] float getH() const { return rect.h; }
		[[nodiscard]] float getW() const { return rect.w; }

		void generateHitbox() { hitbox.generateHitbox(rect); }
		void setPosition(float newRectY_ = 0, float newRectX_ = 0);
		void setPositionRelativeTo(const Button& papaButton_, float yOffset_ = 0, float xOffset_ = 0);
		void offsetPosition(int newRectYOffset_ = 0, int newRectXOffset_ = 0);
		void setDimensions(int newRectHeight_, int newRectWidth_);
		void setDimensions(const SDL_Rect& rect_);
		void scaleDimensionsIndividually(int newRectHeightScaler_ = 1, int newRectWidthScaler_ = 1);
		void scaleDimensions(int scaler_ = 1);
		void centerPosition(int screenWidth_, int screenHeight_);
		void EnableBackgroundImage(const char* fileDirectory_ = "");
#pragma endregion
#pragma region utility
	protected:
		// ReSharper disable once CppInconsistentNaming
		void ClearSDLStuff() {
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
		//  is the mouse hovering over the button's dimensions? [true/false]
		[[nodiscard]] bool isMouseOver(int mouseX_, int mouseY_) const;
	public:
	
#pragma endregion
	}; }