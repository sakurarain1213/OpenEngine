#include "Entity.h"
#include<stdio.h>
using namespace OpenEngine;
std::string OpenEngine::Entity::GetType() {
	return "Entity";
}
int OpenEngine::Entity::Initialize() {
	return 0;
}

int OpenEngine::Entity::Initialize(World* world) {
	mWorld = world;
	return 0;
}

void OpenEngine::Entity::Finalize() {
	mchildrenE.clear();
	mParent = nullptr;

}



OpenEngine::Entity::Entity(std::string name) : IRuntimeModule(name) {
	mParent = nullptr;
	
}
OpenEngine::Entity::Entity(std::string name, const boost::uuids::uuid& guid) : IRuntimeModule(name) {
	mParent = nullptr;
	mTransform = nullptr;
	mGuid = guid;
}
OpenEngine::Entity::~Entity() {
	printf("%dEntity destroyed!\n", mGuid);
	Finalize();
}
boost::uuids::uuid OpenEngine::Entity::GetGuid() {
	return mGuid;
}
void OpenEngine::Entity::SetGuid(const boost::uuids::uuid& guid) {
	mGuid = guid;
}

void OpenEngine::Entity::AddChild(std::shared_ptr<Entity> child) {
	if (IsChild(child)) {
		return;
	}
	mchildrenE.push_back(child);
	child->SetParent(this);
}

void OpenEngine::Entity::RemoveChild(std::shared_ptr<Entity> child) {
	if (!IsChild(child)) {
		return;
	}
	auto iter = mchildrenE.begin();
	for (; iter != mchildrenE.end(); ++iter) {
		if ((*iter) == child) {
			mchildrenE.erase(iter);
			child->SetParent(nullptr);
			return;
		}
	}
}

bool OpenEngine::Entity::IsChild(std::shared_ptr<Entity> child) {
	if (child->GetParent() == this) {
		return true;
	}
	return false;
}

Entity* OpenEngine::Entity::GetParent() {
	return mParent;
}
void OpenEngine::Entity::SetWorld(World* world) {
	mWorld = world;
}
World* OpenEngine::Entity::GetWorld() {
	return mWorld;
}
void OpenEngine::Entity::SetParent(Entity* parent) {
	mParent = parent;
}

size_t OpenEngine::Entity::GetChildrenCount() {
	return mchildrenE.size();
}


template<typename T>
T* OpenEngine::Entity::AddComponent() {
	void* comp = nullptr;
	if (std::is_same<T, TransformComponent>::value) {
		mTransform = new TransformComponent(this);
		
		mTransform->Initialize();
		comp = mTransform;
	}

	return (T*)comp;
}

template<typename T>
T* OpenEngine::Entity::GetComponent() {
	void* ret = nullptr;
	if (std::is_same<T, TransformComponent>::value) {
		ret = mTransform;
	}
	return (T*)ret;
}

template<typename T>
void OpenEngine::Entity::RemoveComponent() {
	if (std::is_same<T, TransformComponent>::value) {
		mTransform->Finalize();
		delete mTransform;
		mTransform = nullptr;
	}
}