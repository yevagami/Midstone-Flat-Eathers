#ifndef BODY_H
#define BODY_H

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Hitbox.h"

using namespace MATH;


class Body {
public:
    Body();

	Body(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_ = 1.0f,
        float radius_ = 0.0f,
        float orientation_ = 0.0f,
        float rotation_ = 0.0f,
        float angular_ = 0.0f
    );

    void LoadHitbox(float w_, float h_);
    void UpdateHitbox(Matrix4 projectionMat);
	[[nodiscard]] Hitbox getHitbox() const { return hitbox; }
	virtual ~Body();
    virtual void Update(float deltaTime);
    virtual void ApplyForce(Vec3 force_);
    virtual Vec3 getPos() { return pos; }
    virtual Vec3 getVel() { return vel; }
    virtual Vec3 getAccel() { return accel; }
    virtual float getMass() { return mass; }
    virtual float getOrientation() { return orientation; }
    virtual float getRotation() { return rotation; }
    virtual float getAngular() { return angular; }

    virtual void setImage(SDL_Surface* image_) { image = image_; }
    virtual SDL_Surface* getImage() { return image; }

    virtual void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_){ imageSizeWorldCoords = imageSizeWorldCoords_; }

    virtual void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    virtual SDL_Texture* getTexture() { return texture; }

    virtual void HandleEvents( const SDL_Event& event );

	// Added this as public to deal with my demo
	// so that mouse position can be copied into a Body.
    virtual void setPos( Vec3 pos );

    virtual void Render(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale = 1.0f);
    void RenderHitbox(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale = 1.0f);


protected:
    // inherited classes can access this
    Vec3 pos;
    Vec3 vel;
    Vec3 accel;
    float mass;
    float radius;           // for getting near walls
    float orientation;		// facing this direction
    float rotation;			// rotating at this speed (radians per second?)
    float angular;          // angular acceleration

    Hitbox hitbox;

    Vec3 imageSizeWorldCoords;
    SDL_Surface* image;
    SDL_Texture* texture;
};


#endif /* BODY_H */