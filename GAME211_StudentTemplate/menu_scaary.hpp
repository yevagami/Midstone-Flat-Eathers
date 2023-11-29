#include <SDL.h>
#include <random>


/// Constants 
namespace ui {
	//	general clamping
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


//#pragma region shapes
//	extern SDL_Rect SDL_Testangle;
//
//	extern SDL_Rect SDL_Rectangle;
//	extern SDL_Rect SDL_Wide_Rectangle;
//	extern SDL_Rect SDL_Tall_Rectangle;
//	extern SDL_Rect SDL_Square;
//#pragma endregion
//#pragma region colour constants
//	///	Most Colour Constants are courtesy of GPT-3.5
//#pragma region transparency
//	extern SDL_Color SDL_White100;
//	extern SDL_Color SDL_White90;
//	extern SDL_Color SDL_White75;
//	extern SDL_Color SDL_White50;
//	extern SDL_Color SDL_White25;
//	extern SDL_Color SDL_White10;
//#pragma endregion
//	///	"Give me a big list of SDL_Colors"
//#pragma region colours
//	extern SDL_Color SDL_COLOR_NULL;
//	extern SDL_Color SDL_COLOR_ALICE_BLUE;
//	extern SDL_Color SDL_COLOR_AMETHYST;
//	extern SDL_Color SDL_COLOR_ANTIQUE_WHITE;
//	extern SDL_Color SDL_COLOR_APPLE_GREEN;
//	extern SDL_Color SDL_COLOR_APRICOT;
//	extern SDL_Color SDL_COLOR_AQUA;
//	extern SDL_Color SDL_COLOR_AQUAMARINE;
//	extern SDL_Color SDL_COLOR_AZURE;
//	extern SDL_Color SDL_COLOR_AZURE_MIST;
//	extern SDL_Color SDL_COLOR_BALL_BLUE;
//	extern SDL_Color SDL_COLOR_BANANA_YELLOW;
//	extern SDL_Color SDL_COLOR_BATTLESHIP_GREY;
//	extern SDL_Color SDL_COLOR_BEIGE;
//	extern SDL_Color SDL_COLOR_BISQUE;
//	extern SDL_Color SDL_COLOR_BLACK;
//	extern SDL_Color SDL_COLOR_BLANCHED_ALMOND;
//	extern SDL_Color SDL_COLOR_BLUE;
//	extern SDL_Color SDL_COLOR_BLUE_VIOLET;
//	extern SDL_Color SDL_COLOR_BROWN;
//	extern SDL_Color SDL_COLOR_BUBBLES;
//	extern SDL_Color SDL_COLOR_BURLY_WOOD;
//	extern SDL_Color SDL_COLOR_BURNT_ORANGE;
//	extern SDL_Color SDL_COLOR_CADET_BLUE;
//	extern SDL_Color SDL_COLOR_CAMEL;
//	extern SDL_Color SDL_COLOR_CANDY_PINK;
//	extern SDL_Color SDL_COLOR_CARMINE;
//	extern SDL_Color SDL_COLOR_CHARCOAL;
//	extern SDL_Color SDL_COLOR_CHARTREUSE;
//	extern SDL_Color SDL_COLOR_CHERRY;
//	extern SDL_Color SDL_COLOR_CHOCOLATE;
//	extern SDL_Color SDL_COLOR_CITRINE;
//	extern SDL_Color SDL_COLOR_COBALT_BLUE;
//	extern SDL_Color SDL_COLOR_COCOA_BROWN;
//	extern SDL_Color SDL_COLOR_CORAL;
//	extern SDL_Color SDL_COLOR_CORNFLOWER_BLUE;
//	extern SDL_Color SDL_COLOR_CRIMSON;
//	extern SDL_Color SDL_COLOR_CRIMSON_RED;
//	extern SDL_Color SDL_COLOR_CREAM;
//	extern SDL_Color SDL_COLOR_CYAN;
//	extern SDL_Color SDL_COLOR_DARK_BLUE;
//	extern SDL_Color SDL_COLOR_DARK_CYAN;
//	extern SDL_Color SDL_COLOR_DARK_GOLDENROD;
//	extern SDL_Color SDL_COLOR_DARK_GRAY;
//	extern SDL_Color SDL_COLOR_DARK_GREEN;
//	extern SDL_Color SDL_COLOR_DARK_KHAKI;
//	extern SDL_Color SDL_COLOR_DARK_LAVENDER;
//	extern SDL_Color SDL_COLOR_DARK_MAGENTA;
//	extern SDL_Color SDL_COLOR_DARK_OLIVE_GREEN;
//	extern SDL_Color SDL_COLOR_DARK_ORANGE;
//	extern SDL_Color SDL_COLOR_DARK_RED;
//	extern SDL_Color SDL_COLOR_DARK_SALMON;
//	extern SDL_Color SDL_COLOR_DARK_SEA_GREEN;
//	extern SDL_Color SDL_COLOR_DARK_SLATE_BLUE;
//	extern SDL_Color SDL_COLOR_DARK_SLATE_GRAY;
//	extern SDL_Color SDL_COLOR_DARK_TURQUOISE;
//	extern SDL_Color SDL_COLOR_DARK_VIOLET;
//	extern SDL_Color SDL_COLOR_DEEP_LILAC;
//	extern SDL_Color SDL_COLOR_DEEP_PINK;
//	extern SDL_Color SDL_COLOR_DEEP_SKY_BLUE;
//	extern SDL_Color SDL_COLOR_DIM_GRAY;
//	extern SDL_Color SDL_COLOR_DODGER_BLUE;
//	extern SDL_Color SDL_COLOR_DUSK_PINK;
//	extern SDL_Color SDL_COLOR_EGGPLANT_PURPLE;
//	extern SDL_Color SDL_COLOR_EMERALD_GREEN;
//	extern SDL_Color SDL_COLOR_FAWN;
//	extern SDL_Color SDL_COLOR_FIREBRICK;
//	extern SDL_Color SDL_COLOR_FLORAL_WHITE;
//	extern SDL_Color SDL_COLOR_FOREST_BROWN;
//	extern SDL_Color SDL_COLOR_FOREST_GREEN;
//	extern SDL_Color SDL_COLOR_FROST;
//	extern SDL_Color SDL_COLOR_FUCHSIA;
//	extern SDL_Color SDL_COLOR_FUCHSIA_PINK;
//	extern SDL_Color SDL_COLOR_GAINSBORO;
//	extern SDL_Color SDL_COLOR_GHOST_WHITE;
//	extern SDL_Color SDL_COLOR_GOLD;
//	extern SDL_Color SDL_COLOR_GOLDEN_YELLOW;
//	extern SDL_Color SDL_COLOR_GOLDENROD;
//	extern SDL_Color SDL_COLOR_GRAPE_PURPLE;
//	extern SDL_Color SDL_COLOR_GRAY;
//	extern SDL_Color SDL_COLOR_GREEN;
//	extern SDL_Color SDL_COLOR_GREEN_YELLOW;
//	extern SDL_Color SDL_COLOR_HONEYDEW;
//	extern SDL_Color SDL_COLOR_HONEY_BROWN;
//	extern SDL_Color SDL_COLOR_HOT_PINK;
//	extern SDL_Color SDL_COLOR_INDIGO;
//	extern SDL_Color SDL_COLOR_INDIGO_BLUE;
//	extern SDL_Color SDL_COLOR_IVORY;
//	extern SDL_Color SDL_COLOR_JADE_GREEN;
//	extern SDL_Color SDL_COLOR_KHAKI;
//	extern SDL_Color SDL_COLOR_LAVENDER;
//	extern SDL_Color SDL_COLOR_LAVENDER_BLUSH;
//	extern SDL_Color SDL_COLOR_LAVENDER_PURPLE;
//	extern SDL_Color SDL_COLOR_LEMONADE;
//	extern SDL_Color SDL_COLOR_LEMON_CHIFFON;
//	extern SDL_Color SDL_COLOR_LIGHT_BRONZE;
//	extern SDL_Color SDL_COLOR_LIGHT_BLUE;
//	extern SDL_Color SDL_COLOR_LIGHT_CORAL;
//	extern SDL_Color SDL_COLOR_LIGHT_CYAN;
//	extern SDL_Color SDL_COLOR_LIGHT_GOLDENROD_YELLOW;
//	extern SDL_Color SDL_COLOR_LIGHT_GREEN;
//	extern SDL_Color SDL_COLOR_LIGHT_GRAY;
//	extern SDL_Color SDL_COLOR_LIGHT_JASMINE;
//	extern SDL_Color SDL_COLOR_LIGHT_PINK;
//	extern SDL_Color SDL_COLOR_LIGHT_SALMON;
//	extern SDL_Color SDL_COLOR_LIGHT_SEA_GREEN;
//	extern SDL_Color SDL_COLOR_LIGHT_SKY_BLUE;
//	extern SDL_Color SDL_COLOR_LIGHT_SLATE_GRAY;
//	extern SDL_Color SDL_COLOR_LIGHT_STEEL_BLUE;
//	extern SDL_Color SDL_COLOR_LIGHT_YELLOW;
//	extern SDL_Color SDL_COLOR_LIME;
//	extern SDL_Color SDL_COLOR_LIME_GREEN;
//	extern SDL_Color SDL_COLOR_LINEN;
//	extern SDL_Color SDL_COLOR_MARIGOLD;
//	extern SDL_Color SDL_COLOR_MAROON;
//	extern SDL_Color SDL_COLOR_MAUVE;
//	extern SDL_Color SDL_COLOR_MEDIUM_AQUAMARINE;
//	extern SDL_Color SDL_COLOR_MEDIUM_BLUE;
//	extern SDL_Color SDL_COLOR_MEDIUM_ORCHID;
//	extern SDL_Color SDL_COLOR_MEDIUM_PURPLE;
//	extern SDL_Color SDL_COLOR_MEDIUM_SEA_GREEN;
//	extern SDL_Color SDL_COLOR_MEDIUM_SLATE_BLUE;
//	extern SDL_Color SDL_COLOR_MEDIUM_SPRING_GREEN;
//	extern SDL_Color SDL_COLOR_MEDIUM_TURQUOISE;
//	extern SDL_Color SDL_COLOR_MEDIUM_VIOLET_RED;
//	extern SDL_Color SDL_COLOR_MIDNIGHT_BLUE;
//	extern SDL_Color SDL_COLOR_MIDNIGHT_PURPLE;
//	extern SDL_Color SDL_COLOR_MINT_CREAM;
//	extern SDL_Color SDL_COLOR_MOCCASIN;
//	extern SDL_Color SDL_COLOR_MOSS_GREEN;
//	extern SDL_Color SDL_COLOR_MULBERRY;
//	extern SDL_Color SDL_COLOR_MUSTARD_YELLOW;
//	extern SDL_Color SDL_COLOR_NIGHT_BLUE;
//	extern SDL_Color SDL_COLOR_NAVY;
//	extern SDL_Color SDL_COLOR_OCEAN_BLUE;
//	extern SDL_Color SDL_COLOR_OLD_LACE;
//	extern SDL_Color SDL_COLOR_OLIVE;
//	extern SDL_Color SDL_COLOR_OLIVE_DRAB;
//	extern SDL_Color SDL_COLOR_ORANGE;
//	extern SDL_Color SDL_COLOR_ORANGE_PEEL;
//	extern SDL_Color SDL_COLOR_ORANGE_RED;
//	extern SDL_Color SDL_COLOR_ORCHID;
//	extern SDL_Color SDL_COLOR_PALE_GOLDENROD;
//	extern SDL_Color SDL_COLOR_PALE_GREEN;
//	extern SDL_Color SDL_COLOR_PALE_LAVENDER;
//	extern SDL_Color SDL_COLOR_PALE_TURQUOISE;
//	extern SDL_Color SDL_COLOR_PALE_VIOLET_RED;
//	extern SDL_Color SDL_COLOR_PAPAYA_WHIP;
//	extern SDL_Color SDL_COLOR_PEACH_PUFF;
//	extern SDL_Color SDL_COLOR_PEACHY_PINK;
//	extern SDL_Color SDL_COLOR_PERU;
//	extern SDL_Color SDL_COLOR_PINK;
//	extern SDL_Color SDL_COLOR_PERSIMMON;
//	extern SDL_Color SDL_COLOR_PINE_GREEN;
//	extern SDL_Color SDL_COLOR_PINEAPPLE_YELLOW;
//	extern SDL_Color SDL_COLOR_WARM_STREAM;
//	extern SDL_Color SDL_COLOR_COOL_STREAM;
//	extern SDL_Color SDL_COLOR_AMBER_STREAM;
//	extern SDL_Color SDL_COLOR_GOLDEN_STREAM;
//	extern SDL_Color SDL_COLOR_BOOGER_GREEN;
//	extern SDL_Color SDL_COLOR_PLUM;
//	extern SDL_Color SDL_COLOR_POWDER_BLUE;
//	extern SDL_Color SDL_COLOR_PUMPKIN_ORANGE;
//	extern SDL_Color SDL_COLOR_RASPBERRY;
//	extern SDL_Color SDL_COLOR_RED;
//	extern SDL_Color SDL_COLOR_ROBIN_EGG_BLUE;
//	extern SDL_Color SDL_COLOR_ROSIE_BROWN;
//	extern SDL_Color SDL_COLOR_ROSY_BROWN;
//	extern SDL_Color SDL_COLOR_ROYAL_BLUE;
//	extern SDL_Color SDL_COLOR_SADDLE_BROWN;
//	extern SDL_Color SDL_COLOR_POOPSTAIN;
//	extern SDL_Color SDL_COLOR_LAWN_GREEN;
//	extern SDL_Color SDL_COLOR_SALAMANDER;
//	extern SDL_Color SDL_COLOR_SALMON;
//	extern SDL_Color SDL_COLOR_SANDY_BROWN;
//	extern SDL_Color SDL_COLOR_SCARLET_RED;
//	extern SDL_Color SDL_COLOR_SEAFOAM_GREEN;
//	extern SDL_Color SDL_COLOR_SEA_GREEN;
//	extern SDL_Color SDL_COLOR_SEASHELL;
//	extern SDL_Color SDL_COLOR_SILVER;
//	extern SDL_Color SDL_COLOR_SILVER_GREY;
//	extern SDL_Color SDL_COLOR_SKY_BLUE;
//	extern SDL_Color SDL_COLOR_SKY_GREY;
//	extern SDL_Color SDL_COLOR_SLATE_BLUE;
//	extern SDL_Color SDL_COLOR_SLATE_GRAY;
//	extern SDL_Color SDL_COLOR_SNOW;
//	extern SDL_Color SDL_COLOR_SPRING_GREEN;
//	extern SDL_Color SDL_COLOR_SPRUCE;
//	extern SDL_Color SDL_COLOR_STEEL_BLUE;
//	extern SDL_Color SDL_COLOR_STORMY_GREY;
//	extern SDL_Color SDL_COLOR_SUNFLOWER_YELLOW;
//	extern SDL_Color SDL_COLOR_TANGERINE;
//	extern SDL_Color SDL_COLOR_TAN;
//	extern SDL_Color SDL_COLOR_TEAL;
//	extern SDL_Color SDL_COLOR_TERRACOTTA;
//	extern SDL_Color SDL_COLOR_THISTLE;
//	extern SDL_Color SDL_COLOR_TITANIUM;
//	extern SDL_Color SDL_COLOR_TOMATO;
//	extern SDL_Color SDL_COLOR_TOMATO_RED;
//	extern SDL_Color SDL_COLOR_TULIP_PINK;
//	extern SDL_Color SDL_COLOR_TURQUOISE;
//	extern SDL_Color SDL_COLOR_TURQUOISE_BLUE;
//	extern SDL_Color SDL_COLOR_TWILIGHT_BLUE;
//	extern SDL_Color SDL_COLOR_VERMILLION;
//	extern SDL_Color SDL_COLOR_VIOLET;
//	extern SDL_Color SDL_COLOR_VIOLET_RED;
//	extern SDL_Color SDL_COLOR_WHEAT;
//	extern SDL_Color SDL_COLOR_WHITE;
//	extern SDL_Color SDL_COLOR_WINTER_GREY;
//	extern SDL_Color SDL_COLOR_XANADU;
//	extern SDL_Color SDL_COLOR_YELLOW;
//	extern SDL_Color SDL_COLOR_YELLOW_GREEN;
//	extern SDL_Color SDL_COLOR_ZAFFRE;
//	extern SDL_Color SDL_COLOR_ZINNWALDITE;
//	extern SDL_Color SDL_COLOR_ZUCCHINI;
//	extern SDL_Color SDL_COLOR_MARINE_BLUE;
//	extern SDL_Color SDL_COLOR_PEACH;
//	extern SDL_Color SDL_COLOR_STARRY_NIGHT;
//	extern SDL_Color SDL_COLOR_EMERALD;
//	extern SDL_Color SDL_COLOR_COTTON_CANDY;
//	extern SDL_Color SDL_COLOR_OCEAN;
//	extern SDL_Color SDL_COLOR_GOLDEN_SUNSET;
//	extern SDL_Color SDL_COLOR_RUBY_RED;
//	extern SDL_Color SDL_COLOR_MIDNIGHT_SKY;
//	extern SDL_Color SDL_COLOR_LUSH_GREEN;
//	extern SDL_Color SDL_COLOR_TROPICAL_ORANGE;
//	extern SDL_Color SDL_COLOR_SILVER_MIST;
//	extern SDL_Color SDL_COLOR_MYSTIC_PURPLE;
//	extern SDL_Color SDL_COLOR_TEAL_BLUE;
//	extern SDL_Color SDL_COLOR_BUBBLEGUM;
//#pragma endregion
//	///	"Give me a list of SDL_Colors based off appliances"
//#pragma region appliances dlc
//	extern SDL_Color SDL_COLOR_MUG;
//	extern SDL_Color SDL_COLOR_TOASTER;
//	extern SDL_Color SDL_COLOR_SOFA;
//	extern SDL_Color SDL_COLOR_BOOKSHELF;
//	extern SDL_Color SDL_COLOR_TELEVISION;
//	extern SDL_Color SDL_COLOR_PLANT_POT;
//	extern SDL_Color SDL_COLOR_LAMP;
//	extern SDL_Color SDL_COLOR_COMPUTER;
//	extern SDL_Color SDL_COLOR_BED;
//	extern SDL_Color SDL_COLOR_WARDROBE;
//	extern SDL_Color SDL_COLOR_CHAIR;
//	extern SDL_Color SDL_COLOR_FRIDGE;
//	extern SDL_Color SDL_COLOR_OVEN;
//	extern SDL_Color SDL_COLOR_MICROWAVE;
//	extern SDL_Color SDL_COLOR_CUTLERY;
//	extern SDL_Color SDL_COLOR_PLATE;
//	extern SDL_Color SDL_COLOR_CANDLE;
//	extern SDL_Color SDL_COLOR_VASE;
//	extern SDL_Color SDL_COLOR_BLINDS;
//	extern SDL_Color SDL_COLOR_CARPET;
//	extern SDL_Color SDL_COLOR_SHOES;
//	extern SDL_Color SDL_COLOR_FRAME;
//	extern SDL_Color SDL_COLOR_RADIO;
//	extern SDL_Color SDL_COLOR_HEADPHONES;
//	extern SDL_Color SDL_COLOR_BRUSH;
//	extern SDL_Color SDL_COLOR_HAIR_DRYER;
//	extern SDL_Color SDL_COLOR_TOOTHBRUSH;
//	extern SDL_Color SDL_COLOR_WASHING_MACHINE;
//#pragma endregion
//	///	"Give me a list of SDL_Colors based off Minecraft blocks"
//#pragma region minecraft blocks dlc
//	extern SDL_Color SDL_COLOR_ANVIL;
//	extern SDL_Color SDL_COLOR_BARREL;
//	extern SDL_Color SDL_COLOR_BAMBOO;
//	extern SDL_Color SDL_COLOR_BEDROCK;
//	extern SDL_Color SDL_COLOR_BEEHIVE;
//	extern SDL_Color SDL_COLOR_BEE_NEST;
//	extern SDL_Color SDL_COLOR_BELL;
//	extern SDL_Color SDL_COLOR_BLAST_FURNACE;
//	extern SDL_Color SDL_COLOR_CAMPFIRE;
//	extern SDL_Color SDL_COLOR_CHEST;
//	extern SDL_Color SDL_COLOR_COAL_ORE;
//	extern SDL_Color SDL_COLOR_COBBLESTONE;
//	extern SDL_Color SDL_COLOR_COMPOSTER;
//	extern SDL_Color SDL_COLOR_CRAFTING_TABLE;
//	extern SDL_Color SDL_COLOR_DIRT;
//	extern SDL_Color SDL_COLOR_DISPENSER;
//	extern SDL_Color SDL_COLOR_ENCHANTING_TABLE;
//	extern SDL_Color SDL_COLOR_END_PORTAL_FRAME;
//	extern SDL_Color SDL_COLOR_FLETCHING_TABLE;
//	extern SDL_Color SDL_COLOR_FURNACE;
//	extern SDL_Color SDL_COLOR_GOLD_ORE;
//	extern SDL_Color SDL_COLOR_GLASS;
//	extern SDL_Color SDL_COLOR_GRAVEL;
//	extern SDL_Color SDL_COLOR_GRASS_BLOCK;
//	extern SDL_Color SDL_COLOR_GRASS_PATH;
//	extern SDL_Color SDL_COLOR_GRINDSTONE;
//	extern SDL_Color SDL_COLOR_IRON_ORE;
//	extern SDL_Color SDL_COLOR_ICE;
//	extern SDL_Color SDL_COLOR_JUKEBOX;
//	extern SDL_Color SDL_COLOR_LADDER;
//	extern SDL_Color SDL_COLOR_LAPIS_LAZULI_ORE;
//	extern SDL_Color SDL_COLOR_LAVA;
//	extern SDL_Color SDL_COLOR_LILAC;
//	extern SDL_Color SDL_COLOR_LOOM;
//	extern SDL_Color SDL_COLOR_NOTEBLOCK;
//	extern SDL_Color SDL_COLOR_OAK_LEAVES;
//	extern SDL_Color SDL_COLOR_OAK_LOG;
//	extern SDL_Color SDL_COLOR_OBSIDIAN;
//	extern SDL_Color SDL_COLOR_PACKED_ICE;
//	extern SDL_Color SDL_COLOR_PEONY;
//	extern SDL_Color SDL_COLOR_RED_TULIP;
//	extern SDL_Color SDL_COLOR_ROSE_BUSH;
//	extern SDL_Color SDL_COLOR_SAND;
//	extern SDL_Color SDL_COLOR_SANDSTONE;
//	extern SDL_Color SDL_COLOR_SCAFFOLDING;
//	extern SDL_Color SDL_COLOR_SEAGRASS;
//	extern SDL_Color SDL_COLOR_SMITHING_TABLE;
//	extern SDL_Color SDL_COLOR_SOUL_CAMPFIRE;
//	extern SDL_Color SDL_COLOR_STONE;
//	extern SDL_Color SDL_COLOR_STONECUTTER;
//	extern SDL_Color SDL_COLOR_TALL_GRASS;
//	extern SDL_Color SDL_COLOR_TALL_SEAGRASS;
//	extern SDL_Color SDL_COLOR_TORCH;
//	extern SDL_Color SDL_COLOR_WATER;
//	extern SDL_Color SDL_COLOR_WET_SPONGE;
//#pragma endregion
//	///	"Give me a list of SDL_Colors based off Overwatch characters"
//#pragma region overwat dlc
//	// Tank Heroes
//	extern SDL_Color SDL_COLOR_DVA;
//	extern SDL_Color SDL_COLOR_DOOMFIST;
//	extern SDL_Color SDL_COLOR_JUNKER_QUEEN;
//	extern SDL_Color SDL_COLOR_ORISA;
//	extern SDL_Color SDL_COLOR_RAMATTRA;
//	extern SDL_Color SDL_COLOR_REINHARDT;
//	extern SDL_Color SDL_COLOR_ROADHOG;
//	extern SDL_Color SDL_COLOR_SIGMA;
//	extern SDL_Color SDL_COLOR_WINSTON;
//	extern SDL_Color SDL_COLOR_WRECKING_BALL;
//	extern SDL_Color SDL_COLOR_ZARYA;
//
//	// Damage Heroes
//	extern SDL_Color SDL_COLOR_ASHE;
//	extern SDL_Color SDL_COLOR_BASTION;
//	extern SDL_Color SDL_COLOR_CASSIDY;
//	extern SDL_Color SDL_COLOR_ECHO;
//	extern SDL_Color SDL_COLOR_GENJI;
//	extern SDL_Color SDL_COLOR_HANZO;
//	extern SDL_Color SDL_COLOR_JUNKRAT;
//	extern SDL_Color SDL_COLOR_MEI;
//	extern SDL_Color SDL_COLOR_PHARAH;
//	extern SDL_Color SDL_COLOR_REAPER;
//	extern SDL_Color SDL_COLOR_SOJOURN;
//	extern SDL_Color SDL_COLOR_SOLDIER_76;
//	extern SDL_Color SDL_COLOR_SOMBRA;
//	extern SDL_Color SDL_COLOR_SYMMETRA;
//	extern SDL_Color SDL_COLOR_TORBJORN;
//	extern SDL_Color SDL_COLOR_TRACER;
//	extern SDL_Color SDL_COLOR_WIDOWMAKER;
//
//	// Support Heroes
//	extern SDL_Color SDL_COLOR_ANA;
//	extern SDL_Color SDL_COLOR_BAPTISTE;
//	extern SDL_Color SDL_COLOR_BRIGITTE;
//	extern SDL_Color SDL_COLOR_ILLARI;
//	extern SDL_Color SDL_COLOR_KIRIKO;
//	extern SDL_Color SDL_COLOR_LIFEWEAVER;
//	extern SDL_Color SDL_COLOR_LUCIO;
//	extern SDL_Color SDL_COLOR_MERCY;
//	extern SDL_Color SDL_COLOR_MOIRA;
//	extern SDL_Color SDL_COLOR_ZENYATTA;
//#pragma endregion
//#pragma region jail dlc
//	extern SDL_Color SDL_COLOR_ROSE_TOY;
//	extern SDL_Color SDL_COLOR_BAD_DRAGON;
//#pragma endregion
//#pragma endregion
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
		result.r = Clamp(colourA_.r + colourB_.r, 0, 255);
		result.g = Clamp(colourA_.g + colourB_.g, 0, 255);
		result.b = Clamp(colourA_.b + colourB_.b, 0, 255);
		result.a = Clamp(colourA_.a + colourB_.a, 0, 255);
		return result;
	}


	SDL_Color operator-(const SDL_Color& colourA_, const SDL_Color& colourB_) {
		SDL_Color result;
		result.r = Clamp(colourA_.r - colourB_.r, 0, 255);
		result.g = Clamp(colourA_.g - colourB_.g, 0, 255);
		result.b = Clamp(colourA_.b - colourB_.b, 0, 255);
		result.a = Clamp(colourA_.a - colourB_.a, 0, 255);
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