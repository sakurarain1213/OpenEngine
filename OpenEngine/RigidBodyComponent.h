#pragma once

//耦合了大多数物理属性 舍弃很多细component  逻辑在system写
//需要 import ...

#include"IComponent.h"
#include"Math.h"
#include<Eigen/Dense>  //?
#include"AABB.h"
#include"TransformComponent.h"


namespace OpenEngine {
	class RigidBodyComponent : public IComponent
	{
    public:
        // 物理属性
        Vec3 force;
        Vec3 velocity;
        Vec3 acceleration;
        Vec3 angularVel;
        bool isSleep;
        bool isStatic;
        float mass;
        float inverseMass;
        float impulseCoefficient;
        Mat3 inertia;   //// 转动惯量 - 局部空间
        Mat3 inverseInertia;   // 转动惯量逆矩阵 - 局部空间
        Mat3 inverseInertiaWs;   // 转动惯量逆矩阵 - 全局空间

        // 描述碰撞发生后的修正参数接近0 - 修复缓慢，但是稳定。接近1 - 快速修复，但是会出现不稳定现象。
        float contactBeta;
        // 描述碰撞发生后的反弹效果，理解为弹性碰撞系数。接近0 - 完全非弹性碰撞接近1 - 完全弹性碰撞
        float restitution;

        
        float frictionCoefficient;   // 摩擦

        AABB aabb;

    public:
        RigidBodyComponent();
        RigidBodyComponent(Entity* owner);

        int Initialize() { return 0; }
        void Finalize() {}

        void InitializeCoeff(float mass, Mat3& inertia, float impulseCoeff, float frictionCoeff);
        // Set 和 Get 

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

        //物理方法计算矩阵
        /*
        计算全局坐标下的惯性张量
        惯性张量的坐标变化满足：
        $I_w = R * I_l * R^T$
        https://www.zhihu.com/question/24846969
        这里I指物体在局部坐标下的惯性张量
        这里R指物体的局部到全局的旋转矩阵
        另外，旋转矩阵满足正交归一特性，逆等于转置
        左右求逆矩阵可以得到下面等式
        */
        void UpdateInverseInertiaWs();
       

    };
}




