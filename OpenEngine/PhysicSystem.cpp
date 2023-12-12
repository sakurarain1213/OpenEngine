
//四大过程
/*
BoardPhase。排除无碰撞object pair
NarrowPhase 准确判断碰撞点，穿透深度，分离法线等等
ResolvePhase 解决约束。各物理属性会在碰撞后保持约束等式或者不等式
Intergration 结果同步

*/
#include<iostream>
#include "PhysicSystem.h"
#include "Time.h"
#include "World.h"
#include "Entity.h"
#include "Math.h"
#include "RigidBodyComponent.h"
#include "BoardPhase.h"
#include "NarrowPhase.h"
#include "ResolutionPhase.h"
#include "IntegratePhase.h"

using namespace OpenEngine;
using namespace std;


int OpenEngine::PhysicSystem::Initialize() noexcept
{
	gravity = Vector3f(0.0f, 9.80665f, 0.0f);
	return 0;
}

void OpenEngine::PhysicSystem::Finalize() noexcept
{
}

void OpenEngine::PhysicSystem::Tick() noexcept
{
	float deltaTime = Time::GetDeltaTime();
	
	std::vector<RigidBodyComponent*> activedRigidBodies;
	CollectRigidBodies(activedRigidBodies);
	
	// udpate Inertia tensor in global 坐标
	for (auto* rigidBody : activedRigidBodies)
	{
		rigidBody->UpdateInverseInertiaWs();
		
	}

	// gravity
	Vector3f gravityImpulse = VectorScale(gravity, deltaTime);

	for (auto* rigidBody : activedRigidBodies)
	{
		if (rigidBody->IsStatic())
		{
			continue;
		}
		Vector3f tempVelocity = rigidBody->GetVelocity() + gravityImpulse;
		rigidBody->SetVelocity(tempVelocity);
		
	}


	// boardPhase
	boardPhase->Update(deltaTime);

	vector<RigidBodyPair> candicate;
	boardPhase->GeneratePossiblePair(activedRigidBodies, candicate);

	// narrowPhase
	narrowPhase->CollideDetection(candicate, manifolds);

	// resolutionPhase
	resolutionPhase->Resolve(manifolds, deltaTime);

	// integratePhase
	integratePhase->integrate(activedRigidBodies, deltaTime);

	// clearPhase
	manifolds.clear();
	
}

void OpenEngine::PhysicSystem::AddComponent(RigidBodyComponent* comp)
{
	if (nullptr == comp)
	{
		return;
	}

	components.insert(comp);
}

void OpenEngine::PhysicSystem::DeleteComponent(RigidBodyComponent* comp)
{
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}

/*
暂时先每帧都收集一遍。后续可以加脏标记或者维护一个有效集合。
*/
void OpenEngine::PhysicSystem::CollectRigidBodies(std::vector<RigidBodyComponent*>& activedRigidBodies)
{
	activedRigidBodies.clear();
	for (auto* comp : components)    //遍历rigidbodyComponent
	{
		activedRigidBodies.push_back((comp));
	}

}
