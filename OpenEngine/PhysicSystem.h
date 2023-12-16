#pragma once
#include"ISystem.h"
#include <set>
#include <vector>
#include "Math.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Contact.h"

#include "BoardPhase.h"
#include "NarrowPhase.h"
#include "ResolutionPhase.h"
#include "IntegratePhase.h"
#include <iostream>


namespace OpenEngine {

	class World;
	class RigidBodyComponent;
	class IBoardPhase;
	class INarrowPhase;
	class IResolutionPhase;
	class IIntegratePhase;
	class ContactManifold;

	class PhysicSystem : public ISystem
	{
	public:

		PhysicSystem(World* world) {
			this->mWorld = world;
			this->boardPhase = new BoardPhaseNquared();
			this->narrowPhase = new NarrowPhaseGJKEPA();
			this->resolutionPhase = new ResolutionPhaseConstraintBase();
			this->integratePhase = new IntegratePhase();
		}
		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		virtual void AddComponent(RigidBodyComponent* comp);
		virtual void DeleteComponent(RigidBodyComponent* comp);

		void CollectRigidBodies(std::vector<RigidBodyComponent*>& activedRigidBodies);

		//math
		Vector3f VectorScale(Vector3f v, float scale) {
			size_t count = 3;
			Vector3f result;
			for (size_t i = 0; i < count; ++i) {
				result(i) = v(i) * scale;
			}
			return result;
		}

		//�ع�  �� ������AABB��ײ�ж� 
		bool isCollid(AABB obj1, AABB obj2) {
			bool overlapX = obj1.maxPoint(0) >= obj2.minPoint(0) && obj1.minPoint(0) <= obj2.maxPoint(0);
			bool overlapY = obj1.maxPoint(1) >= obj2.minPoint(1) && obj1.minPoint(1) <= obj2.maxPoint(1);
			bool overlapZ = obj1.maxPoint(2) >= obj2.minPoint(2) && obj1.minPoint(2) <= obj2.maxPoint(2);
			// ������������϶����ص�����ʾ��ײ
			return overlapX && overlapY && overlapZ;
		}

		void changeV(RigidBodyComponent* a, RigidBodyComponent* b) {
			AABB obj1 = a->GetAABB(); 
			AABB obj2 = b->GetAABB();
			bool overlapX = obj1.maxPoint(0) >= obj2.minPoint(0) && obj1.minPoint(0) <= obj2.maxPoint(0);
			bool overlapY = obj1.maxPoint(1) >= obj2.minPoint(1) && obj1.minPoint(1) <= obj2.maxPoint(1);
			bool overlapZ = obj1.maxPoint(2) >= obj2.minPoint(2) && obj1.minPoint(2) <= obj2.maxPoint(2);
			// ������������϶����ص�����ʾ��ײ
			if(overlapX&& overlapY&& overlapZ){
				// ������ײ����ٶ�
				//std::cout << "CCCCCLLLLLLIIIICCCCCCC";  ����ֻ����ײһ֡
				Vec3 velocityA = a->GetVelocity();
				Vec3 velocityB = b->GetVelocity();
				float massA = a->GetMass();
				float massB = b->GetMass();

				// �����������Ϸ�����ײ�������ٶȷ���   �������״�͸  ��������  ��Զ��ײ  ���Ƿ����
				if (overlapX) {
					
					velocityA(0) = ((velocityA(0) * (massA - massB) + 2 * massB * velocityB(0)) / (massA + massB));
					velocityB(0) = ((velocityB(0) * (massB - massA) + 2 * massA * velocityA(0)) / (massA + massB));
				}
				if (overlapY) {
				
					velocityA(1) = ((velocityA(1) * (massA - massB) + 2 * massB * velocityB(1)) / (massA + massB));
					velocityB(1) = ((velocityB(1) * (massB - massA) + 2 * massA * velocityA(1)) / (massA + massB));

				}
				if (overlapZ) {
					velocityA(2) = ((velocityA(2) * (massA - massB) + 2 * massB * velocityB(2)) / (massA + massB));
					velocityB(2) = ((velocityB(2) * (massB - massA) + 2 * massA * velocityA(2)) / (massA + massB));
				
				
				}
				// ����������ٶ�
				a->SetVelocity(velocityA);
				b->SetVelocity(velocityB);


			}

		}





	private:
		std::set<RigidBodyComponent*> components;

		World* mWorld;
		Vector3f gravity;

		IBoardPhase* boardPhase;
		INarrowPhase* narrowPhase;
		IResolutionPhase* resolutionPhase;
		IIntegratePhase* integratePhase;

		std::vector< std::shared_ptr<ContactManifold> > manifolds;

	};

}
