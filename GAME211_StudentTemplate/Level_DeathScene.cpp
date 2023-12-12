#include "Level_DeathScreen.h"


std::string Level_DeathScreen::randomizeDeathMessage() {
    int totalCases = 4;

    std::mt19937 rng(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<int> distribution(1, totalCases);

    switch (int randomNum = distribution(rng)) {
    case 1:
        return "trash lmao.";
    case 2:
        return "don't cry now...";
    case 3:
        return "big death for a small man";
    case 4:
        return "maybe next time, or maybe not";
    default:
        return "game over";
    }

}

bool Level_DeathScreen::OnCreate() {

    name = "Gameover";
    isDeathScreenHere = true;

    deathText = new Button(Font{ "default", 75 });

    deathText->centerPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
    deathText->offsetPosition(-100);
    deathText->textColour = SDL_COLOR_ROSE_TOY;

    return true;
}


void Level_DeathScreen::OnDestroy() {

    delete deathText;



    //Destroys everything except the player
    for (Body* body : levelBodies) {
        if (body->type == body->PLAYER) {
            body = nullptr;
            continue;
        }
        body->OnDestroy();
        delete body;
    }

    levelBodies.clear();
}


void Level_DeathScreen::Update(const float time_) {

    if (isDeathScreenHere) {
        isDeathScreenHere = false;
        deathString = randomizeDeathMessage();
        cc.log(debug, "death text is ", deathString);
        deathText->text = deathString;
    }


}

void Level_DeathScreen::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) {


    deathText->Render(renderer_);

}

void Level_DeathScreen::HandleEvents(const SDL_Event& event_) {

    deathText->HandleEvents(event_);

}
