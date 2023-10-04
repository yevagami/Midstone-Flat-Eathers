#include "Hitbox.h"

bool Hitbox::collisionCheck(Hitbox other){
    bool collisionX = x + w >= other.x &&
        other.x + other.w >= x;

    bool collisionY = y + h >= other.y &&
        other.y + other.h >= y;
    
    return collisionX && collisionY;
}
