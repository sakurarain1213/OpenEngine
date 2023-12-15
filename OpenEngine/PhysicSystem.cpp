
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

	//std::cout << activedRigidBodies.size()<<"SIZESSSSS";   OK

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
	//ok  gravityImpulse是速度增量

	//debug this
	// boardPhase
	boardPhase->Update(deltaTime);

	vector<RigidBodyPair> candicate;
	boardPhase->GeneratePossiblePair(activedRigidBodies, candicate);
	//add activedRigidBodies  to   candicate ok
	//std::cout << activedRigidBodies.size() << "candicate"; 

	//------------------------------------------
	// narrowPhase
	//narrowPhase->CollideDetection(candicate, manifolds);  //这一步的内部函数DEBUG复杂

	// resolutionPhase
	//resolutionPhase->Resolve(manifolds, deltaTime);

	//------------------------------------------
	//重构   耦合narrowPhase+ resolutionPhase  解决碰撞

	for (auto pair : candicate)
	{
		RigidBodyComponent* A = pair.first;
		RigidBodyComponent* B = pair.second;
		Vector3f position1 = A->GetOwner()->GetComponent<TransformComponent>()->Position;
		Vector3f position2 = B->GetOwner()->GetComponent<TransformComponent>()->Position;
		//changeV(A, B);  再重构

		AABB obj1 = A->GetAABB();
		AABB obj2 = B->GetAABB();
		bool overlapX = obj1.maxPoint(0) > obj2.minPoint(0) && obj1.minPoint(0) < obj2.maxPoint(0);
		bool overlapY = obj1.maxPoint(1) > obj2.minPoint(1) && obj1.minPoint(1) < obj2.maxPoint(1);
		bool overlapZ = obj1.maxPoint(2) > obj2.minPoint(2) && obj1.minPoint(2) < obj2.maxPoint(2);
		// 如果在所有轴上都有重叠，表示碰撞
		if (overlapX && overlapY && overlapZ) {
			// 计算碰撞后的速度
			//std::cout << "CCCCCLLLLLLIIIICCCCCCC";   现在只会碰撞一帧
			Vec3 velocityA = A->GetVelocity();
			Vec3 velocityB = B->GetVelocity();
			float massA = A->GetMass();
			float massB = B->GetMass();

			// 在三个方向上发生碰撞，容易穿透  反复变向  永远碰撞   物理上也不能同时更新三维度的更新速度分量     考虑
			//自研 只适合AABB的 速度变化  ：只会在一个方向上碰撞   面积检测   垂直最大接触面即法线    再加上循环 保证分离
			//重叠部分的长度是 maxPoint(0) - minPoint(0)，Y轴是 maxPoint(1) - minPoint(1)，Z轴是 maxPoint(2) - minPoint(2)。
			//比较三个轴上的重叠部分体积，找到最大体积的轴，该轴对应的法线方向就是重叠部分的法线方向。
			Vector3f overlapMinPoint(0, 0, 0); Vector3f overlapMaxPoint(0, 0, 0);
			overlapMinPoint(0) = max(obj1.minPoint(0), obj2.minPoint(0));
			overlapMaxPoint(0) = min(obj1.maxPoint(0), obj2.maxPoint(0));
			overlapMinPoint(1) = max(obj1.minPoint(1), obj2.minPoint(1));
			overlapMaxPoint(1) = min(obj1.maxPoint(1), obj2.maxPoint(1));
			overlapMinPoint(2) = max(obj1.minPoint(2), obj2.minPoint(2));
			overlapMaxPoint(2) = min(obj1.maxPoint(2), obj2.maxPoint(2));
			//重叠部分的坐标

			//求最大重叠方向

			float overlapXLength = overlapMaxPoint(0) - overlapMinPoint(0) ;
			float overlapYLength = overlapMaxPoint(1) - overlapMinPoint(1) ;
			float overlapZLength = overlapMaxPoint(2) - overlapMinPoint(2) ;

			bool SmaxX = false; bool SmaxY = false; bool SmaxZ = false;
			float SX = overlapYLength * overlapZLength;
			float SY = overlapXLength * overlapZLength;
			float SZ = overlapXLength * overlapYLength;

			if (SX >= SY && SX >= SZ) {
				SmaxX = true;}
			else if (SY >= SX && SY >= SZ) {
				SmaxY = true;}
			else {
				SmaxZ = true;}
			//确定解除碰撞的方向

			if (SmaxX) {
				velocityA(0) = ((A->GetVelocity()(0) * (massA - massB) + 2 * massB * B->GetVelocity()(0)) / (massA + massB));
				velocityB(0) = ((B->GetVelocity()(0) * (massB - massA) + 2 * massA * A->GetVelocity()(0)) / (massA + massB));

				// 对应方向碰撞  更新物体的速度
				A->SetVelocity(velocityA);
				B->SetVelocity(velocityB);
				//循环防止相交   如果还相交 继续按照速度匀速移动
				while (overlapX) {
					//aabb位置要根据pos刷新
					Vec3 newMinPoint = A->GetAABB().minPoint + A->GetVelocity() * deltaTime;
					Vec3 newMaxPoint = A->GetAABB().maxPoint + A->GetVelocity() * deltaTime;
					A->SetAABB(newMinPoint, newMaxPoint);

					Vec3 newMinPointB = B->GetAABB().minPoint + B->GetVelocity() * deltaTime;
					Vec3 newMaxPointB = B->GetAABB().maxPoint + B->GetVelocity() * deltaTime;
					B->SetAABB(newMinPointB, newMaxPointB);

					overlapX = A->GetAABB().maxPoint(0) > B->GetAABB().minPoint(0) && A->GetAABB().minPoint(0) < B->GetAABB().maxPoint(0);
				}


			}
			else if (SmaxY) {
				velocityA(1) = ((A->GetVelocity()(1) * (massA - massB) + 2 * massB * B->GetVelocity()(1)) / (massA + massB));
				velocityB(1) = ((B->GetVelocity()(1) * (massB - massA) + 2 * massA * A->GetVelocity()(1)) / (massA + massB));
				A->SetVelocity(velocityA);
				B->SetVelocity(velocityB);
				while (overlapY) {
					Vec3 newMinPoint = A->GetAABB().minPoint + A->GetVelocity() * deltaTime;
					Vec3 newMaxPoint = A->GetAABB().maxPoint + A->GetVelocity() * deltaTime;
					A->SetAABB(newMinPoint, newMaxPoint);

					Vec3 newMinPointB = B->GetAABB().minPoint + B->GetVelocity() * deltaTime;
					Vec3 newMaxPointB = B->GetAABB().maxPoint + B->GetVelocity() * deltaTime;
					B->SetAABB(newMinPointB, newMaxPointB);

					overlapY = A->GetAABB().maxPoint(1) > B->GetAABB().minPoint(1) && A->GetAABB().minPoint(1) < B->GetAABB().maxPoint(1);
				}
			}
			else {
				velocityA(2) = ((A->GetVelocity()(2) * (massA - massB) + 2 * massB * B->GetVelocity()(2)) / (massA + massB));
				velocityB(2) = ((B->GetVelocity()(2) * (massB - massA) + 2 * massA * A->GetVelocity()(2)) / (massA + massB));
				A->SetVelocity(velocityA);
				B->SetVelocity(velocityB);
				while (overlapZ) {
					// aabb位置要根据pos刷新
					Vec3 newMinPoint = A->GetAABB().minPoint + A->GetVelocity() * deltaTime;
					Vec3 newMaxPoint = A->GetAABB().maxPoint + A->GetVelocity() * deltaTime;
					A->SetAABB(newMinPoint, newMaxPoint);

					Vec3 newMinPointB = B->GetAABB().minPoint + B->GetVelocity() * deltaTime;
					Vec3 newMaxPointB = B->GetAABB().maxPoint + B->GetVelocity() * deltaTime;
					B->SetAABB(newMinPointB, newMaxPointB);

					overlapZ = A->GetAABB().maxPoint(2) > B->GetAABB().minPoint(2) && A->GetAABB().minPoint(2) < B->GetAABB().maxPoint(2);
				}
			}
		
		//一组碰撞处理结束
			//fin?  
		}

	//没发生碰撞也要更新aabb box
	Vec3 newMinPoint = A->GetAABB().minPoint + A->GetVelocity() * deltaTime;
	Vec3 newMaxPoint = A->GetAABB().maxPoint + A->GetVelocity() * deltaTime;
	A->SetAABB(newMinPoint, newMaxPoint);

	Vec3 newMinPointB = B->GetAABB().minPoint + B->GetVelocity() * deltaTime;
	Vec3 newMaxPointB = B->GetAABB().maxPoint + B->GetVelocity() * deltaTime;
	B->SetAABB(newMinPointB, newMaxPointB);

	/*
	std::cout << A->GetAABB().minPoint << "------AMIN" << endl;
	std::cout << A->GetAABB().maxPoint << "------Amax" << endl;
	std::cout << B->GetAABB().minPoint << "------BMIN" << endl;
	std::cout << B->GetAABB().maxPoint << "------Bmax" << endl;
	std::cout << endl;
	std::cout << position1 << "------A POS" << endl;
	std::cout << position2 << "------B POS" << endl;
	std::cout << endl;
	*/
	}

	// integratePhase   更新位置
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
