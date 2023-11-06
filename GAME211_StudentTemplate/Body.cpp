#include "Body.h"
#include "Scene.h"

//Body::Body() {
//    pos = Vec3();
//    vel = Vec3();
//    accel = Vec3();
//	mass = 1.0f;
//    radius = 0.0f;
//    orientation = 0.0f;
//    rotation = 0.0f;
//    angular = 0.0f;
//
//	image = nullptr;
//}

Body::Body (
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_,
    float radius_,
    float orientation_,
    float rotation_,
    float angular_
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

void Body::OnDestroy() {
    SDL_DestroyTexture(texture);
    texture = nullptr;

    delete hitbox;
    hitbox = nullptr;

    parentScene = nullptr;
}

Body::Body(Scene* parentScene_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_){
    parentScene = parentScene_;
    pos = pos_;
    scale = scale_;
    LoadHitbox(w_ * scale_.x, h_ * scale_.y);
    image = image_;
    texture = SDL_CreateTextureFromSurface(parentScene->getRenderer(), image);
}

void Body::LoadHitbox(float w_, float h_) {
    hitbox = new Hitbox(w_, h_, pos.x, pos.y);
}

void Body::ApplyForce( Vec3 force_ ) {
    accel = force_ / mass;
}

void Body::Update( float deltaTime ) {
    vel = vel + accel * deltaTime;
    pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
    
    // Update orientation
    orientation += rotation * deltaTime;
    rotation += angular * deltaTime;

    //Updates the hitbox's position based on the projection matrix
    if (parentScene == nullptr) { //guard clause, exits the function early 
        std::cout << "Parent scene is not set";
        return; 
    }

    if (hitbox == nullptr) { return; }
    Matrix4 projectionMat = parentScene->getProjectionMatrix();
    Vec3 hitboxPos = projectionMat * pos;
    hitbox->x = hitboxPos.x - hitbox->w * 0.5f;
    hitbox->y = hitboxPos.y - hitbox->h * 0.5f;
}


void Body::HandleEvents( const SDL_Event& event_ ) {
    
    //  michael- i'm moving this stuff. imma make a keybinds class for global keybinds, then u can just do "keybindHandler.HandleEvents(event)"
    //              - its mostly for stuff like escape = quit, mouse input tracking, etc. WE'LL SEE HOW IT GOES!
    if ( event_.type == SDL_MOUSEBUTTONDOWN ){
        printf("Mousedown\n");
    }
    if ( event_.type == SDL_KEYDOWN ){
        if ( event_.key.keysym.scancode == SDL_SCANCODE_SPACE){
            printf("Space\n");
        }
    }
    // etc
}

void Body::setPos( Vec3 pos_ ){
    pos = pos_;
}


void Body::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){
    //Failsafe incase the programmer forgets to add a texture to the body
    if (texture == nullptr) {
        texture = SDL_CreateTextureFromSurface(renderer_, IMG_Load("Textures/programmer_art/missing_texture.png"));
        std::cout << "You forgot a texture\n";
    }

    SDL_Rect square;
    Vec3 screenCoords;
    float w, h;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix_ * pos;

    // Scale the image, in case the .png file is too big or small
    w = image->w * scale.x;
    h = image->h * scale.y;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    //square.x = static_cast<int>(pos.x - 0.5f * w);
    //square.y = static_cast<int>(pos.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer_, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
}

void Body::RenderHitbox(SDL_Renderer* renderer_){
    SDL_Rect box;

    box.x = static_cast<int>(hitbox->x);
    box.y = static_cast<int>(hitbox->y);
    box.w = static_cast<int>(hitbox->w);
    box.h = static_cast<int>(hitbox->h);

    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer_, &box);
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}