#include "Scene1.h"

using namespace ui;


//a global var. My problem was that i defined it in the Scene 3 again, that made a linking error.
//IMPORTANT!!!
#include "EntityMap.h"
EntityMap eMap; //not member of scene1 class




// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;


		///	button time

	auto BUTTON_BACKGROUND = ui::SDL_COLOR_MYSTIC_PURPLE; auto BUTTON_TEXT = ui::SDL_COLOR_BLACK; auto rectangle = SDL_Rect{ 0,0,325,75 }; auto square = ui::SDL_Square;
	auto BUTTON_HOVERBACKGROUND = ui::SDL_COLOR_GRAY; auto BUTTON_BORDER = SDL_COLOR_DARK_GRAY;
	auto TEXT_TEXT = ui::SDL_COLOR_ROSE_TOY;

		///	Step 1: Create the Buttons with Initial Values

	myJankyText = new Button(Font{ "ur amazing<3", 100, fontMap.at("lobster") }, {}, Colour{ SDL_COLOR_NULL, TEXT_TEXT, SDL_COLOR_NULL });
	myJankySubText = new Button(Font{ "stunning!", 25, fontMap.at("comic serif"),0,0,-45.0 }, {}, Colour{ SDL_COLOR_NULL, TEXT_TEXT, SDL_COLOR_NULL });
	myCreditingText = new Button(Font{ "Adriel, Michael, Diana, and Helen", 25, fontMap.at("comic serif") }, {}, Colour{ SDL_COLOR_NULL, TEXT_TEXT, SDL_COLOR_NULL });

	myStartButton = new Button(	//	
		Font{ "start", 50, fontMap.at("comic serif") },
		rectangle, Colour{BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND});

	myOptionsButton = new Button(	//	
		Font{ "options", 50, fontMap.at("comic serif") },
		rectangle,
		Colour{ BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND });

	myExitButton = new Button(	//	
		Font{ "exit", 50, fontMap.at("comic serif") },
		rectangle,
		Colour{ BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND });

	mySmallButton = new Button(	//
		Font{ ":)", 55, fontMap.at("comic serif"),0,0,90 },
		square,
		Colour{ BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND });

	myDebugButton = new Button(
		Font{ "D:<", 55, fontMap.at("ransom"), 0,0,-90 },
		square,
		Colour{ BUTTON_BACKGROUND, BUTTON_TEXT, BUTTON_BORDER, BUTTON_HOVERBACKGROUND });

	mySpookyButton = new Button(
		Font{ "boo!", 75, fontMap.at("gothic") },
		square, Colour{ SDL_COLOR_NULL, SDL_COLOR_SCARLET_RED, BUTTON_BORDER, BUTTON_HOVERBACKGROUND}, 0);


	//	grouping for mass attrbute changing, deleting and rendering
	allButtons.emplace_back(myJankyText);	allButtons.emplace_back(myJankySubText); allButtons.emplace_back(myCreditingText); //	text
	allButtons.emplace_back(myStartButton);
	allButtons.emplace_back(myOptionsButton);
	allButtons.emplace_back(myExitButton);	//	lowkey the layering (who's rendered on top)
	allButtons.emplace_back(mySmallButton);
	allButtons.emplace_back(myDebugButton);
	allButtons.emplace_back(mySpookyButton);

	//1.1 individial changes before grouping
	mySmallButton->scaleDimensions(50);
	myDebugButton->scaleDimensions(55);

	myDebugButton->isPrideful = true;		//	changes colour on click
	mySmallButton->isPrideful = true;		//	changes colour on click
	myStartButton->isTogglable = true;//becomes inactive on click (it scurries away)
	myExitButton->isTogglable = true;	//becomes inactive on click (it runs away)
	myOptionsButton->isTogglable = true;	//	becomes togglablable (use button->isOn for the state)

	myJankyText->textColour = myJankyText->textColour << SDL_White75;
	myJankySubText->textColour = myJankySubText->textColour << SDL_White50; //	applying the transparency onto the colour
	myCreditingText->textColour = myCreditingText->textColour << SDL_White10;
	
	//sub buttons
	mySpookyButton->scaleDimensions(95);
	mySpookyButton->isActive = false;


	///	Step 2: Aesthetics

	for (auto* button : allButtons) {
		button->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	myJankyText->offsetPosition(-300);	//	offsets the text up
	myJankySubText->setPositionRelativeTo(*myJankyText, 50, 280);
	myCreditingText->setPosition(20, 230);

	myStartButton->offsetPosition(-150);	//	offsets the start button 150 units vertically (up)
	myOptionsButton->offsetPosition(); //doesn't move the button (can take no parameters)
	myExitButton->offsetPosition(+150);	//	offsets the exit button 150 units vertically (down)

	mySpookyButton->offsetPosition(0, 350);

	//	cornering 
	mySmallButton->setPosition(SCREEN_HEIGHT - mySmallButton->getH(), SCREEN_WIDTH - mySmallButton->getW()); //	places the square button into the top corner
	myDebugButton->setPosition(0, SCREEN_WIDTH - myDebugButton->getW()); //	places the square button into the bottom corner

	isBopping = true;
}


