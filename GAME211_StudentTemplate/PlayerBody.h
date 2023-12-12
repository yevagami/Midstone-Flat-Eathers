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
#include "Animation.h"

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
    float getCurrentInvincibilityDuration() const { return invincible_timer->duration; }
    float getDefaultInvincibilityDuration() const { return invincibleDurationDefault;}
    void setCurrentInvincibilityDuration(const float newDuration_) {
        invincibleDuration = newDuration_;//just in case
        invincible_timer->duration = invincibleDuration;
    }
    void setCurrentInvincibilityToDefault() {
        invincibleDuration = invincibleDurationDefault;
        invincible_timer->duration = invincibleDuration;
    }
    void setInvincible(const bool state_) { invincible = state_; }

    float getCurrentDrawMeleeDuration() const { return drawAttack_timer->duration; }
    float getDefaultDrawMeleeDuration() const { return drawMeleeDurationDefault; }
    void setCurrentDrawMeleeDuration(const float newDuration_) {
        drawAttackDuration = newDuration_;	//just in case
        drawAttack_timer->duration = drawAttackDuration;
    }
    void setCurrentDrawMeleeToDefault() {
        drawAttackDuration = drawMeleeDurationDefault;	//	just in case
        drawAttack_timer->duration = drawAttackDuration;
    }

    float getCurrentDefence() const { return playerDefence;}
    float getDefaultDefence() const { return playerDefenceDefault; }
    float getMaxDefence() const { return playerDefenceMax; }
    void setCurrentDefence(const float newDefense_) { playerDefence = newDefense_;}
    void setCurrentDefenceToDefault() { playerDefence = playerDefenceDefault;}

    float getCurrentMeleeDamage() const { return meleePowerCurrent; }
    float getDefaultMeleeDamage() const { return meleePowerDefault; }
    void setCurrentMeleeDamage(const float newMeleeDamage_) {  meleePowerCurrent = newMeleeDamage_; }
    void setCurrentMeleeDamageToDefault() {  meleePowerCurrent = meleePowerDefault; }
	float getCurrentProjectileDamage() const { return projectilePowerCurrent; }
	float getDefaultProjectileDamage() const { return projectilePowerDefault; }
    void setCurrentProjectileDamage(const float newProjectileDamage_) {  projectilePowerCurrent = newProjectileDamage_; }
    void setCurrentProjectileDamageToDefault() {  projectilePowerCurrent = projectilePowerDefault; }
    void AddHealth(float amount) {
        currentHealth += amount;
        if (currentHealth > maxHealth) {
            currentHealth = maxHealth;
        }
    }

    //state methods
    void state_idle();
    void state_dash(float deltaTime_);
    void state_attack(float deltaTime_);

    //Public variables
    bool isShielding = false;
    int killCount = 0;
    int points = 0;

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

    //Sprite stuff
    Sprite playerSpriteSheet;
    Sprite effectSpriteSheet;
    SDL_Rect currentSprite;
    int currentSpriteIndex = 0;
    float frameInterval = 0.5f;
    float currentIntervalTimer = 0.0f;

    //animations
    AnimationController* animController;
    AnimationController* attackAnimController;

    //Standing animations
    Animation anim_up;
    Animation anim_down;
    Animation anim_left;
    Animation anim_right;

    //Walking animations
    Animation anim_walk_up;
    Animation anim_walk_down;
    Animation anim_walk_left;
    Animation anim_walk_right;

    //Attack animations
    Animation anim_slash;
    Animation anim_sword;
    Animation anim_shoot;
    Animation anim_gun;
    Animation anim_shield;
    SDL_Rect* attackAnimCutout = nullptr;
    void LoadAnimations();

    //melee variables
    Hitbox* meleeHitbox = nullptr;
    Vec3 mouseDirection = {};
    float meleePowerCurrent = 50.0f;
    float meleePowerDefault = 50.0f;
    float drawAttackDuration = 0.6f;
    float drawMeleeDurationDefault = 0.6f;
    bool drawAttack = false; //Plays the respective attack animation for a set duration of time

    //shooting variables
    float projectileSpeed = 2500.0f;
    float shootingCooldown = 0.2f;
    float projectilePowerCurrent = 50.0f;
    float projectilePowerDefault = 50.0f;

    //timers and cooldowns
    Clock* dash_timer = nullptr; //how long the player can dash for
    Clock* dash_cooldown = nullptr; //how long before the player can dash again
    Clock* shooting_cooldown = nullptr; //how long before the player can shoot again
    Clock* invincible_timer = nullptr; //how long before the player can take damage again
    Clock* drawAttack_timer = nullptr;  //how long the attack animation would stay on screen for
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
