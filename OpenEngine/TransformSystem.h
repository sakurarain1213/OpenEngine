#pragma once
#include"ISystem.h"
#include<set>
#include"TransformComponent.h"
namespace OpenEngine {

	class World;
	

	class TransformSystem : public ISystem
	{
	public:
		TransformSystem(World* world);
	

		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		virtual void AddComponent(TransformComponent* comp);
		virtual void DeleteComponent(TransformComponent* comp);

	private:
		std::set<TransformComponent*> components;
		World* mWorld;
	};
}
