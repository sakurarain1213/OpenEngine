#include "RigidBodyComponent.h"
#include"Entity.h"
#include"Eigen/Dense"

using namespace OpenEngine;



OpenEngine::RigidBodyComponent::RigidBodyComponent()
{
	isSleep = true;
	force = Vec3(0, 0, 0);
	velocity = Vec3(0, 0, 0);
	acceleration = Vec3(0, 0, 0);
	angularVel = Vec3(0, 0, 0);

	SetStatic(false);
}


void OpenEngine::RigidBodyComponent::InitializeCoeff(float mass,  Mat3& inertia, float impulseCoeff, float frictionCoeff)
{
	SetMass(mass);
	SetInertia(inertia);
	SetImpulseCoefficient(impulseCoeff);
	SetFrictionCoefficient(frictionCoeff);
}

void OpenEngine::RigidBodyComponent::SetFrictionCoefficient(float frictionCoeff)
{
	this->frictionCoefficient = frictionCoeff;
}

bool OpenEngine::RigidBodyComponent::IsStatic()
{
	return this->isStatic;
}

void OpenEngine::RigidBodyComponent::SetStatic(bool isStatic)
{
	this->isStatic = isStatic;
}

void OpenEngine::RigidBodyComponent::SetMass(float mass)
{
	this->mass = mass;
	this->inverseMass = 1.0f / mass;
}

float OpenEngine::RigidBodyComponent::GetMass()
{
	return this->mass;
}

float OpenEngine::RigidBodyComponent::GetInverseMass()
{
	return this->inverseMass;
}

void OpenEngine::RigidBodyComponent::SetInertia( Mat3& inertia)
{
	this->inertia = inertia;
	this->inverseInertia= inertia.inverse();
}

Mat3 OpenEngine::RigidBodyComponent::GetInertia()
{
	return this->inertia;
}

Mat3 OpenEngine::RigidBodyComponent::GetInverseInertia()
{
	return this->inverseInertia;
}

Mat3 OpenEngine::RigidBodyComponent::GetInverseInertiaWs()
{
	return inverseInertiaWs;
}

float OpenEngine::RigidBodyComponent::GetImpulseCoefficient()
{
	return this->impulseCoefficient;
}

void OpenEngine::RigidBodyComponent::SetImpulseCoefficient(float coeff)
{
	if (coeff > 1.0f)
	{
		coeff = 1.0f;
	}
	else if (coeff < 0.0f)
	{
		coeff = 0.0f;
	}
	this->impulseCoefficient = coeff;
}

float OpenEngine::RigidBodyComponent::GetFriction()
{
	return this->frictionCoefficient;
}

void OpenEngine::RigidBodyComponent::SetFriction(float coeff)
{
	this->frictionCoefficient = coeff;
}

Vec3 OpenEngine::RigidBodyComponent::GetForce()
{
	return this->force;
}

void OpenEngine::RigidBodyComponent::SetForce( Vec3& force)
{
	this->force = force;
}

Vec3 OpenEngine::RigidBodyComponent::GetVelocity()
{
	return this->velocity;
}

void OpenEngine::RigidBodyComponent::SetVelocity( Vec3& velocity)
{
	this->velocity = velocity;
}

Vec3 OpenEngine::RigidBodyComponent::GetAngularVelocity()
{
	return this->angularVel;
}

void OpenEngine::RigidBodyComponent::SetAngularVelocity( Vec3& angularVelocity)
{
	this->angularVel = angularVelocity;
}

bool OpenEngine::RigidBodyComponent::CheckIfSleep()
{
	return false;
}




