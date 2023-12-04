#pragma once
#include"IComponent.h"
#include"IRuntimeModule.h"
#include"TransformComponent.h"
#include<vector>
#include<list>
#include<memory>
namespace OpenEngine {
	class World;
	class Entity : public IRuntimeModule
	{
	public:
		virtual std::string GetType();
		virtual int Initialize() ;
		virtual int Initialize(World* world);
		virtual void Finalize() ;
		virtual void Tick();

		
		Entity(std::string name);
		Entity(std::string name,int id);
		virtual ~Entity();

		void SetEid(int id);
		int GetEid();
		void AddChild(std::shared_ptr<Entity> child);
		void RemoveChild(std::shared_ptr<Entity>child);
		Entity* GetParent();
		void SetWorld(World* world);
		World* GetWorld();
		void SetParent(Entity* parent);
		bool IsChild(std::shared_ptr<Entity>child);
		size_t GetChildrenCount();

		
		template<typename T>T* AddComponent(){};

		std::list<IComponent*> Components;

	private:
		int Eid;
		std::vector<std::shared_ptr<Entity>> mchildrenE;
		Entity* mParent;
		World* mWorld;

	};

	
}