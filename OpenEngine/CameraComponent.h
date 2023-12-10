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

		Mat4 GetViewMatrix() {

		}
	private:
		

		Mat4 ViewMatrix;
		Vec3 Position;
		Vec3 Lookat;//N
		Vec3 Up;//U

		Mat4 ProjectionMatrix;
		float NearClip;
		float FarClip;

		float Fov;


	};
}

