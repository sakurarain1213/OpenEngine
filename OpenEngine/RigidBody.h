#pragma once
#include<Eigen/Dense>
using namespace Eigen;
class RigidBodyComponent;
class RigidBody
{
	private:
		Vector2f force;//力
		Vector2f velocity;//线速度
		Vector2f acceleration;//线性加速度
		Vector2f angularVel;//角速度

		bool isSleep;//是否休眠
		bool isStatic;//是否静态物体
		float mass;//质量
		float inverseMass;//质量倒数
		float impulseCoefficient;//弹性系数
		float frictionCoefficient;//摩擦系数

		RigidBodyComponent* master;
		
	public:
		RigidBody();
		
		void InitializeCoeff(float mass, float impulseCoeff, float frictionCoeff);

		bool IsStatic();
		void SetStatic(bool isStatic);

		void SetMass(float m);
		float GetMass();
		float GetInverseMass();

		float GetImpulseCoefficient();
		void SetImpulseCoefficient(float coeff);

		float GetFrictionCoefficient();
		void SetFrictionCoefficient(float coeff);

		Vector2f GetForce();
		void SetForce(const Vector2f& force);

		Vector2f GetVelocity();
		void SetVelocity(const Vector2f& velocity);

		Vector2f GetAngularVelocity();
		void SetAngularVelocity(const Vector2f& angularVelocity);

		bool CheckIfSleep();


};

