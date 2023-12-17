#include"MonoBehaviourSystem.h"
using namespace OpenEngine;
MonoBehaviourSystem::MonoBehaviourSystem(World* world):mWorld(world) {
	
}

void MonoBehaviourSystem::AddComponent(MonoBehaviour* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.insert(comp);
}
void MonoBehaviourSystem::DeleteComponent(MonoBehaviour* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}

int MonoBehaviourSystem::Initialize() {

	return 0;
}

void MonoBehaviourSystem::Finalize() {
	components.clear();
}

void MonoBehaviourSystem::Tick() {

	for (MonoBehaviour* comp : components) {
		comp->Update();
	}

}

void MonoBehaviourSystem::FixedTick() {
	for (MonoBehaviour* comp : components) {
		comp->FixedUpdate();
	}
}
