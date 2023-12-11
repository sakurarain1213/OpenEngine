#include "ColliderComponent.h"
#include"Eigen/Dense"
#include"Math.h"

using namespace OpenEngine;

void OpenEngine::ColliderPlane::SetPoint(Vec3 p)
{
	this->point = p;
}

Vec3 OpenEngine::ColliderPlane::GetPoint()
{
	return this->point;
}

void OpenEngine::ColliderPlane::SetNormal(Vec3 n)
{
	this->normal = n;
}

Vec3 OpenEngine::ColliderPlane::GetNormal()
{
	return this->normal;
}

void OpenEngine::ColliderBox::SetMinPoint(Vec3 minPoint)
{
	this->minPoint = minPoint;
}

Vec3 OpenEngine::ColliderBox::GetMinPoint()
{
	return this->minPoint;
}

void OpenEngine::ColliderBox::SetMaxPoint(Vec3 maxPoint)
{
	this->maxPoint = maxPoint;
}

Vec3 OpenEngine::ColliderBox::GetMaxPoint()
{
	return this->maxPoint;
}

void OpenEngine::ColliderSphere::SetCenter(Vec3 c)
{
	this->center = c;
}

Vec3 OpenEngine::ColliderSphere::GetCenter()
{
	return this->center;
}

void OpenEngine::ColliderSphere::SetRadius(float r)
{
	this->radius = r;
}

float OpenEngine::ColliderSphere::GetRadius()
{
	return this->radius;
}