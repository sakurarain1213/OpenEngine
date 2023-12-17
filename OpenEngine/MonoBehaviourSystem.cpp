#include"MonoBehaviourSystem.h"
using namespace OpenEngine;
MonoBehaviourSystem::MonoBehaviourSystem(World* world):mWorld(world) {
	
}

int MonoBehaviourSystem::Initialize() {

	return 0;
}

void MonoBehaviourSystem::Finalize() {

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
