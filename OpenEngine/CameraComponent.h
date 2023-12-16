#pragma once
#include"IComponent.h"
#include"Math.h"
//暂时用不到的 实体  （不应该用component）
namespace OpenEngine {
	class CameraComponent : IComponent
	{
	public:
		
		CameraComponent(Entity* entity);
		CameraComponent();

		virtual int Initialize();
		virtual void Finalize();

		Mat4 GetViewMatrix();
		Mat4 GetProjectionMatrix();
		Vec3 GetPosition();

		void SetPosition(Vec3 posi);
		void SetFront(Vec3 front);
		void SetUp(Vec3 up);

		void SetNearClip(float d);
		void SetFarClip(float d);
		void SetFov(float d);
	private:
		
		bool VMdirtyflag;//true则重新计算矩阵
		Mat4 ViewMatrix;
		Vec3 Position;
		Vec3 Front;//向前的向量   center（焦点）可由Pos+Front得到
		Vec3 Up;//向上   Right 可由Front cross Up得到

		bool PMdirtyflag;
		Mat4 ProjectionMatrix;
		float NearClip;
		float FarClip;

		float Fov;//


	};
}

