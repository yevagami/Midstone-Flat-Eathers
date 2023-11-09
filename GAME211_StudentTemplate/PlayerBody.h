//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include "Clock.h"
#include <vector>
class Scene;

class PlayerBody : public Body{
protected:
    Scene* parentScene = nullptr;

public:
    //Constructors
    PlayerBody() {}

    //Constructor requiring the bare minimum to make the player function (the player's texture is set internally)
    PlayerBody(Scene* parentScene_, Vec3 pos_, Vec3 scale_, int w_, int h_) {
        parentScene = parentScene_;
        pos = pos_;
        scale = scale_;
        Body::LoadHitbox(w_, h_);
        type = player;
    }

    // use the base class versions of getters
    //Fundamental methods (create, update, handle input, render, destroy, collisions)
    bool OnCreate();
    void HandleEvents( const SDL_Event& event ) override;
    void Update( float deltaTime ) override;
    void RenderHitbox(SDL_Renderer* renderer_) override;
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    void OnDestroy() override;
    ~PlayerBody();

private:
    //melee hitbox
    Hitbox* meleeHitbox = nullptr;

    //timers and cooldowns
    Clock* dash_timer = nullptr; //how long the player can dash for
    Clock* dash_cooldown = nullptr; //how long before the player can dash again
    std::vector<Clock*> cooldowns; //list of cooldowns to update

    //dashing variables
    float dashDuration = 0.15f;
    float dashCooldown = 0.3f;

    //movement variables
    Vec3 movement = {};
    Vec3 playerDirection = {};
    bool canMove = true;
    float walkSpeed = 100.0f;
    float dashSpeed = 1000.0f;
    float currentSpeed = 0.0f;
    float maxSpeed = 0.0f;

    //states
    enum states { idle, walk, dash, melee, shooting };
    states currentState = idle;
};

#endif /* PLAYERBODY_H */
