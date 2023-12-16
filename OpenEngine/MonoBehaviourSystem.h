#pragma once

#include"ISystem.h"
#include"MonoBehaviour.h"
#include<set>
namespace OpenEngine {
	class World;
	class MonoBehaviourSystem :public ISystem 
	{
	public:



		int Initialize();
		void Finalize();
		void Tick();



	private:
		std::set<MonoBehaviour*>components;
		World* mWorld;
	};
}