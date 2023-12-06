#include "TransformComponent.h"
#include"Entity.h"
#include"Eigen/Dense"
using namespace OpenEngine;

OpenEngine::TransformComponent::TransformComponent() {
	
	Position = { 0,0,0 };
	LinearVelocity = { 0,0,0 };
	Rotation = { 0,0,0,0 };
	AngularVelocity = { 0,0,0,0 };
	mOwner = nullptr;
	mIsActive = true;
	
}

OpenEngine::TransformComponent::TransformComponent(Entity* entity) {
	Position = { 0,0,0 };
	Rotation = { 0,0,0,0 };
	LinearVelocity = { 0,0,0 };
	AngularVelocity = { 0,0,0,0 };
	mOwner = entity;
	mIsActive = true;
}
int OpenEngine::TransformComponent::Initialize() {
	return 0;
}
void OpenEngine::TransformComponent::Finalize() {

}
void OpenEngine::TransformComponent::SetPosition(Vector3f posi) {
	Position = posi;
}
void OpenEngine::TransformComponent::Rotate(Quaternionf rota) {
	Rotation = rota;
}
void OpenEngine::TransformComponent::SetLinearVelocity(Vector3f vel) {
	LinearVelocity = vel;
}
void OpenEngine::TransformComponent::SetAngularVelocity(Quaternionf vel) {
	AngularVelocity = vel;
}