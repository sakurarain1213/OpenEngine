#pragma once
#include"IComponent.h"
#include<Eigen/Dense>
using namespace Eigen;
namespace OpenEngine {
	class TransformComponent : public IComponent
	{
	public:
		TransformComponent(Entity* owner);
		TransformComponent();

		void SetPosition(Vector3f posi);
		void Rotate(Quaternionf rota);

	public:
		Vector3f Position;
		Quaternionf Rotation;
		Vector3f Scale;

	};
}
