
#include "BoardPhase.h"
#include "RigidBodyComponent.h"

using namespace OpenEngine;


void OpenEngine::BoardPhaseNquared::Update(float dt)
{
}

std::vector<RigidBodyPair>& OpenEngine::BoardPhaseNquared::GeneratePossiblePair(std::vector<RigidBodyComponent*>& rigidbodies, std::vector<RigidBodyPair>& candicate)
{
	candicate.clear();

	for (int i = 0; i < rigidbodies.size(); i++)
	{
		for (int j = i; j < rigidbodies.size(); j++)
		{
			if (i == j)
			{
				continue;
			}
			candicate.push_back(std::make_pair(rigidbodies[i], rigidbodies[j]));
		}
	}
	return candicate;
}
