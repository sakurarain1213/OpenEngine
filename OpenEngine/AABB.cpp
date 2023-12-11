#include "AABB.h"

using namespace OpenEngine;   //aiMesh ºóÐø»áÒÀÀµ
using namespace Eigen;

void OpenEngine::AABB::Initialize(Vec3& minPoint, Vec3& maxPoint)
{
	this->minPoint = minPoint;
	this->maxPoint = maxPoint;
}

void OpenEngine::AABB::Initialize(aiMesh* mesh)
{
	float maxx = 0.0f;
	float minx = 0.0f;
	float maxy = 0.0f;
	float miny = 0.0f;
	float maxz = 0.0f;
	float minz = 0.0f;

	auto count = mesh->mNumVertices;
	auto data = mesh->mVertices;

	for (int idx = 0; idx < count; ++idx)
	{
		float x = data[idx].x;
		float y = data[idx].y;
		float z = data[idx].z;

		if (x < minx)
		{
			minx = x;
			minPoint[0] = x;
		}
		else if (x > maxx)
		{
			maxx = x;
			maxPoint[0] = x;
		}

		if (y < miny)
		{
			miny = y;
			minPoint[1] = y;
		}
		else if (y > maxy)
		{
			maxy = y;
			maxPoint[1] = y;
		}

		if (z < minz)
		{
			minz = z;
			minPoint[2] = z;
		}
		else if (z > maxz)
		{
			maxz = z;
			maxPoint[2] = z;
		}
	}
}

float  OpenEngine::AABB::btFsels(float x, float a, float b)
{
	if (x > 0)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// http://allenchou.net/2013/12/game-physics-collision-detection-csos-support-functions/
// support function
Vec3 OpenEngine::AABB::LocalGetSupportVertex(const Vec3& dir)
{
	return Vec3(
		btFsels(dir(0), maxPoint(0), -maxPoint(0)),
		btFsels(dir(1), maxPoint(1), -maxPoint(1)),
		btFsels(dir(2), maxPoint(2), -maxPoint(2))
	);
}