Scene1::~Scene1() = default;


bool Scene1::OnCreate() {
#pragma region SDL Window Stuff
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
#pragma endregion
	name = "scene1"; // we dont need that 
				//	ew^


	//		button showcase
	///	step 3: Hitbox and OnLeftClick

	for (auto* button : allButtons) { button->generateHitbox(); } //	we're going this in the OnCreate because the hitbox needs to be generated after repositioning. this ensures that

	//	what happens when each button is clicked?
	//myStartButton->SetOnLeftClick([&] {
	//	cc.log(update, "start pressed"); sound.playSound("flame", false);});
	//myOptionsButton->SetOnLeftClick([&] {cc.log(update, "options pressed");sound.playSound("flame", false); bTestMenu = !bTestMenu; });
	//myExitButton->SetOnLeftClick([&] {cc.log(update, "exit pressed");sound.playSound("big powerup", false); isBopping = !isBopping; });
	//mySmallButton->SetOnLeftClick([&] {cc.log(update, "small pressed");sound.playSound("my bike", false); });
	//myDebugButton->SetOnLeftClick([&] {cc.log(update, "debug pressed | back from the dead!");sound.playSound("gyat"); for (auto const button : allButtons) { button->isActive = true; }});

	//mySpookyButton->SetOnLeftClick([&] {cc.log(update, "spooky aahhhH!");sound.playSound("oops", true); });


	//myStartButton->SetOnRightClick([&] {cc.log(update, "start RIGHT CLICKED!!!!!!!!!!!!!!!!!!!!!"); });
	//myStartButton->SetOnHover([&] {cc.log(update, "start hOOoOoVErrRRrrrRing"); });
	//myStartButton->SetOnScroll([&](int xxx) {cc.log(update, "start scrolled on (rekt ig)"); cout << xxx << endl; });


	return true;
}


void Scene1::OnDestroy() {
	for (auto* button : allButtons) { delete button; }
}


void Scene1::Update(const float deltaTime) {
	// Update player
	//game->getPlayer()->Update(deltaTime);
	if (bTestMenu) {
		mySpookyButton->isActive = true;
	} else {
		mySpookyButton->isActive = false;
	}




}


void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//	render the buttons
	for (auto* button : allButtons) { button->Render(renderer); }


	SDL_RenderPresent(renderer); }


void Scene1::HandleEvents(const SDL_Event& event) {
	PrettyPrinting::printMouseCoords(event);
	for (const auto button : allButtons) { button->HandleEvents(event); }



	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);

#pragma region debuggingKeys
	if (event.key.keysym.sym == SDLK_u && event.type == SDL_KEYDOWN) {
		///	CONSOLE TESTING
		//	console messages display: how to call the method
		cc.log(error, "error: this is an error message");
		cc.log(warning, "warning: this is a warning message");
		cc.log(update, "update: this is an update message");
		cc.log(not_error, "this is not an error");
	}


	if (event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN) {
		using namespace ui;

		cc.log(update, "toggling all button visibility");
		for(auto button : allButtons) {
			bool state = button->isActive;
			button->isActive = !state; }

	}


	if (event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN) {
	}


	if (event.key.keysym.sym == SDLK_n && event.type == SDL_KEYDOWN) {
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("dog")));
		PrettyPrinting::printVS(eMap.findEntitiesByData(string("meow")));
	}


	if (event.key.keysym.sym == SDLK_m && event.type == SDL_KEYDOWN) {
		///	ENTITY MAP TESTING
		//	to insert into an entit map...
		eMap.insertEntity(string("rex"), string("is my dog"));
		eMap.insertEntity(string("deedee"), string("was my dog ;-;"));
		eMap.insertEntity(string("turnip"), string("is my cat"));
		eMap.insertEntity(string("adriel"), string("is adriel"));
		//	DELETING the test entity
		eMap.removeEntity(string("test"));
		//	printing...
		PrettyPrinting::printEM(eMap);
		//	to serialize that entity map...
		eMap.saveEntityMapToFile("SaveData/entitymap.txt");
	}
#pragma endregion
}
