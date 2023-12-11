#pragma once

#include <Eigen/Dense>

namespace OpenEngine {
	using Vec4 = Eigen::Vector4f;
	using Vec3 = Eigen::Vector3f;
	using Vec2 = Eigen::Vector2f;
	using Mat3 = Eigen::Matrix3f;
	using Mat4 = Eigen::Matrix4f;



	template <typename T>
	struct Vector3Type {
		union {
			T data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vector3Type<T>() {};
		Vector3Type<T>(const T& _v) : x(_v), y(_v), z(_v) {};
		Vector3Type<T>(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};

		operator T* () { return data; };
		operator const T* () const { return static_cast<const T*>(data); };

		Vector3Type<T> operator+(const Vector3Type<T>& rhs) {
			Vector3Type<T> res;
			res.x = x + rhs.x;
			res.y = y + rhs.y;
			res.z = z + rhs.z;
			return res;
		}

		Vector3Type<T> operator-(const Vector3Type<T>& rhs) {
			Vector3Type<T> res;
			res.x = x - rhs.x;
			res.y = y - rhs.y;
			res.z = z - rhs.z;
			return res;
		}

		Vector3Type<T> operator*(T scale) {
			Vector3Type<T> res;
			res.x = x * scale;
			res.y = y * scale;
			res.z = z * scale;
			return res;
		}


	};

	using Qua = Eigen::Quaternionf;

	
}