#include "World.h"
#include"Entity.h"
using namespace std;
using namespace OpenEngine;
OpenEngine::World::World(std::string name) : IRuntimeModule(name) {

}
std::string OpenEngine::World::GetType() {
	return "World";
}
void OpenEngine::World::Tick() {
	
	mTransformSystem->Tick();
}

int OpenEngine::World::Initialize() {
	
	mTransformSystem = new TransformSystem(this);
	mTransformSystem->Initialize();


	return 0;
}
void OpenEngine::World::Finalize() {
	mEntities.clear();

	mTransformSystem->Finalize();
}
shared_ptr<Entity> OpenEngine::World::CreateEntity(string name) {
	auto entity = std::make_shared<Entity>();
	entity->Initialize(this);
	mEntities[entity->GetGuid()] = entity;
	return entity;
}