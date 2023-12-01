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
		virtual int Initialize() ;
		virtual int Initialize(World* world);
		virtual void Finalize() ;


		Entity();
		Entity(int id);
		virtual ~Entity();

		void SetEid(int id);
		int GetEid();
		void AddChild(std::shared_ptr<Entity> child);
		void RemoveChild(std::shared_ptr<Entity>child);
		Entity* GetParent();
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

	template<typename T>
	T* OpenEngine::Entity::AddComponent() {
		void* comp = nullptr;
		if (std::is_same<T, TransformComponent>::value) {
			TransformComponent* mTransform = new TransformComponent();
			mTransform->SetOwner(this);
			Components.push_back(mTransform);
			comp = mTransform;
		}
		return comp;
	}
}