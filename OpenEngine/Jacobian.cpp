#include "Jacobian.h"
#include "Contact.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"



/*
这里的dir是在某个方向上解决约束。1个法线方向和2个切线方向。
法线方向前面定义为A指向B
*/
void OpenEngine::Jacobian::Init(std::shared_ptr<ContactManifold> manifold, int idx, JacobianType jt, Eigen::Vector3f dir, float dt)
{
	jacobinType = jt;

	m_jva = dir * -1;
	m_jwa = manifold->contactPoints[idx].rA.cross(dir) * -1;
	m_jvb = dir;
	m_jwb = manifold->contactPoints[idx].rB.cross(dir);

	m_bias = 0.0f;

	if (jacobinType == JacobianType::Normal)
	{
		float betaA = manifold->colliderA->GetContactBeta();
		float betaB = manifold->colliderB->GetContactBeta();
		float beta = betaA * betaB;

		float restitutionA = manifold->colliderA->GetRestitution();
		float restitutionB = manifold->colliderB->GetRestitution();
		float restitution = restitutionA * restitutionB;


		Vec3 va = manifold->colliderA->GetVelocity();
		Vec3 wa = manifold->colliderA->GetAngularVelocity();
		Vec3 ra = manifold->contactPoints[idx].rA;

		Vec3 vb = manifold->colliderB->GetVelocity();
		Vec3 wb = manifold->colliderB->GetAngularVelocity();
		Vec3 rb = manifold->contactPoints[idx].rB;

		m_bias = 0;
		if (jacobinType == JacobianType::Normal)
		{
			// 推导方式具体可以看
			// http://allenchou.net/2013/12/game-physics-resolution-contact-constraints/
			Vector3f relativeVelocity = vb + wb.cross( rb) - va -wa.cross(ra);
			float closingVelocity = relativeVelocity.dot(dir);
			m_bias = -(beta / dt) * manifold->contactPoints[idx].penetrationDistance + restitution * closingVelocity;
		}
	}

	// http://allenchou.net/2013/12/game-physics-constraints-sequential-impulse/
	// https://www.youtube.com/watch?v=pmdYzNF9x34
	// 视频里面有 effectiveMass 的算法。
	// 不过这里的计算依然没理解得太透彻
	auto rigidA = manifold->colliderA;
	auto rigidB = manifold->colliderB;

	Vec3 rva = rigidA->GetInverseInertia() * m_jwa;
	Vec3 rvb = rigidB->GetInverseInertia() * m_jwb;

	float k =
		rigidA->GetInverseMass() + rigidB->GetInverseMass()
		+ m_jwa.dot(rva)
		+ m_jwb.dot(rvb);

	m_effectiveMass = 1 / k;
	m_totalLambda = 0;
}

void OpenEngine::Jacobian::Solve(std::shared_ptr<ContactManifold> manifold, int idx, Vector3f dir, float dt)
{

	ContactPoint& point = manifold->contactPoints[idx];

	float jv = m_jva.dot(manifold->colliderA->GetVelocity())
		+ m_jwa.dot(manifold->colliderA->GetAngularVelocity())
		+ m_jvb.dot(manifold->colliderB->GetVelocity())
		+ m_jwb.dot(manifold->colliderB->GetAngularVelocity());

	float lambda = m_effectiveMass * (-(jv + m_bias));
	float oldTotalLambda = m_totalLambda;
	switch (jacobinType)
	{
	case JacobianType::Normal:
		m_totalLambda = std::max(m_totalLambda + lambda, 0.0f);
		break;

	case JacobianType::Tangent:
		float friction = manifold->colliderA->GetFriction() * manifold->colliderB->GetFriction();
		float maxFriction = friction * point.m_jN.m_totalLambda;
		m_totalLambda = Clamp(m_totalLambda + lambda, -maxFriction, maxFriction);
		break;
	}
	lambda = m_totalLambda - oldTotalLambda;

	Vec3 va = manifold->colliderA->GetVelocity();
	Vec3 vadelta = m_jva * manifold->colliderA->GetInverseMass() * lambda;

	Vec3 tempset(va + vadelta);
	manifold->colliderA->SetVelocity(tempset);

	Vec3 wa = manifold->colliderA->GetAngularVelocity();
	Vec3 wadelta = manifold->colliderA->GetInverseInertiaWs() * m_jwa * lambda;

	tempset = (wa + vadelta);
	manifold->colliderA->SetAngularVelocity(tempset);

	Vec3 vb = manifold->colliderB->GetVelocity();
	Vec3 vbdelta = m_jvb * manifold->colliderB->GetInverseMass() * lambda;

	tempset = (vb + vadelta);
	manifold->colliderB->SetVelocity(tempset);

	Vec3 wb = manifold->colliderB->GetAngularVelocity();
	Vec3 wbdelta = manifold->colliderB->GetInverseInertiaWs() * m_jwb * lambda;

	tempset = (wb + vadelta);
	manifold->colliderB->SetAngularVelocity(tempset);

}
