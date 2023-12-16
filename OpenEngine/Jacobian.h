#pragma once
#include <vector>
#include "Math.h"
#include "Eigen/Dense"

#include <Eigen/Dense>
//雅可比矩阵，力和运动的转换

namespace OpenEngine
{
	class ContactManifold;

	enum JacobianType
	{
		Normal,
		Tangent
	};

	struct  Jacobian
	{
		Jacobian(JacobianType jt)
		{
			m_jva = Vec3(0, 0, 0);
			m_jwa = Vec3(0, 0, 0);
			m_jvb = Vec3(0, 0, 0);
			m_jwa = Vec3(0, 0, 0);

		}

		
		void Init(std::shared_ptr<ContactManifold> manifold, int idx, JacobianType jt, Eigen::Vector3f dir, float dt);
		
		void Solve(std::shared_ptr<ContactManifold> manifold, int idx, Vec3 dir, float dt);

		JacobianType jacobinType;
		Vec3 m_jva;
		Vec3 m_jwa;
		Vec3 m_jvb;
		Vec3 m_jwb;
		float m_bias;
		float m_effectiveMass;
		float m_totalLambda;



		//强耦合的数学方法
		// 添加 CrossProduct DotProduct函数
		/*   eigrn内部 报protected 先不用    访问矩阵要用()  不能{]
	public:
		template <template<typename> class TT, typename T>
		inline void CrossProduct(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2) {
			result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
			result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
		}
	
		
		template <template<typename> class TT, typename T>
		 inline TT<T>  CrossProduct(const TT<T>& vec1, const TT<T>& vec2) {
			TT<T> result;
			result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
			result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
			return result;
		}
	*/
		//向量点乘   可以直接用库函数.dot
		template <template<typename> class TT, typename T>
		inline T DotProduct(const TT<T>& vec1, const TT<T>& vec2) {
			size_t count = ElementCount(vec1.data);
			T result = 0;
			for (size_t i = 0; i < count; ++i) {
				result += vec1[i] * vec2[i];
			}
			return result;
		}

		inline float Clamp(float v, float a, float b)
		{
			if (v < a)	return a;
			if (v > b)	return b;
			return v;
		}
		/*   库函数直接乘  
		inline Vector3f TransformVector(const Matrix4f& matrix, Vector3f& vector)
		{
			Vector4f hSpace = Vector4f(vector[0], vector[1], vector[2], 0);
			Vector4f tmp = Vector4f(0, 0, 0, 0);

			for (int r = 0; r < 4; ++r) {
				for (int c = 0; c < 4; ++c) {
					tmp[r] += hSpace[c] * matrix[r][c];
				}
			}
			return Vector3f(tmp[0], tmp[1], tmp[2]);
		}

		inline Vector3f TransformVector(const Matrix3f& matrix, Vector3f& vector)
		{
			Vector3f tmp = Vector3f(0, 0, 0);
			for (int r = 0; r < 3; ++r) {
				for (int c = 0; c < 3; ++c) {
					tmp[r] += vector[c] * matrix[r][c];
				}
			}
			return tmp;
		}
		*/


	};

}