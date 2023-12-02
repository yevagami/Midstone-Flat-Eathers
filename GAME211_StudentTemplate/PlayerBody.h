//
//  PlayerBody.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "Body.h"
#include "GameManager.h"
#include "Clock.h"
#include <vector>
#include "SpriteDefs.h"

class Solid;
class Scene;

class PlayerBody : public Body{
protected:
    Scene* parentScene = nullptr;

public:
 
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
    std::string getSelectedAbility() const;

    //  you know what these are. (getters and setters)
    float getCurrentInvincibilityDuration() const;
    float getDefaultInvincibilityDuration() const;
    void setCurrentInvincibilityDuration(float newDuration_);
    void setCurrentInvincibilityToDefault();
    void setInvincible(const bool state_) { invincible = state_; }

    float getCurrentDrawMeleeDuration() const;
    float getDefaultDrawMeleeDuration() const;
    void setCurrentDrawMeleeDuration(float newDuration_);
    void setCurrentDrawMeleeToDefault();

    float getCurrentDefence() const;
    float getDefaultDefence() const;
    float getMaxDefence() const;
    void setCurrentDefence(float newDefense_);
    void setCurrentDefenceToDefault();


    //state methods
    void state_idle();
    void state_dash(float deltaTime_);
    void state_attack(float deltaTime_);

private:
    //Player abilities enum
    enum abilities { melee, shoot, shield };
    abilities selectedAbilities = melee;

    //  health is managed in Body()

    //Defense/Shield ability related variables
    float playerDefence = 25.0f;
    float playerDefenceDefault = 25.0f;
    float playerDefenceShielded = 75.0f;
    float playerDefenceMax = 100.0f;
    bool drawShield = false;

    //Invincible frames so the player doesn't get hurt every single fram
    float invincibleDuration = 1.5f;
    float invincibleDurationDefault = 1.5f;
    bool invincible = false;

    Sprite playerSpriteSheet;

    //melee variables
    Hitbox* meleeHitbox = nullptr;
    Vec3 mouseDirection = {};
    float meleePower = 50.0f;
    float drawMeleeDuration = 0.3f;
    float drawMeleeDurationDefault = 0.3f;
    bool drawMelee = false; //Draws a sprite to the screen when the player melees

    //shooting variables
    float projectileSpeed = 2500.0f;
    float shootingCooldown = 0.2f;
    float projectilePower = 50.0f;

    //Idk what this is -Adriel
public:
    bool isShielding;
private:

    //timers and cooldowns
    Clock* dash_timer = nullptr; //how long the player can dash for
    Clock* dash_cooldown = nullptr; //how long before the player can dash again
    Clock* shooting_cooldown = nullptr; //how long before the player can shoot again
    Clock* invincible_timer = nullptr; //how long before the player can take damage again
    Clock* drawMelee_timer = nullptr;  //how long the melee sprite would stay on screen for
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
    enum states { idle, dash, attack};
    states currentState = idle;
};

#endif /* PLAYERBODY_H */
