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

class PlayerBody : public Body{

protected:
    class GameManager* game;

public:
    PlayerBody() : Body{} { game = nullptr; }

    // Note the last parameter in this constructor!
    // Look in GameManager.cpp to see how this is called.
    // Look in .cpp file, at Render(), to see why game_ is a parameter.
    PlayerBody(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_,
        GameManager *game_
    ) : Body{
          pos_
        , vel_
        , accel_
        , mass_
        , radius_
        , orientation_
        , rotation_
        , angular_
    }
        , game{ game_ }
    {}
    
    // use the base class versions of getters

    bool OnCreate();
    void HandleEvents( const SDL_Event& event );
    void Update( float deltaTime );
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    void CollisionResponse(float deltaTime, Body* other);
    ~PlayerBody();

private:
    //timers and cooldowns
    Clock* dash_timer = nullptr; //how long the player can dash for
    Clock* dash_cooldown = nullptr; //how long before the player can dash again
    std::vector<Clock*> cooldowns; //list of cooldowns to update

    //dashing variables
    float dashDuration = 0.5f;
    float dashCooldown = 0.3f;

    //movement variables
    Vec3 movement;
    Vec3 playerDirection;
    bool canMove = true;
    float walkSpeed = 100.0f;
    float dashSpeed = 200.0f;
    float currentSpeed;
    float maxSpeed;

    //states
    enum states { idle, walk, dash };
    states currentState;
};

#endif /* PLAYERBODY_H */
