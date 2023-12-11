#include "CameraComponent.h"

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
}

int OpenEngine::CameraComponent::Initialize() {
	return 0;
}
void OpenEngine::CameraComponent::Finalize() {

}

OpenEngine::Mat4 OpenEngine::CameraComponent::GetViewMatrix() {
	
	
	Vec3 f = Front.normalized();
	Vec3 s = f;
	s=s.cross(Up);
	s.normalize();
	
	Vec3 u = s.cross(f);
	u.normalize();
	Mat4 Result;

	Result(0,0) = s.x();
	Result(0,1) = s.y();
	Result(0,2) = s.z();
	Result(1,0) = u.x();
	Result(1,1) = u.y();
	Result(1,2) = u.z();
	Result(2,0) = -f.x();
	Result(2,1) = -f.y();
	Result(2,2) = -f.z();
	Result(0,3) = -s.dot(Position);
	Result(1,3) = -u.dot(Position);
	Result(2,3) = f.dot(Position);
	Result(3,0) = 0;
	Result(3,1) = 0;
	Result(3,2) = 0;
	Result(3,3) = 0;
	return Result;
}