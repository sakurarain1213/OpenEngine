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
	auto entity = std::make_shared<Entity>(name);
	entity->Initialize(this);
	mEntities[entity->GetGuid()] = entity;
	return entity;
}
std::shared_ptr<Entity> OpenEngine::World::CreateEntity(string name,const boost::uuids::uuid& guid)
{
	if (mEntities[guid]) {
		return nullptr;
	}

	auto entity = std::make_shared<Entity>(name,guid);
	entity->Initialize(this);
	mEntities[guid] = entity;
	return entity;
}
void OpenEngine::World::DeleteEntity(const boost::uuids::uuid& guid)
{
	auto entity = mEntities[guid];
	if (entity) {
		entity->Finalize();
		mEntities.erase(guid);
	}
}

std::shared_ptr<Entity> OpenEngine::World::GetEntity(const boost::uuids::uuid& guid)
{
	if (!mEntities[guid]) {
		return nullptr;
	}
	return mEntities[guid];
}

size_t OpenEngine::World::GetEntityCount() {
	return mEntities.size();
}