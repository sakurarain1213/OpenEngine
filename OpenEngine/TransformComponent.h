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

		virtual int Initialize();
		virtual void Finalize();

		void SetPosition(Vector3f posi);
		void Rotate(Quaternionf rota);

		void SetLinearVelocity(Vector3f vel);
		void SetAngularVelocity(Quaternionf vel);
	public:
		Vector3f Position;
		Vector3f LinearVelocity;
		Quaternionf  AngularVelocity;
		Quaternionf Rotation;
		Vector3f Scale;

	};
}
