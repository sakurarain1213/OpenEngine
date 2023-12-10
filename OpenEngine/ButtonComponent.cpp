#include"ButtonComponent.h"
#include"Entity.h"
OpenEngine::ButtonComponent::ButtonComponent(Entity* entity) {
	mOwner = entity;
	mIsActive = true;
	posi = { 0,0 };
	text = "";
}

OpenEngine::ButtonComponent::ButtonComponent() {
	mOwner = nullptr;
	mIsActive = true;
	posi = { 0,0 };
	text = "";
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