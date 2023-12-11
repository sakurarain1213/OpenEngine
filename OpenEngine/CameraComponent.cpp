#include "CameraComponent.h"
#include<math.h>
#include"Renderer.h"
#include"ServiceLocator.h"
OpenEngine::CameraComponent::CameraComponent() {
	ViewMatrix <<   0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0;
	Position = { 0,0,0 };
	Front = { 0,0,0 };
	Up = { 0,0,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 0;
	FarClip = 0;
	Fov = 0;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

OpenEngine::CameraComponent::CameraComponent(Entity* entity) {
	mOwner = entity;
	ViewMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	Position = { 0,0,0 };
	Front = { 0,0,0 }; 
	Up = { 0,0,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 0;
	FarClip = 0;
	Fov = 0;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

int OpenEngine::CameraComponent::Initialize() {
	return 0;
}
void OpenEngine::CameraComponent::Finalize() {

}

OpenEngine::Mat4 OpenEngine::CameraComponent::GetViewMatrix() {
	
	if (VMdirtyflag) {
		Vec3 f = Front.normalized();
		Vec3 s = f;
		s = s.cross(Up);
		s.normalize();

		Vec3 u = s.cross(f);
		u.normalize();
		Mat4 Result;

		Result(0, 0) = s.x();
		Result(0, 1) = s.y();
		Result(0, 2) = s.z();
		Result(1, 0) = u.x();
		Result(1, 1) = u.y();
		Result(1, 2) = u.z();
		Result(2, 0) = -f.x();
		Result(2, 1) = -f.y();
		Result(2, 2) = -f.z();
		Result(0, 3) = -s.dot(Position);
		Result(1, 3) = -u.dot(Position);
		Result(2, 3) = f.dot(Position);
		Result(3, 0) = 0;
		Result(3, 1) = 0;
		Result(3, 2) = 0;
		Result(3, 3) = 0;
		ViewMatrix = Result;
	}

	return ViewMatrix;
}

OpenEngine::Mat4 OpenEngine::CameraComponent::GetProjectionMatrix() {
	if (PMdirtyflag) {
		float right, left, top, bottom;//NearClip,FarClip;
		top = NearClip * tan(Fov / 2);
		bottom = -top;
		right = 16 * top / 9;
		left = -right;
		float n = NearClip;
		float f = FarClip;
		Mat4 Result;
		Result <<
			n / right, 0, 0, 0,
			0, n / top, 0, 0,
			0, 0, -(f + n) / (f - n), (-2 * f * n) / (f - n),
			0, 0, -1, 0;

		ProjectionMatrix = Result;
		
	}
	
	return ProjectionMatrix;
}

OpenEngine::Vec3 OpenEngine::CameraComponent::GetPosition() {
	return Position;
}

void OpenEngine::CameraComponent::SetPosition(Vec3 posi) {
	Position = posi;
}

void OpenEngine::CameraComponent::SetFront(Vec3 front) {
	Front = front;
}
void OpenEngine::CameraComponent::SetUp(Vec3 up) {
	Up = up;
}

void OpenEngine::CameraComponent::SetNearClip(float d) {
	NearClip = d;
}
void OpenEngine::CameraComponent::SetFarClip(float d) {
	FarClip = d;
}
void OpenEngine::CameraComponent::SetFov(float d) {
	Fov = d;
}