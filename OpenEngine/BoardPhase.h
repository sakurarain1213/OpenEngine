#pragma once
#include <vector>
#include "RigidBodyComponent.h"



namespace OpenEngine
{
	typedef std::pair<RigidBodyComponent*, RigidBodyComponent*> RigidBodyPair;

	class IBoardPhase
	{
	public:
		virtual void Update(float dt) = 0;
		virtual std::vector<RigidBodyPair>& GeneratePossiblePair(std::vector<RigidBodyComponent*>& rigidbodies, std::vector<RigidBodyPair>& candicate) = 0;

	};


	class BoardPhaseNquared : public IBoardPhase
	{
	public:
		virtual void Update(float dt);
		virtual std::vector<RigidBodyPair>& GeneratePossiblePair(std::vector<RigidBodyComponent*>& rigidbodies, std::vector<RigidBodyPair>& candicate);


	};

}