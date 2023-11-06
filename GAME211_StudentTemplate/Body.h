#pragma once
#ifndef BODY_H
#define BODY_H
#include <SDL.h>
#include <MMath.h>
#include "Hitbox.h"


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

class Scene;
class Body {
private:
	//The scene where this body belongs to
	Scene* parentScene = nullptr;

public:
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
		Scene* parentScene_,
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
	virtual Vec3 getAccel() { return accel; }
	virtual float getMass() { return mass; }
	virtual float getOrientation() { return orientation; }
	virtual float getRotation() { return rotation; }
	virtual float getAngular() { return angular; }
	Scene* getParentScene() { return parentScene; }
	void setParentScene(Scene* parentScene_) { parentScene = parentScene_; }

	//Texture related methods
	virtual void setImage(SDL_Surface* image_) { image = image_; }
	virtual SDL_Surface* getImage() { return image; }
	virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
	virtual SDL_Texture* getTexture() { return texture; }
	virtual void setImageSizeWorldCoords(const Vec3& imageSizeWorldCoords_) { imageSizeWorldCoords = imageSizeWorldCoords_; }
	
	// Added this as public to deal with my demo
	// so that mouse position can be copied into a Body.
	virtual void setPos(Vec3 pos_);

protected:
	// inherited classes can access this
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Vec3 scale = Vec3(1.0f, 1.0f, 1.0f);
	float mass;
	float radius; // for getting near walls
	float orientation; // facing this direction
	float rotation; // rotating at this speed (radians per second?)
	float angular; // angular acceleration

	Hitbox* hitbox;
	Transform transform;	//	constructor list struct

	Vec3 imageSizeWorldCoords;
	SDL_Surface* image = nullptr;
	SDL_Texture* texture = nullptr;
};


#endif /* BODY_H */
