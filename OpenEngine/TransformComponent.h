#pragma once
#include"IComponent.h"
#include"Math.h"
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
		Vector3f GetPosition() { return this->Position; }
		void Rotate(Quaternionf rota);
		Quaternionf GetRotation() { return this->Rotation; }
		void SetLinearVelocity(Vector3f vel);

		void SetAngularVelocity(Quaternionf vel);

		Vector3f GlobalVectorToLocalVector(Vector3f globalVector);
		Vector3f LocalPointToGlobalPoint(Vector3f localPoint);

		void SetWorldMatrix(Matrix4f  mWorldMatrix);
		Matrix4f GetWorldMatrix() { return this->mWorldMatrix; }

		void SetWorldMatrixInverse(Matrix4f  mWorldMatrixInverse);
		Matrix4f GetWorldMatrixInverse() { return this->mWorldMatrixInverse; }

		Vector3f TransformVector(Matrix4f& matrix, Vector3f& vector);
		Vector3f TransformVector(Matrix3f& matrix, Vector3f& vector);
		Vector3f TransformPoint(Matrix4f matrix, Vector3f point);

	public:
		Vector3f Position;
		Vector3f LinearVelocity;
		Quaternionf  AngularVelocity;
		Quaternionf Rotation;
		Vector3f Scale;

		Matrix4f  mWorldMatrix;
		Matrix4f  mWorldMatrixInverse;

	};
}
