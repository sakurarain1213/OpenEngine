#pragma once


#include "Eigen/Dense"
#include "Math.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"

namespace OpenEngine
{
	class AABB				//�����ı߽��  ��ײ���
	{
	public:
		void Initialize(Vec3& minPoint, Vec3& maxPoint);
		void Initialize(aiMesh* mesh);

		float btFsels(float x, float a, float b);
		Vec3 LocalGetSupportVertex(const Vec3& dir);

	public:
		Vec3 minPoint;
		Vec3 maxPoint;

	};
}