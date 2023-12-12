#include "Body.h"
#include "Level.h"

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


Body::Body(Level* parentLevel_, Vec3 pos_, Vec3 scale_, int w_, int h_, SDL_Surface* image_){
    parentLevel = parentLevel_;
    pos = pos_;
    scale = scale_;
    LoadHitbox(w_ * scale_.x, h_ * scale_.y);
    image = image_;
    texture = SDL_CreateTextureFromSurface(parentLevel->getParentScene()->getRenderer(), image);
}

void Body::OnDestroy() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
  
    if (image) {
        SDL_FreeSurface(image);
        image = nullptr;
    }

    delete hitbox;

    cutout = nullptr;

    parentLevel = nullptr;
}

void Body::LoadHitbox(float w_, float h_) {
    hitbox = new Hitbox(w_, h_, pos.x, pos.y);
}

void Body::ApplyForce(Vec3 force_) {
    accel = force_ / mass;
}

void Body::Update(float deltaTime) {
    //If a body is flagged for deletion, push itself to the trash vector (unless the update method is overrided) 
    if (destroyFlag) {
        parentLevel->trashBodies.push_back(this);
        return;
    }

    if (isActive) {
        vel = vel + accel * deltaTime;
        pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);

        // Update orientation
        orientation += rotation * deltaTime;
        rotation += angular * deltaTime;

        //Updates the hitbox's position based on the projection matrix
        if (parentLevel == nullptr) { //guard clause, exits the function early 
            std::cout << "Parent level is not set\n";
            return;
        }

        //Updates the hitbox's postion
        //If it doesn't have a hitbox for whatever reason, just leave
        if (hitbox == nullptr) { return; }
        Matrix4 projectionMat = parentLevel->getParentScene()->getProjectionMatrix();
        Vec3 hitboxPos = projectionMat * pos;
        hitbox->x = hitboxPos.x - hitbox->w * 0.5f;
        hitbox->y = hitboxPos.y - hitbox->h * 0.5f;
    }
}

void Body::HandleEvents( const SDL_Event& event_ ) {

}

void Body::Render(SDL_Renderer* renderer_, Matrix4 projectionMatrix_){
    if (isActive) {
        //Failsafe incase the programmer forgets to add a texture to the body
        if (texture == nullptr && type != TRIGGER) {
            cc.log(error, "You forgot a texture");
        }


        SDL_Rect square;
        Vec3 screenCoords;
        float w, h;

        // convert the position from game coords to screen coords.
        screenCoords = projectionMatrix_ * pos;

        // Scale the image, in case the .png file is too big or small
        //If a cutout was provided, scale the image based on it
        //Otherwise use the image's dimensions


        if (cutout == nullptr) {
            if (image == nullptr) {
                cc.log(error, "You forgot the image");
                w = 0;
                h = 0;
            }
            else {
                w = image->w * scale.x;
                h = image->h * scale.y;
            }
        }
        else {
            w = cutout->w * scale.x;
            h = cutout->h * scale.y;
        }

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


        //If you don't give it a cutout for a smaller section of the image, it'll just use the entire thing
        //Pretty useful ngl -Adriel
        SDL_RenderCopyEx(renderer_, texture, cutout, &square, orientationDegrees, nullptr, flip);
    }
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