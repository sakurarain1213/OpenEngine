#include "TransformSystem.h"
OpenEngine::TransformSystem::TransformSystem(World* world) :ISystem("TransformSystem") {

}

int OpenEngine::TransformSystem::Initialize() {
	
	return 0;

}

void OpenEngine::TransformSystem::Tick() {


}

void OpenEngine::TransformSystem::Finalize() {


}

void OpenEngine::TransformSystem::AddComponent(TransformComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}
	
	components.insert(comp);
}
void OpenEngine::TransformSystem::DeleteComponent(TransformComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}

