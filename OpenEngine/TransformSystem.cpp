#include "TransformSystem.h"
#include"Time.h"
#include<algorithm>
#include<iostream>
using namespace Eigen;
OpenEngine::TransformSystem::TransformSystem(World* world) :ISystem("TransformSystem") {
	mWorld = world;
}

int OpenEngine::TransformSystem::Initialize()noexcept {
	
	return 0;

}

void OpenEngine::TransformSystem::Tick()noexcept {

	float dTime = Time::GetDeltaTime();

	for (TransformComponent* t : components) {
		
		t->SetPosition(t->Position + dTime * t->LinearVelocity);

		float x = t->Position.x();
		float y = t->Position.y();
		std::cout << x << " " << y << "\n";
	}
	
		

}

void OpenEngine::TransformSystem::Finalize()noexcept {


}

void OpenEngine::TransformSystem::AddComponent(TransformComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}
	
	components.insert(comp);
}
void OpenEngine::TransformSystem::DeleteComponent(TransformComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}

