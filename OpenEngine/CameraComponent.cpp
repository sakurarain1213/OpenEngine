#include "CameraComponent.h"
#include<iostream>
#include"Entity.h"
#include<math.h>

OpenEngine::CameraComponent::CameraComponent() {
	ViewMatrix <<   0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0;
	Position = { 0,0,20 };
	Front = { 0,0,-1 };
	Up = { 0,1,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 1;
	FarClip = 50;
	Fov = 1;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

OpenEngine::CameraComponent::CameraComponent(Entity* entity) {
	mOwner = entity;
	ViewMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	Position = { 0,0,20 };
	Front = { 0,0,-1 };
	Up = { 0,1,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 1;
	FarClip = 50;
	Fov = 1;
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
		Vec3 p = GetPosition();
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
		Result(0, 3) = -s.dot(p);
		Result(1, 3) = -u.dot(p);
		Result(2, 3) = f.dot(p);
		Result(3, 0) = 0;
		Result(3, 1) = 0;
		Result(3, 2) = 0;
		Result(3, 3) = 1;
		ViewMatrix = Result;
		VMdirtyflag = false;
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
		PMdirtyflag = false;
	}
	
	return ProjectionMatrix;
}

OpenEngine::Vec3 OpenEngine::CameraComponent::GetPosition() {
	return this->GetOwner()->GetComponent<TransformComponent>()->GetPosition();
}

void OpenEngine::CameraComponent::SetPosition(Vec3 posi) {
	this->GetOwner()->GetComponent<TransformComponent>()->SetPosition(posi);
	Position = posi;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

void OpenEngine::CameraComponent::SetFront(Vec3 front) {
	Front = front;
	VMdirtyflag = true;
	PMdirtyflag = true;
}
void OpenEngine::CameraComponent::SetUp(Vec3 up) {
	Up = up;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

void OpenEngine::CameraComponent::SetNearClip(float d) {
	NearClip = d; VMdirtyflag = true;
	PMdirtyflag = true;
}
void OpenEngine::CameraComponent::SetFarClip(float d) {
	FarClip = d;
	VMdirtyflag = true;
	PMdirtyflag = true;
}
void OpenEngine::CameraComponent::SetFov(float d) {
	Fov = d;
	VMdirtyflag = true;
	PMdirtyflag = true;
}