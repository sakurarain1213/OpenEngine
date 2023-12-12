#pragma once
#include"IComponent.h"
#include"IRuntimeModule.h"
#include"TransformComponent.h"
#include"ButtonComponent.h"
#include"CameraComponent.h"
#include"RigidBodyComponent.h"
#include"ColliderComponent.h"
#include"World.h"
#include<vector>
#include<list>
#include<memory>
#include <boost/uuid/uuid_generators.hpp>
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
		virtual void Tick()noexcept;

		
		Entity(std::string name);
		Entity(std::string name, const boost::uuids::uuid& guid);
		virtual ~Entity();
		boost::uuids::uuid	GetGuid() const noexcept;
		void	SetGuid(const boost::uuids::uuid& guid) noexcept;
		
		void AddChild(std::shared_ptr<Entity> child);
		void RemoveChild(std::shared_ptr<Entity>child);
		Entity* GetParent();
		void SetWorld(World* world);
		World* GetWorld();
		void SetParent(Entity* parent);
		bool IsChild(std::shared_ptr<Entity>child);
		size_t GetChildrenCount();

		
		template<typename T>T* AddComponent();
		template<typename T>T* GetComponent();
		template<typename T>void	RemoveComponent();
		

	private:
		boost::uuids::uuid		mGuid;
		std::vector<std::shared_ptr<Entity>> mchildrenE;
		Entity* mParent;
		World* mWorld;

		TransformComponent* mTransform;
		ButtonComponent* mButton;
		CameraComponent* mCamera;
		RigidBodyComponent* mRigidBody;
		//ColliderComponent* mCollider;
	};
	template<typename T>
	T* OpenEngine::Entity::AddComponent() {
		void* comp = nullptr;
		if (std::is_same<T, TransformComponent>::value) {
			if(!mTransform){
			mTransform = new TransformComponent(this);

			mTransform->Initialize();
			mWorld->mTransformSystem->AddComponent(mTransform);
			
			}
			comp = mTransform;
		}
		else if (std::is_same<T, ButtonComponent>::value) {
			
			if (!mButton) {
				mButton = new ButtonComponent(this);
				mButton->Initialize();
				mWorld->mUISystem->AddComponent(mButton);
			}
			comp = mButton;
		}
		else if (std::is_same<T, CameraComponent>::value) {
			
			if (!mCamera) {
				mCamera = new CameraComponent(this);
				mCamera->Initialize();
			}
			comp = mCamera;
		}
		else if (std::is_same<T, RigidBodyComponent>::value) {
			if (!mRigidBody) {
				mRigidBody = new RigidBodyComponent(this);
				mWorld->mPhysicSystem->AddComponent(mRigidBody);
				mRigidBody->Initialize();
			}
			comp = mRigidBody;
		}
		/*else if (std::is_same<T, ColliderComponent>::value) {
			mCollider = new ColliderComponent(this);
			mCollider->Initialize();

			comp = mCollider;
		}*/

		return (T*)comp;
	}

	template<typename T>
	T* OpenEngine::Entity::GetComponent() {
		void* ret = nullptr;
		if (std::is_same<T, TransformComponent>::value) {
			ret = mTransform;
		}
		else if (std::is_same<T, ButtonComponent>::value) {
			ret = mButton;
		}
		else if (std::is_same<T, CameraComponent>::value) {
			ret = mCamera;
		}
		else if (std::is_same<T, RigidBodyComponent>::value) {
			ret = mRigidBody;
		}
		/*else if (std::is_same<T, ColliderComponent>::value) {
			ret = mCollider;
		}*/
		return (T*)ret;
	}

	template<typename T>
	void OpenEngine::Entity::RemoveComponent() {
		if (std::is_same<T, TransformComponent>::value) {
			mWorld->mTransformSystem->DeleteComponent(mTransform);
			mTransform->Finalize();
			delete mTransform;
			mTransform = nullptr;
		}
		else if (std::is_same<T, ButtonComponent>::value) {
			
			mWorld->mUISystem->DeleteComponent(mButton);
			mButton->Finalize();
			delete mButton;
			mButton = nullptr;
		}
		else if (std::is_same<T, CameraComponent>::value) {

			mCamera->Finalize();
			delete mCamera;
			mCamera = nullptr;
		}
		else if (std::is_same<T, RigidBodyComponent>::value) {

			mRigidBody->Finalize();
			delete mRigidBody;
			mRigidBody = nullptr;
		}
	}
	
}