#pragma once

//����˴������������ �����ܶ�ϸcomponent  �߼���systemд
//��Ҫ import ...

#include"IComponent.h"
#include"Math.h"
#include<Eigen/Dense>  //?
#include"AABB.h"

namespace OpenEngine {
	class RigidBodyComponent : public IComponent
	{
    public:
        // ��������
        Vec3 force;
        Vec3 velocity;
        Vec3 acceleration;
        Vec3 angularVel;
        bool isSleep;
        bool isStatic;
        float mass;
        float inverseMass;
        float impulseCoefficient;
        Mat3 inertia;   //// ת������ - �ֲ��ռ�
        Mat3 inverseInertia;   // ת����������� - �ֲ��ռ�
        Mat3 inverseInertiaWs;   // ת����������� - ȫ�ֿռ�

        // ������ײ����������������ӽ�0 - �޸������������ȶ����ӽ�1 - �����޸������ǻ���ֲ��ȶ�����
        float contactBeta;
        // ������ײ������ķ���Ч�������Ϊ������ײϵ�����ӽ�0 - ��ȫ�ǵ�����ײ�ӽ�1 - ��ȫ������ײ
        float restitution;

        
        float frictionCoefficient;   // Ħ��

        AABB aabb;

    public:
        RigidBodyComponent();

        void InitializeCoeff(float mass, Mat3& inertia, float impulseCoeff, float frictionCoeff);
        // Set �� Get 

        void SetFrictionCoefficient(float f);

        bool IsStatic();
        void SetStatic(bool isStatic);

        float GetMass();
        void SetMass(float mass);
        float GetInverseMass();




        void SetAABB(AABB& ab) { aabb = ab; }
        AABB GetAABB(){ return aabb; }


        void SetForce(Vec3& f);
        Vec3 GetForce();

        void SetVelocity(Vec3& v);
        Vec3 GetVelocity();

        void SetAcceleration( Vec3& a) { acceleration = a; }
        Vec3 GetAcceleration() { return acceleration; }

        void SetAngularVelocity(Vec3& av);
        Vec3 GetAngularVelocity();

        void SetIsSleep(bool s) { isSleep = s; }
        bool GetIsSleep() { return isSleep; }

        bool CheckIfSleep();

        void SetIsStatic(bool s) { isStatic = s; }
        bool GetIsStatic() const { return isStatic; }






        void SetInertia(Mat3& i);
        Mat3 GetInertia();


        void SetInverseInertia(Mat3& ii) { inverseInertia = ii; }
        Mat3 GetInverseInertia();

        void SetInverseInertiaWs(Mat3& iiws) { inverseInertiaWs = iiws; }
        Mat3 GetInverseInertiaWs();


        void SetImpulseCoefficient(float ic);
        float GetImpulseCoefficient();



        void SetFriction(float fc);
        float GetFriction();


        void SetContactBeta(float cb) { contactBeta = cb; }
        float GetContactBeta() { return contactBeta; }

        void SetRestitution(float r) { restitution = r; }
        float GetRestitution() { return restitution; }

        

    };
}




