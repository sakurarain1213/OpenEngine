#pragma once
#include"IComponent.h"
#include"Math.h"
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
		
	private:
		
		bool VMdirtyflag;//true则需要修改矩阵
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

