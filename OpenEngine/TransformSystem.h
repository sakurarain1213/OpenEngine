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
