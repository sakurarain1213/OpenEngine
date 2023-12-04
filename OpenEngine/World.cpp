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
	for (auto sys : Systems) {
		sys->Tick();
	}
}

int OpenEngine::World::Initialize() {
	
	mTransformSystem = new TransformSystem();
	return 0;
}

shared_ptr<Entity> OpenEngine::World::CreateEntity(string name) {
	Entity e(name);
	shared_ptr<Entity> p = e;
	return e;
}