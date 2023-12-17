#include "TransformComponent.h"
#include"Entity.h"
#include"Eigen/Dense"

using namespace OpenEngine;

OpenEngine::TransformComponent::TransformComponent() {
	Scale = { 1,1,1 };
	Position = { 0,0,0 };
	//LinearVelocity = { 0,0,0 };
	Rotation = { 0,0,0,0 };
	//AngularVelocity = { 0,0,0,0 };
	mOwner = nullptr;
	mIsActive = true;
	ModelMatrixdirtyflag = true;
}

OpenEngine::TransformComponent::TransformComponent(Entity* entity) {
	Scale = { 1,1,1 };
	Position = { 0,0,0 };
	Rotation = { 0,0,0 ,0 };
	//LinearVelocity = { 0,0,0 };
	//AngularVelocity = { 0,0,0,0 };
	mOwner = entity;
	mIsActive = true;
	ModelMatrixdirtyflag = true;
}
int OpenEngine::TransformComponent::Initialize() {
	return 0;
}
void OpenEngine::TransformComponent::Finalize() {

}
void OpenEngine::TransformComponent::SetPosition(Vector3f posi) {
	Position = posi;
}

void OpenEngine::TransformComponent::Rotate(Quaternionf rota) {
	Rotation = rota;
}
void OpenEngine::TransformComponent::SetScale(Vec3 scale) {
	Scale = scale;
}
/*
void OpenEngine::TransformComponent::SetLinearVelocity(Vector3f vel) {
	LinearVelocity = vel;
}

void OpenEngine::TransformComponent::SetAngularVelocity(Quaternionf vel) {
	AngularVelocity = vel;
}
*/
Vector3f OpenEngine::TransformComponent::GlobalVectorToLocalVector(Vector3f globalVector)
{
	Matrix4f world2local = GetWorldMatrixInverse();
	Vector3f localVector = TransformVector(world2local, globalVector);
	return localVector;
}

Vector3f OpenEngine::TransformComponent::LocalPointToGlobalPoint(Vector3f localPoint)
{
	Matrix4f local2world = GetWorldMatrix();
	Vector3f globalPoint = TransformPoint(local2world, localPoint);
	return globalPoint;
}

Vector3f OpenEngine::TransformComponent::TransformPoint(Matrix4f matrix, Vector3f point)
{
	Vector4f hSpace = Vector4f(point[0], point[1], point[2], 1);
	Vector4f tmp = Vector4f(0, 0, 0, 0);

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			tmp(r) += hSpace(c) * matrix(r * 4 + c);
		}
	}
	return Vector3f(tmp(0), tmp(1), tmp(2));
}



Vector3f OpenEngine::TransformComponent::TransformVector(Matrix4f& matrix, Vector3f& vector)
{
	Vector4f hSpace = Vector4f(vector(0), vector(1), vector(2), 0);
	Vector4f tmp = Vector4f(0, 0, 0, 0);

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			tmp(r) += hSpace(c) * matrix(r * 4 + c);
		}
	}
	return Vector3f(tmp(0), tmp(1), tmp(2));
}

Vector3f OpenEngine::TransformComponent::TransformVector(Matrix3f& matrix, Vector3f& vector)
{
	Vector3f tmp = Vector3f(0, 0, 0);
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			tmp(r) += vector(c) * matrix(r * 3 + c);   //!   访问矩阵要用小括号  不然会报Eigen内部错误
		}
	}
	return tmp;
}

Mat4 OpenEngine::TransformComponent::GetModelMatrix() {
	if (ModelMatrixdirtyflag) {
		Mat4 scaleM;
		scaleM <<
			Scale.x(), 0, 0, 0,
			0, Scale.y(), 0, 0,
			0, 0, Scale.z(), 0,
			0, 0, 0, 1;

		Rotation.normalized();
		Mat3 rot3=Rotation.toRotationMatrix();
		Mat4 rotM;
		rotM <<
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				rotM(i, j) = rot3(i, j);
			}
		}
		rotM(3, 3) = 1;
		Mat4 posiM;
		posiM <<
			1, 0, 0, Position.x(),
			0, 1, 0, Position.y(),
			0, 0, 1, Position.z(),
			0, 0, 0, 1;
		
		ModelMatrix = posiM*(rotM * scaleM);
		ModelMatrixdirtyflag = false;
	}

	return ModelMatrix;
}