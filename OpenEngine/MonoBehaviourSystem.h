#pragma once

#include"ISystem.h"
#include<set>
namespace OpenEngine {
	class MonoBehaviourSystem :public ISystem 
	{
	public:

		int Initialize();
		void Finalize();
		void Tick();

	private:
		std::set<MeshRendererComponent*>components;
		World* mWorld;
	};
}