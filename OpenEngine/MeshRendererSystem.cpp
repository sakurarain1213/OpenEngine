#include "MeshRendererSystem.h"
using namespace OpenEngine;

MeshRendererSystem::MeshRendererSystem(World* world) {
	mWorld = world;

}

int MeshRendererSystem::Initialize() noexcept {
	return 0;
}
void MeshRendererSystem::Finalize() noexcept {
	components.clear();
}

void MeshRendererSystem::Tick()noexcept {

}
void MeshRendererSystem::AddComponent(MeshRendererComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.insert(comp);
}
void MeshRendererSystem::DeleteComponent(MeshRendererComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}