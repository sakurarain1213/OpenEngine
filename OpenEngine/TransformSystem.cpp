#include "TransformSystem.h"
#include"Time.h"
#include<algorithm>
#include<iostream>
#include"Entity.h"
using namespace Eigen;
OpenEngine::TransformSystem::TransformSystem(World* world) {
	mWorld = world;
}

int OpenEngine::TransformSystem::Initialize()noexcept {
	
	return 0;

}

void OpenEngine::TransformSystem::Tick()noexcept {

	float dTime = Time::GetDeltaTime();

	for (TransformComponent* t : components) {
		//if (!t->GetOwner()->GetComponent<RigidBodyComponent>()) {
			//t->SetPosition(t->Position + dTime * t->LinearVelocity);
		//}
		//else {
		//	t->SetPosition(t->Position + dTime * t->GetOwner()->GetComponent<RigidBodyComponent>()->GetVelocity());
		//}
		//Vec3 temp=t->GetOwner()->GetComponent<TransformComponent>()->GetPosition();
		//std::cout << temp;
		
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

