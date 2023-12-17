#pragma once

#include"ISystem.h"
#include"MonoBehaviour.h"
#include<set>
namespace OpenEngine {
	class World;
	class MonoBehaviourSystem :public ISystem 
	{
	public:

		MonoBehaviourSystem(World* world);

		virtual void AddComponent(MonoBehaviour* comp);
		virtual void DeleteComponent(MonoBehaviour* comp);

		int Initialize();
		void Finalize();
		void Tick();
		void FixedTick();


	private:
		std::set<MonoBehaviour*>components;
		World* mWorld;
	};
}