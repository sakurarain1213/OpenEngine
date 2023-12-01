#pragma once
#include"IRuntimeModule.h"
#include"TransformSystem.h"
#include"ISystem.h"
#include<memory>
#include<string>
#include<list>
namespace OpenEngine {
	class Entity;
	class World : public IRuntimeModule
	{
	public:
		virtual int Initialize();
		virtual void Finalize() = 0;
		virtual void Tick();

		World();

		std::shared_ptr<Entity>	CreateEntity();
		std::shared_ptr<Entity>	CreateEntity(int id);
		void	DeleteEntity(int id);
		std::shared_ptr<Entity>	GetEntity(int id);
		size_t GetEntityCount();

		void LoadScene(const std::string& scenePath);
		void DumpEntities();


		std::list<ISystem*> Systems;

		TransformSystem* mTransformSystem;

	};
}
