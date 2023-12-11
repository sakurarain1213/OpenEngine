#pragma once
#include <vector>


namespace OpenEngine
{
	class RigidBodyComponent;
	class IIntegratePhase
	{
	public:
		virtual void integrate(std::vector<RigidBodyComponent*> activedRigidBodies, float dt) = 0;
	};

	class IntegratePhase : public IIntegratePhase
	{
	public:
		virtual void integrate(std::vector<RigidBodyComponent*> activedRigidBodies, float dt);
	};
}