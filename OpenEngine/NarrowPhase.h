#pragma once
#include <vector>

#include "Math.h"
#include "BoardPhase.h"
#include "Contact.h"
#include "Jacobian.h"
#include <Eigen/Dense>

namespace OpenEngine
{
	class RigidBodyComponent;

	class INarrowPhase
	{
	public:
		virtual void UpdateManifolds(std::vector<std::shared_ptr<ContactManifold>>& collisions) = 0;
		virtual void CollideDetection(std::vector<RigidBodyPair>& rigidBodies, std::vector<std::shared_ptr<ContactManifold>>& collisions) = 0;

	};


	struct sResults
	{
		enum eStatus
		{
			Separated,   /* Shapes doesnt penetrate												*/
			Penetrating, /* Shapes are penetrating												*/
			GJK_Failed,  /* GJK phase fail, no big issue, shapes are probably just 'touching'	*/
			EPA_Failed   /* EPA phase fail, bigger problem, need to save parameters, and debug	*/
		} status;

		Vector3f witnessInGlobal[2];
		Vector3f witnessesInFirstLocal[2];
		Vector3f normal;
		float distance;
	};

	//两个物体的Minkowski差，用于GJK和EPA碰撞检测算法
	struct MinkowskiDiff
	{
		RigidBodyComponent* box1;
		RigidBodyComponent* box2;

		inline Vector3f Support1(Vector3f dir);
		inline Vector3f Support2(Vector3f dir);
		Vector3f Support(Vector3f dir);
		Vector3f Support(Vector3f dir, int idx);
	};

	class NarrowPhaseGJKEPA : public INarrowPhase
	{
		//
		virtual void UpdateManifolds(std::vector<std::shared_ptr<ContactManifold>>& collisions);
		
		
		virtual void CollideDetection(std::vector<RigidBodyPair>& rigidBodies, std::vector<std::shared_ptr<ContactManifold>>&);


		void InitializeMinkowskiDiff(RigidBodyPair& pair, sResults& result, MinkowskiDiff& diff);//用于初始化Minkowski差
		
		//检测两个物体是否发生了穿透，通常在碰撞检测的GJK阶段
		bool Penetration(RigidBodyPair& pair, Vector3f& guess, sResults& result);

		//生成切线信息的函数，在检测到碰撞时调用
		void GenerateTangents(ContactPoint& contactPoint);



		//需要的数学工具类  归一化模=1
		Vector3f TransformPoint(Matrix4f matrix, Vector3f point)
		{
			Vector4f hSpace = Vector4f(point(0), point(1), point(2), 1);
			Vector4f tmp = Vector4f(0, 0, 0, 0);

			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					tmp(r) += hSpace(c) * matrix(r * 4 + c);
				}
			}
			return Vector3f(tmp(0), tmp(1), tmp(2));
		}

		
		/*
		template <template<typename>class TT, typename T>
		inline void Normalize(TT<T>& result)
		{
			T length;
			size_t count = ElementCount(result.data);
			length = result.dot(result);
			length = 1.0f / std::sqrt(length);
			for (size_t i = 0; i < count; ++i) {
				result(i) = result(i) * length;
			}
		}
		*/
		//模板函数错误  用vec3
		void Normalize(Vector3f& result)
		{
			float length;
			size_t count = 3;
			length = result.dot(result);
			length = 1.0f / std::sqrt(length);
			for (size_t i = 0; i < count; ++i) {
				result(i) = result(i) * length;
			}
		}


	};

}