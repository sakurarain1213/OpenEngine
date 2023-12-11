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
