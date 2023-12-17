#include "World.h"
#include"Entity.h"
using namespace std;
using namespace OpenEngine;
OpenEngine::World::World(std::string name) : IRuntimeModule(name) {
	mTransformSystem = new TransformSystem(this);
	mTransformSystem->Initialize();
	mPhysicSystem = new PhysicSystem(this);
	mPhysicSystem->Initialize();

	mUISystem = new UISystem(this);
	mUISystem->Initialize();
	mCameraSystem = new CameraSystem(this);
	mCameraSystem->Initialize();
	mMeshRendererSystem = new MeshRendererSystem(this);
	mMeshRendererSystem->Initialize();

	mMonoBehaviourSystem = new MonoBehaviourSystem(this);
	mMonoBehaviourSystem->Initialize();
}
std::string OpenEngine::World::GetType() {
	return "World";
}
void OpenEngine::World::Tick() {

	mCameraSystem->Tick();
	mPhysicSystem->Tick();
	mTransformSystem->Tick();
	mMeshRendererSystem->Tick();
	mUISystem->Tick();
	mMonoBehaviourSystem->Tick();
}

int OpenEngine::World::Initialize() {
	

	shared_ptr<Entity> mainCamera = CreateEntity("mainCamera");
	CameraComponent* comp=mainCamera->AddComponent<CameraComponent>();
	mCameraSystem->SetMainCamera(comp);
	return 0;
}
void OpenEngine::World::Finalize() {
	mEntities.clear();

	mPhysicSystem->Finalize();
	mTransformSystem->Finalize();
	mUISystem->Finalize();
	mCameraSystem->Finalize();
	mMeshRendererSystem->Finalize();
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

