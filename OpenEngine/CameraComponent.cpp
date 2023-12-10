#include "CameraComponent.h"

OpenEngine::CameraComponent::CameraComponent() {
	ViewMatrix <<   0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0;
	Position = { 0,0,0 };
	Lookat = { 0,0,0 };
	Up = { 0,0,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 0;
	FarClip = 0;
	Fov = 0;
}

OpenEngine::CameraComponent::CameraComponent(Entity* entity) {
	mOwner = entity;
	ViewMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	Position = { 0,0,0 };
	Lookat = { 0,0,0 }; 
	Up = { 0,0,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 0;
	FarClip = 0;
	Fov = 0;
}

int OpenEngine::CameraComponent::Initialize() {
	return 0;
}
void OpenEngine::CameraComponent::Finalize() {

}