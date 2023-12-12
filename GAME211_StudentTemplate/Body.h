#pragma once
#ifndef BODY_H
#define BODY_H
#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Hitbox.h"
#include "SpriteDefs.h"

using namespace MATH;
struct Transform {
	Vec3 bodyPosition;
	Vec3 bodyVelocity;
	Vec3 bodyAcceleration;

	float bodyMass;
	float bodyRadius;
	float bodyOrientation;
	float bodyRotation;
	float bodyAngular;

	Transform(
		const Vec3& pos_ = Vec3(0, 0, 0), const Vec3& vel_ = Vec3(0, 0, 0), const Vec3& accel_ = Vec3(0, 0, 0),
		const float mass_ = 1.0f,
		const float radius_ = 0.0f,
		const float orientation_ = 0.0f,
		const float rotation_ = 0.0f,
		const float angular_ = 0.0f)
		: bodyPosition(pos_), bodyVelocity(vel_), bodyAcceleration(accel_),
		  bodyMass(mass_), bodyRadius(radius_), bodyOrientation(orientation_), bodyRotation(rotation_),
		  bodyAngular(angular_) {}
};

class Level;
class Body {
public:
	//Enum for body types
	enum TYPE{
		BODY = 0, 
		SOLID = 1, 
		PROJECTILE = 2, 
		PLAYER = 3,
		ENEMY = 4,
		DROP = 5
	};
	TYPE type = BODY;

	Body(
		Vec3 pos_, Vec3 vel_ = Vec3(0, 0, 0), Vec3 accel_ = Vec3(0, 0, 0),
		float mass_ = 1.0f,
		float radius_ = 0.0f,
		float orientation_ = 0.0f,
		float rotation_ = 0.0f,
		float angular_ = 0.0f
	);
	//	Constructor 2: (list initializer edition)
	// ReSharper disable once CppPossiblyUninitializedMember
	Body(
		const Transform& transform_ = Transform{})
	  : image(nullptr), texture(nullptr) {
		//	make it so that textures can be passed and automatically applied (ease of use)
		//	maybe move the projection matrix here..?
		pos = transform_.bodyPosition;
		vel = transform_.bodyVelocity;
		accel = transform_.bodyAcceleration;
		mass = transform_.bodyMass;
		radius = transform_.bodyRadius;
		orientation = transform_.bodyOrientation;
		rotation = transform_.bodyRotation;
		angular = transform_.bodyAngular;
	}
	//Basic body constuctor containing everything we need to make it work (pos, scale, hitbox w&h, texture)
	Body(
		Level* parentLevel_,
		Vec3 pos_,
		Vec3 scale_,
		int w_,
		int h_,
		SDL_Surface* image_
	);


	//Fundamental methods (create, update, handle input, render, destroy, collisions)
	void LoadHitbox(float w_, float h_);
	virtual void Update(float deltaTime);
	virtual void HandleEvents(const SDL_Event& event_);
	virtual void Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_);
	virtual void RenderHitbox(SDL_Renderer* renderer_);
	virtual void OnCollide(Body* other, float deltaTime) { return; }
	virtual void OnDestroy();
	virtual ~Body() {}

	//Getters and setters
	[[nodiscard]] Hitbox* getHitbox() const { return hitbox; }
	virtual void ApplyForce(Vec3 force_);
	virtual Vec3 getPos() { return pos; }
	virtual Vec3 getVel() { return vel; }
	void setVel(Vec3 vel_) { vel = vel_; }
	virtual Vec3 getAccel() { return accel; }
	virtual float getMass() { return mass; }
	virtual float getOrientation() { return orientation; }
	virtual float getRotation() { return rotation; }
	virtual float getAngular() { return angular; }
	Level* getParentLevel() const { return parentLevel; }
	void setParentLevel(Level* parentLevel_) { parentLevel = parentLevel_; }
	float getCurrentHealth() const { return currentHealth; }
	float getMaxHealth() const { return maxHealth; }
	void setCurrentHealth(float newHealth) { currentHealth = newHealth; }
	void setCurrentHealthToMax() { currentHealth = maxHealth; }
	void setCurrentHealthToDefault() { currentHealth = defaultHealth; }

	//Texture related methods
	virtual void setImage(SDL_Surface* image_) { image = image_; }
	virtual SDL_Surface* getImage() { return image; }
	virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
	virtual SDL_Texture* getTexture() { return texture; }

	//Extra methods
	// Added this as public to deal with my demo
	// so that mouse position can be copied into a Body.
	void setPos(Vec3 pos_) { pos = pos_; }
	virtual void takeDamage(float amount) { return; }
	void setCutout(SDL_Rect* cutout_) { cutout = cutout_; } //Sets the SRect when rendering from a larger sprite sheet

protected:
	// inherited classes can access this
	Level* parentLevel = nullptr;

	//Body variables
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);
	const float maxHealth = 200;
	float defaultHealth = 200;
	float currentHealth = 200;
	float mass;
	float radius; // for getting near walls
	float orientation; // facing this direction
	float rotation; // rotating at this speed (radians per second?)
	float angular; // angular acceleration
	bool destroyFlag = false; //Bool that will self report iself to the trashBodies vector to remove itself from the level
	Hitbox* hitbox;
	Transform transform;	//	constructor list struct



	//Texture stuff
	SDL_Surface* image = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect* cutout = nullptr;
};


#endif /* BODY_H */
