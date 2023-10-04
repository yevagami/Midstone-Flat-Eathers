#include "Body.h"

Body::Body() {
    pos = Vec3();
    vel = Vec3();
    accel = Vec3();
	mass = 1.0f;
    radius = 0.0f;
    orientation = 0.0f;
    rotation = 0.0f;
    angular = 0.0f;

	image = nullptr;
}

Body::Body (
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_,
    float radius_ = 0.0f,
    float orientation_ = 0.0f,
    float rotation_ = 0.0f,
    float angular_ = 0.0f
)
{
    pos = pos_;
    vel = vel_;
    accel = accel_;
    mass = mass_;
    radius = radius_;
    orientation = orientation_;
    rotation = rotation_;
    angular = angular_;

    image = nullptr;
}

void Body::LoadHitbox(float w_, float h_) {
    hitbox.w = w_;
    hitbox.h = h_;
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}

Body::~Body()
{}

void Body::ApplyForce( Vec3 force_ ) {
    accel = force_ / mass;
}


void Body::Update( float deltaTime ) {
    vel = vel + accel * deltaTime;
    pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
    
    // Update orientation
    orientation += rotation * deltaTime;
    rotation += angular * deltaTime;

    //Update hitbox position
    hitbox.x = pos.x;
    hitbox.y = pos.y;
}


void Body::HandleEvents( const SDL_Event& event ) {
    
    //  michael- i'm moving this stuff. imma make a keybinds class for global keybinds, then u can just do "keybindHandler.HandleEvents(event)"
    //              - its mostly for stuff like escape = quit, mouse input tracking, etc. WE'LL SEE HOW IT GOES!
    if ( event.type == SDL_MOUSEBUTTONDOWN ){
        printf("Mousedown\n");
    }
    if ( event.type == SDL_KEYDOWN ){
        if ( event.key.keysym.scancode == SDL_SCANCODE_SPACE){
            printf("Space\n");
        }
    }
    // etc
}

void Body::setPos( Vec3 pos_ ){
    pos = pos_;
}


void Body::Render(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale){
    SDL_Rect square;
    Vec3 screenCoords;
    float w, h;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Scale the image, in case the .png file is too big or small
    w = image->w * scale;
    h = image->h * scale;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
}
