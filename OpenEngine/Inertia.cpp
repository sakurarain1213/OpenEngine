#include "Inertia.h"
using namespace OpenEngine;
using namespace Eigen;  //?

// https://en.wikipedia.org/wiki/List_of_moments_of_inertia


Matrix3f OpenEngine::Inertia::CalculateInertiaSolidCuboid(float mass, float w, float h, float d)
{
	float v1 = 1.0 / 12 * mass * (h * h + d * d);
	float v2 = 1.0 / 12 * mass * (w * w + d * d);
	float v3 = 1.0 / 12 * mass * (h * h + w * w);
	Matrix3f ret;
	ret <<				//构造函数格式问题
		v1, 0, 0,
		0, v2, 0,
		0, 0, v3;
	return ret;
}

Matrix3f OpenEngine::Inertia::CalculateInertiaSolidSphere(float mass, float r)
{
	float v1 = 2 / 5 * mass * r * r;
	Matrix3f ret;
	ret <<				//构造函数格式问题
		v1, 0, 0,
		0, v1, 0,
		0, 0, v1;

	return ret;
}
