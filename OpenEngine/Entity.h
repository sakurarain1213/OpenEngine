#pragma once
#include"IComponent.h"
#include"IRuntimeModule.h"
#include"TransformComponent.h"
#include<vector>
#include<list>
#include<memory>
#include <boost/uuid/uuid.hpp>
namespace OpenEngine {
	class World;
	class Entity : public IRuntimeModule
	{
	public:
		virtual std::string GetType();
		virtual int Initialize() ;
		virtual int Initialize(World* world);
		virtual void Finalize() ;
		

		
		Entity(std::string name);
		Entity(std::string name, const boost::uuids::uuid& guid);
		virtual ~Entity();
		boost::uuids::uuid	GetGuid() const noexcept;
		void	SetGuid(const boost::uuids::uuid& guid) noexcept;
		boost::uuids::uuid GetGuid();
		void AddChild(std::shared_ptr<Entity> child);
		void RemoveChild(std::shared_ptr<Entity>child);
		Entity* GetParent();
		void SetWorld(World* world);
		World* GetWorld();
		void SetParent(Entity* parent);
		bool IsChild(std::shared_ptr<Entity>child);
		size_t GetChildrenCount();

		
		template<typename T>T* AddComponent(){};
		template<typename T>T* GetComponent();
		template<typename T>void	RemoveComponent();
		

	private:
		boost::uuids::uuid		mGuid;
		std::vector<std::shared_ptr<Entity>> mchildrenE;
		Entity* mParent;
		World* mWorld;

		TransformComponent* mTransform;
	};

	
}