
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
	gravity = Vector3f(0.0f, 98.0665f, 0.0f);
	return 0;
}

void OpenEngine::PhysicSystem::Finalize() noexcept
{
}

void OpenEngine::PhysicSystem::Tick() noexcept
{


	float deltaTime = Time::GetDeltaTime();
	//gravity = Vector3f(0, 980.665, 0);  //尝试强制重设  gravity值 稳定
	
	
	std::vector<RigidBodyComponent*> activedRigidBodies;
	CollectRigidBodies(activedRigidBodies);

	//使用物理时间

	/*
	if (curPhysicDTime <= deltaTime) {
		//按照curPhysicDTime更新位置，然后用PhysicDTime执行物理运算，在用deltaTime更新位置。再重置curPhysicDTime=PhysicDTime再return
	}
	else {
		curPhysicDTime -= deltaTime;
		//按照deltaTime更新位置
	}
	*/
	

	//std::cout << activedRigidBodies.size()<<"SIZESSSSS";  

	// udpate Inertia tensor in global 坐标
	for (auto* rigidBody : activedRigidBodies)
	{
		rigidBody->UpdateInverseInertiaWs();  //无影响
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
		//cout <<rigidBody->GetVelocity() << endl;
	}

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

	//先假设都不碰撞 先全部没动  (包括静态)
	for (auto* rigidBody : activedRigidBodies)
	{
		rigidBody->SetMove(false);
	}


	for (auto pair : candicate)
	{
		//std::cout << "M";   //现在只会碰撞一帧 move提示
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
			//如果碰撞  设置AB的ismov = T   单独解决碰撞盒移动分离
			A->SetMove(true); B->SetMove(true);   //key phase   -----------------------唯一标志move  move只增不减
			//同一帧  move过了也可能和别的再碰  再加进move就行  只要set只有一次就行
			// 计算碰撞后的速度
			//std::cout << "CCCCCLLLLLLIIIICCCCCCC";   //现在只会碰撞一帧
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
			float overlapXLength = overlapMaxPoint(0) - overlapMinPoint(0);
			float overlapYLength = overlapMaxPoint(1) - overlapMinPoint(1);
			float overlapZLength = overlapMaxPoint(2) - overlapMinPoint(2);

			bool SmaxX = false; bool SmaxY = false; bool SmaxZ = false;
			float SX = overlapYLength * overlapZLength;
			float SY = overlapXLength * overlapZLength;
			float SZ = overlapXLength * overlapYLength;

			//确定解除碰撞的方向
			if (SX >= SY && SX >= SZ) {
				SmaxX = true;}
			else if (SY >= SX && SY >= SZ) {
				SmaxY = true;}
			else {
				SmaxZ = true;}
			
			//solve
			if (SmaxX) {
					solveCollid(A, B, 0 /*维度 0 1 2*/, overlapX/*碰撞flag*/, deltaTime);
			}
			else if (SmaxY) {
					solveCollid(A, B, 1 /*维度 0 1 2*/, overlapY/*碰撞flag*/, deltaTime);
			}
			else {
					solveCollid(A, B, 2 /*维度 0 1 2*/, overlapZ/*碰撞flag*/, deltaTime);
			}

			//一组碰撞处理结束
		}
		else {
			//没发生碰撞  也是两个刚体对  也要更新aabb以及pos   留到后续
			/*
			std::cout << A->GetAABB().minPoint << "------AMIN" << endl;
			std::cout << endl;
			std::cout << position1 << "------A POS" << endl;
			*/
		}
	}
	//rigid pair碰撞处理结束  只有碰撞的对 更新了AABB和pos

	// integratePhase 
	//integratePhase->integrate(activedRigidBodies, deltaTime);

	updateAABBandPOS(activedRigidBodies, deltaTime);




	/*
	for (auto* rigidBody : activedRigidBodies)
	{
		cout << rigidBody->GetOwner()->GetComponent<TransformComponent>()->GetRotation().w() << endl;

	}   
	*/
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

void OpenEngine::PhysicSystem:: updateAABBandPOS(std::vector<RigidBodyComponent*> activedRigidBodies, float deltaTime) {
	for (auto* rigidBodyComponent : activedRigidBodies)
	{
		if (rigidBodyComponent->IsStatic())
		{
			Vector3f tempset(0, 0, 0);
			rigidBodyComponent->SetVelocity(tempset);
			rigidBodyComponent->SetAngularVelocity(tempset);
			continue;
		}
		if (rigidBodyComponent->GetMove())
		{
			continue;
		}
		//更新AABB
		Vec3 newMinPoint = rigidBodyComponent->GetAABB().minPoint + rigidBodyComponent->GetVelocity() * deltaTime;
		Vec3 newMaxPoint = rigidBodyComponent->GetAABB().maxPoint + rigidBodyComponent->GetVelocity() * deltaTime;
		rigidBodyComponent->SetAABB(newMinPoint, newMaxPoint);

		//更新POS
		TransformComponent* transform = rigidBodyComponent->GetOwner()->GetComponent<TransformComponent>();
		Vector3f newPosition(0, 0, 0);
		newPosition = transform->GetPosition() + rigidBodyComponent->GetVelocity() * deltaTime;
		transform->SetPosition(newPosition);
	}
}

