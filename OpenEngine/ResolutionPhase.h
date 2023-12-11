#pragma once
#include <vector>
#include "Contact.h"


namespace OpenEngine
{
	class IResolutionPhase
	{
	public:
		virtual void Resolve(std::vector<std::shared_ptr<ContactManifold>>& manifolds, float deltaTime) = 0;
	};

	class ResolutionPhaseConstraintBase : public IResolutionPhase
	{
	public:
		virtual void Resolve(std::vector<std::shared_ptr<ContactManifold>>& manifolds, float deltaTime);
		void SolveContactConstranst(std::shared_ptr<ContactManifold> manifold, int idx, float deltaTime);
		void InitContactConstranst(std::shared_ptr<ContactManifold> manifold, int idx, float deltaTime);
	

		//数学工具方法
		Vector3f TransformPoint(Matrix4f matrix, Vector3f point)
		{
			Vector4f hSpace = Vector4f(point(0), point(1), point(2), 1);
			Vector4f tmp = Vector4f(0, 0, 0, 0);

			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					tmp(r) += hSpace(c) * matrix(r * 4 + c);
				}
			}
			return Vector3f(tmp(0), tmp(1), tmp(2));
		}

	
	
	
	
	};
}