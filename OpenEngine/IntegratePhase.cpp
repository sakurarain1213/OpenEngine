#include "IntegratePhase.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "Eigen/Dense"



void OpenEngine::IntegratePhase::integrate(std::vector<RigidBodyComponent*> activedRigidBodies, float dt)
{
	for (auto* rigidBodyComponent :activedRigidBodies)
	{
		if (rigidBodyComponent->IsStatic())
		{
			Vector3f tempset(0, 0, 0);
			rigidBodyComponent->SetVelocity(tempset);
			rigidBodyComponent->SetAngularVelocity(tempset);
			continue;
		}

		// 更新位置   
		
		//拿到所属实体的另外一个component
		TransformComponent* transform = rigidBodyComponent->GetOwner()->GetComponent<TransformComponent>();
		auto position = transform->GetPosition();
		Vector3f newPosition;
		Vector3f v = rigidBodyComponent->GetVelocity();
		newPosition=position+v*dt;
		transform->SetPosition(newPosition);

		// 更新朝向
		// omega: angular velocity (direction is axis, magnitude is angle)
		// https://fgiesen.wordpress.com/2012/08/24/quaternion-differentiation/
		// https://www.ashwinnarayan.com/post/how-to-integrate-quaternions/
		// https://gafferongames.com/post/physics_in_3d/

		Quaternion rotation = transform->GetRotation();

		Vector3f omega = rigidBodyComponent->GetAngularVelocity();
		dt *= 0.5f;
		Quaternion delta(omega(0) * dt, omega(1) * dt, omega(2) * dt, 1.0f);  //不用Omega.x .y
		Quaternion target = delta * rotation;
		transform->Rotate(target); //setRotate

	}
}

