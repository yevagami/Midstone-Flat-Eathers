#include "GameObjects.h"

GameObject::GameObject(const char* objectName, Vec3 position) {
	isSolid = true;
	isActive = true;

	name = objectName;
	body.pos = position;
	textureFile = "";
	texture = nullptr;
}

GameObject::GameObject(const char* objectName, Vec3 position, const char* textureFile_) {
	isSolid = true;
	isActive = true;

	name = objectName;
	body.pos = position;
	textureFile = textureFile_;
	texture = nullptr;
}

GameObject::GameObject(const char* objectName, Vec3 position, const char* textureFile_, bool isActive_, bool isSolid_) {
	isSolid = isSolid_;
	isActive = isActive_;

	name = objectName;
	body.pos = position;
	textureFile = textureFile_;
	texture = nullptr;
}

void GameObject::OnDestroy() {
	texture = nullptr;
	textureFile = "";

}
