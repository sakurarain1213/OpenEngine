#include"ButtonComponent.h"
#include"Entity.h"
OpenEngine::ButtonComponent::ButtonComponent(Entity* entity) {
	mOwner = entity;
	mIsActive = true;
	size = { 200,200 };
	window_id = "";
	text = " ";
}

OpenEngine::ButtonComponent::ButtonComponent() {
	mOwner = nullptr;
	mIsActive = true;
	size = { 200,200 };
	window_id = "";
	text = " ";
}

int OpenEngine::ButtonComponent::Initialize() {
	return 0;
}
void OpenEngine::ButtonComponent::Finalize() {

}

void OpenEngine::ButtonComponent::SetText(std::string str) {
	
	text = str;
}

OpenEngine::Vec3 OpenEngine::ButtonComponent::GetPosition() {
	return mOwner->GetComponent<TransformComponent>()->GetPosition();
	
}

void OpenEngine::ButtonComponent::SetSize(Vec2 _size) {
	size = _size;
}
OpenEngine::Vec2 OpenEngine::ButtonComponent::GetSize() {
	return size;

}

std::string OpenEngine::ButtonComponent::GetText() {
	return text;
}

void OpenEngine::ButtonComponent::SetWindowid(std::string nam) {
	window_id= nam;
}

std::string OpenEngine::ButtonComponent::GetWindowid() {
	return window_id;
}