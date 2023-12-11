#pragma once
#include "Math.h"

//πﬂ–‘ Ù–‘
namespace OpenEngine
{
	using namespace Eigen;  //?
	class Inertia
	{
	public:
		static Matrix3f CalculateInertiaSolidCuboid(float mass, float w, float h, float d);
		static Matrix3f CalculateInertiaSolidSphere(float mass, float r);
	};
}