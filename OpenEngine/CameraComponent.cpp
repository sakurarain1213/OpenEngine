#include "CameraComponent.h"
#include<iostream>
#include<math.h>
#include"Renderer.h"
#include"ServiceLocator.h"
OpenEngine::CameraComponent::CameraComponent() {
	ViewMatrix <<   0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0,
					0, 0, 0, 0;
	Position = { 0,0,20 };
	Center = { 0,0,1 };
	Up = { 0,1,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 1;
	FarClip = 50;
	Fov = 0.6;
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
	Center = { 0,0,1 };
	Up = { 0,1,0 };
	ProjectionMatrix << 0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0;
	NearClip = 10;
	FarClip = 30;
	Fov = 0.5;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

int OpenEngine::CameraComponent::Initialize() {
	return 0;
}
void OpenEngine::CameraComponent::Finalize() {

}

OpenEngine::Mat4 OpenEngine::CameraComponent::GetViewMatrix() {
	
	
		Vec3 z((Position - Center).normalized());
		std::cout << z << std::endl;
		//Vec3 x(z.cross(Up).normalized());
		//Vec3 y(x.cross(z));

		Mat4 result;

		result[0] = x.x();
		result[4] = x.y();
		result[8] = x.z();
		result[12] = -x.dot(Position);

		result[1] = y.x();
		result[5] = y.y();
		result[9] = y.z();
		result[13] = -y.dot(Position);

		result[2] = z.x();
		result[6] = z.y();
		result[10] = z.z();
		result[14] = -z.dot(Position);

		result[3] = result[7] = result[11] = 0.0f;
		result[15] = 1.0f;
		
		ViewMatrix = result;
		VMdirtyflag = false;
	

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
	return Position;
}

void OpenEngine::CameraComponent::SetPosition(Vec3 posi) {
	Position = posi;
	VMdirtyflag = true;
	PMdirtyflag = true;
}

void OpenEngine::CameraComponent::SetFront(Vec3 front) {
	Center = front;
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