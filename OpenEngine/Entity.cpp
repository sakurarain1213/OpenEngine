#include "Entity.h"
#include<stdio.h>
using namespace OpenEngine;
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

OpenEngine::Entity::Entity() :
	mParent(nullptr){}

OpenEngine::Entity::Entity(int id) {
	mParent = nullptr;
	Eid = id;
}

OpenEngine::Entity::~Entity() {
	printf("%dEntity destroyed!\n", Eid);
	Finalize();
}
int OpenEngine::Entity::GetEid() {
	return Eid;
}
void OpenEngine::Entity::SetEid(int id) {
	Eid = id;
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

World* OpenEngine::Entity::GetWorld() {
	return mWorld;
}
void OpenEngine::Entity::SetParent(Entity* parent) {
	mParent = parent;
}

size_t OpenEngine::Entity::GetChildrenCount() {
	return mchildrenE.size();
}

