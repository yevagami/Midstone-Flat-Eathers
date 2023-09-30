#include "GameObjects.h"

GameObject::GameObject(const char* objectName, Vec3 position_) {
	isSolid = true;
	isActive = true;

	name = objectName;
	position = position_;
	textureFile = "";
	texture = nullptr;
}

GameObject::GameObject(const char* objectName, Vec3 position_, const char* textureFile_) {
	isSolid = true;
	isActive = true;

	name = objectName;
	position = position_;
	textureFile = textureFile_;
	texture = nullptr;
}

GameObject::GameObject(const char* objectName, Vec3 position_, const char* textureFile_, bool isActive_, bool isSolid_) {
	isSolid = isSolid_;
	isActive = isActive_;

	name = objectName;
	position = position_;
	textureFile = textureFile_;
	texture = nullptr;
}

void GameObject::OnDestroy() {
	texture = nullptr;
	textureFile = "";

}


SDL_Texture* GameObject::getSDLTexture() {
	return texture;
}

void GameObject::setSDLTexture(SDL_Texture* newTexture) {
	texture = newTexture;
}

const char* GameObject::getTextureFile() {
	return textureFile;
}

void GameObject::setTextureFile(const char* newTextureFile) {
	textureFile = newTextureFile;
}