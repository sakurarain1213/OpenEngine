#pragma once


//只存物理属性   逻辑在system写

#include"IComponent.h"
#include"Math.h"
#include<Eigen/Dense>  //?

namespace OpenEngine {

	enum ColliderType
	{
		Plane,
		Box,
		Sphere,
	};

	class RigidBodyComponent;

	class ColliderComponent : public IComponent
	{
	public:
		ColliderType GetColliderType()
		{
			return ct;
		}

		RigidBodyComponent* GetComponent()
		{
			return master;
		}

	protected:
		ColliderType ct;
		RigidBodyComponent* master;
	};


	class ColliderPlane : public ColliderComponent
	{
	public:
		ColliderPlane() :
			point(0, 0, 0),
			normal(0, 1, 0)
		{
			ct = ColliderType::Plane;
		}
	private:
		Vec3 point;
		Vec3 normal;

	public:
		void SetPoint(Vec3 p);
		Vec3 GetPoint();
		void SetNormal(Vec3 n);
		Vec3 GetNormal();
	};


	class ColliderBox : public ColliderComponent
	{
	public:
		ColliderBox() :
			minPoint(-0.5f, -0.5f, -0.5f),
			maxPoint(0.5f, 0.5f, 0.5f)
		{
			ct = ColliderType::Box;
		}

	private:
		Vec3 minPoint;
		Vec3 maxPoint;

	public:
		void SetMinPoint(Vec3 minPoint);
		Vec3 GetMinPoint();
		void SetMaxPoint(Vec3 maxPoint);
		Vec3 GetMaxPoint();


	};

	class ColliderSphere : public ColliderComponent
	{
	public:
		ColliderSphere() :
			center(0, 0, 0),
			radius(1.0f)
		{
			ct = ColliderType::Sphere;
		}
	private:
		Vec3 center;
		float radius;

	public:
		void SetCenter(Vec3 c);
		Vec3 GetCenter();
		void SetRadius(float r);
		float GetRadius();


	};
}




