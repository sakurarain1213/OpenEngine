#pragma once
#include"IRuntimeModule.h"
#include"TransformSystem.h"
#include"ISystem.h"
#include<memory>
#include<string>
#include<list>
#include <boost/functional/hash.hpp>
#include<boost/uuid/uuid.hpp>
namespace OpenEngine {
	class Entity;
	class World : public IRuntimeModule
	{
	public:
		virtual std::string GetType();
		virtual int Initialize();
		virtual void Finalize() = 0;
		virtual void Tick();

		World(std::string name);

		std::shared_ptr<Entity>	CreateEntity(std::string name);
		std::shared_ptr<Entity>	CreateEntity(std::string name,int id);
		void	DeleteEntity(int id);
		std::shared_ptr<Entity>	GetEntity(int id);
		size_t GetEntityCount();

		void LoadScene(const std::string& scenePath);
		void DumpEntities();


		std::list<ISystem*> Systems;

		TransformSystem* mTransformSystem;

	private:
		std::unordered_map<boost::uuids::uuid, std::shared_ptr<Entity>, boost::hash<boost::uuids::uuid>>	mEntities;
	};
}
