#pragma once
#include"MonoBehaviour.h"
using namespace OpenEngine;
namespace OpenEngine {
	class Move : public MonoBehaviour
	{

	public:
		Move(Entity* entity);

		virtual int Initialize();
		virtual void Update();

	};
}