void OpenEngine::PhysicSystem:: solveCollid(RigidBodyComponent* A, RigidBodyComponent* B, int wei/*维度 0 1 2*/, bool overlap/*碰撞flag*/, float deltaTime) {
	float massA = A->GetMass(); float massB = B->GetMass();
	Vec3 velocityA = A->GetVelocity(); Vec3 velocityB = B->GetVelocity();
	velocityA(wei) = ((A->GetVelocity()(wei) * (massA - massB) + 2 * massB * B->GetVelocity()(wei)) / (massA + massB));
	velocityB(wei) = ((B->GetVelocity()(wei) * (massB - massA) + 2 * massA * A->GetVelocity()(wei)) / (massA + massB));
	// 对应方向碰撞  更新物体的速度
	A->SetVelocity(velocityA);
	B->SetVelocity(velocityB);
	//循环防止相交   如果还相交 继续按照变速的速度移动
	int cnt = 0;
	while (overlap) {
		//aabb位置要根据碰撞之后的速度乘时间 刷新	这里取巧了  避免无穷碰撞  与体积有关
		Vec3 newMinPoint = A->GetAABB().minPoint + VectorScale(A->GetVelocity(), deltaTime);
		Vec3 newMaxPoint = A->GetAABB().maxPoint + VectorScale(A->GetVelocity(), deltaTime);

		if (!A->IsStatic()) {
			A->SetAABB(newMinPoint, newMaxPoint);    //-------SET  AABB
			TransformComponent* tA = A->GetOwner()->GetComponent<TransformComponent>();  	//-----SET  POS
			Vector3f newPosition(0, 0, 0);
			newPosition = tA->GetPosition() + A->GetVelocity() * deltaTime;
			tA->SetPosition(newPosition);
		}

		Vec3 newMinPointB = B->GetAABB().minPoint + VectorScale(B->GetVelocity(), deltaTime);
		Vec3 newMaxPointB = B->GetAABB().maxPoint + VectorScale(B->GetVelocity(), deltaTime);
		if (!B->IsStatic()) {
			B->SetAABB(newMinPointB, newMaxPointB);  //-------SET  AABB

			TransformComponent* tB = B->GetOwner()->GetComponent<TransformComponent>();  	//-----SET  POS
			Vector3f newPosition(0, 0, 0);
			newPosition = tB->GetPosition() + B->GetVelocity() * deltaTime;
			tB->SetPosition(newPosition);

		}

		overlap = A->GetAABB().maxPoint(wei) > B->GetAABB().minPoint(wei) && A->GetAABB().minPoint(wei) < B->GetAABB().maxPoint(wei);

		cnt++;
		if (cnt > 10)//cnt重复算10帧 强制回弹
		{
			Vec3 temp1 = velocityA; Vec3 temp2 = velocityB;
			temp1(wei) = -velocityA(wei); temp2(wei) = -velocityB(wei);
			A->SetVelocity(temp1);
			B->SetVelocity(temp2);
			Vec3 newMinPoint = A->GetAABB().minPoint + VectorScale(A->GetVelocity(), deltaTime);
			Vec3 newMaxPoint = A->GetAABB().maxPoint + VectorScale(A->GetVelocity(), deltaTime);
			if (!A->IsStatic()) {
				A->SetAABB(newMinPoint, newMaxPoint);    //-------SET  AABB
				TransformComponent* tA = A->GetOwner()->GetComponent<TransformComponent>();  	//-----SET  POS
				Vector3f newPosition(0, 0, 0);
				newPosition = tA->GetPosition() + A->GetVelocity() * deltaTime;
				tA->SetPosition(newPosition);
			}
			Vec3 newMinPointB = B->GetAABB().minPoint + VectorScale(B->GetVelocity(), deltaTime);
			Vec3 newMaxPointB = B->GetAABB().maxPoint + VectorScale(B->GetVelocity(), deltaTime);
			if (!B->IsStatic()) {
				B->SetAABB(newMinPointB, newMaxPointB);  //-------SET  AABB
				TransformComponent* tB = B->GetOwner()->GetComponent<TransformComponent>();  	//-----SET  POS
				Vector3f newPosition(0, 0, 0);
				newPosition = tB->GetPosition() + B->GetVelocity() * deltaTime;
				tB->SetPosition(newPosition);
			}

			overlap = false;
		}
		std::cout << " warning  collidsion in  " << wei << std::endl;   //现在只会碰撞一帧 ???
	}




}