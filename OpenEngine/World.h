#pragma once
#include"IRuntimeModule.h"
#include"TransformSystem.h"
#include"UISystem.h"
#include"ISystem.h"
#include"CameraSystem.h"
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
		virtual void Finalize();
		virtual void Tick();

		World(std::string name);

		std::shared_ptr<Entity>	CreateEntity(std::string name);
		std::shared_ptr<Entity>	CreateEntity(std::string name, const boost::uuids::uuid& guid);
		void	DeleteEntity(const boost::uuids::uuid& guid);
		std::shared_ptr<Entity>	GetEntity(const boost::uuids::uuid& guid);
		size_t GetEntityCount();

		//void LoadScene(const std::string& scenePath);
		//void DumpEntities();
		

		TransformSystem* mTransformSystem;
		UISystem* mUISystem;
		CameraSystem* mCameraSystem;
	private:
		std::unordered_map<boost::uuids::uuid, std::shared_ptr<Entity>, boost::hash<boost::uuids::uuid>>	mEntities;

	};
}
