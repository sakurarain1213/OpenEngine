#pragma once
#include"ISystem.h"
#include<set>

namespace OpenEngine {

	class World;
	class TransformComponent;

	class TransformSystem : public ISystem
	{
	public:
		TransformSystem(World* world);
		std::string GetType() {
			return "TransformSystem";
		};

		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();

		virtual void AddComponent(TransformComponent* comp);
		virtual void DeleteComponent(TransformComponent* comp);

	private:
		std::set<TransformComponent*> components;
	};
}
