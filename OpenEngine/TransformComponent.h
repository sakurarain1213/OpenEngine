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
		void SetScale(Vec3 scale);
		//void SetLinearVelocity(Vector3f vel);

		//void SetAngularVelocity(Quaternionf vel);

		Vector3f GlobalVectorToLocalVector(Vector3f globalVector);
		Vector3f LocalPointToGlobalPoint(Vector3f localPoint);

		void SetWorldMatrix(Matrix4f  mWorldMatrix) { mWorldMatrix = mWorldMatrix;}
		Matrix4f GetWorldMatrix() { return this->mWorldMatrix; }

		void SetWorldMatrixInverse(Matrix4f  mWorldMatrixInverse) { mWorldMatrixInverse = mWorldMatrixInverse; }
		Matrix4f GetWorldMatrixInverse() { return this->mWorldMatrixInverse; }

		Vector3f TransformVector(Matrix4f& matrix, Vector3f& vector);
		Vector3f TransformVector(Matrix3f& matrix, Vector3f& vector);
		Vector3f TransformPoint(Matrix4f matrix, Vector3f point);

		//math
		Matrix3f GetRatationMatrixGlobal2Local33()
		{
			Matrix4f world2local = GetWorldMatrixInverse();
			Matrix3f ret;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					ret(i*3+j) = world2local(i*3+j);
				}
			}
			return ret;
		}
		Mat4 GetModelMatrix();
		

	public:
		Vector3f Position;
		//Vector3f LinearVelocity;
		//Quaternionf  AngularVelocity;
		Quaternionf Rotation;
		Vector3f Scale;

		bool ModelMatrixdirtyflag;//true则重新计算矩阵
		Mat4 ModelMatrix;


		Matrix4f  mWorldMatrix;
		Matrix4f  mWorldMatrixInverse;

	};
}
