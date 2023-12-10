#pragma once
#include"ISystem.h"
#include<set>
#include"ButtonComponent.h"



namespace OpenEngine {
	class World;
	class UISystem : public ISystem {
	public:
		UISystem(World* world);


		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		virtual void AddComponent(ButtonComponent* comp);
		virtual void DeleteComponent(ButtonComponent* comp);

	private:
		std::set<ButtonComponent*> components;
		World* mWorld;

	
	};
}