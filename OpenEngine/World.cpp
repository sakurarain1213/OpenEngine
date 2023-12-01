#include "World.h"
using namespace std;
void OpenEngine::World::Tick() {
	for (auto sys : Systems) {
		sys->Tick();
	}
}

int OpenEngine::World::Initialize() {
	
	mTransformSystem=new TransformSystem()
}