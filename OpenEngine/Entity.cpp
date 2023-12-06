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

void OpenEngine::Entity::Tick() noexcept{}

OpenEngine::Entity::Entity(std::string name) : IRuntimeModule(name) {
	mParent = nullptr;
	mTransform = nullptr;
	mGuid = boost::uuids::random_generator()();
}
OpenEngine::Entity::Entity(std::string name, const boost::uuids::uuid& guid) : IRuntimeModule(name) {
	mParent = nullptr;
	mTransform = nullptr;
	mGuid = guid;
}
OpenEngine::Entity::~Entity() {
	
	Finalize();
}
boost::uuids::uuid OpenEngine::Entity::GetGuid()const noexcept {
	return mGuid;
}
void OpenEngine::Entity::SetGuid(const boost::uuids::uuid& guid)noexcept {
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


