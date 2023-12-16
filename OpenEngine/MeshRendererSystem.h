#pragma once
#include"ISystem.h"
#include"MeshRendererComponent.h"

#include<set>
namespace OpenEngine {
	class World;
	class MeshRendererSystem : public ISystem
	{
	public:
		MeshRendererSystem(World* world);

		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		virtual void AddComponent(MeshRendererComponent* comp);
		virtual void DeleteComponent(MeshRendererComponent* comp);
		
	private:
		std::set<MeshRendererComponent*>components;
		World* mWorld;
	};
}
