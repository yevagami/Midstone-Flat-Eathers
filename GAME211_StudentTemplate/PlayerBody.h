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
#include "SpriteDefs.h"

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
        type = PLAYER;
    }

    // use the base class versions of getters
    //Fundamental methods (create, update, handle input, render, destroy, collisions)
    bool OnCreate();
    void HandleEvents( const SDL_Event& event ) override;
    void Update( float deltaTime ) override;
    void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_) override;
    void RenderHitbox(SDL_Renderer* renderer_) override;
    void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    void OnDestroy() override;
    ~PlayerBody();

    //Extra methods
    void updateMouseDir();
    void updateMeleeHitbox();
    void takeDamage(float amount) override;

    //state methods
    void state_idle();
    void state_walk();
    void state_dash(float deltaTime);
    void state_attack();

private:
    //Player abilities
    enum abilities { melee, shoot, shield };
    abilities selectedAbilities = melee;

    //Player variables
    float maxPlayerHealth = 250.0f;
    float playerDefense = 25.0f;
    float invincibleDuration = 1.5f;
    bool invincible = false;
    Sprite playerSpriteSheet;

    //melee variables
    Hitbox* meleeHitbox = nullptr;
    Vec3 mouseDirection = {};
    float meleePower = 50.0f;

    //shooting variables
    float projectileSpeed = 2500.0f;
    float shootingCooldown = 0.2f;
    float projectilePower = 50.0f;

    //timers and cooldowns
    Clock* dash_timer = nullptr; //how long the player can dash for
    Clock* dash_cooldown = nullptr; //how long before the player can dash again
    Clock* shooting_cooldown = nullptr;
    Clock* invincible_timer = nullptr;
    std::vector<Clock*> cooldowns; //list of cooldowns to update

    //dashing variables
    float dashDuration = 0.2f;
    float dashCooldown = 0.3f;

    //movement variables
    Vec3 movement = {};
    Vec3 playerDirection = {};
    bool canMove = true;
    float walkSpeed = 800.0f;
    float dashSpeed = 1500.0f;
    float currentSpeed = 0.0f;
    float maxSpeed = 0.0f;

    //states
    enum states { idle, walk, dash, attack};
    states currentState = idle;
};

#endif /* PLAYERBODY_H */
