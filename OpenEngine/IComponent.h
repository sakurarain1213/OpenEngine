#pragma once
#include"IRuntimeModule.h"

namespace OpenEngine {
	class Entity;
	
	class IComponent : public IRuntimeModule {
	public:
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		IComponent():mOwner(nullptr),mIsActive(true){}

		bool IsActive() { return mIsActive; }
		void SetActive(bool state) { mIsActive = state; }

		Entity* GetOwner() { return mOwner; }
		void SetOwner(Entity* owner) { mOwner = owner; }
		

	protected:
		Entity* mOwner;
		bool mIsActive;
	};
}