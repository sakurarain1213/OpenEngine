#pragma once
#include"IRuntimeModule.h"
namespace OpenEngine {
	class ISystem {
	public:
		ISystem(std::string name) {
			mIsActive = true;
		}
		virtual std::string GetType() {
			return "PhysicsSystem";
		};
		virtual int Initialize() = 0;
		virtual void Finalize() = 0;
		virtual void Tick() = 0;
		virtual bool IsActive() { return mIsActive; }
		virtual void Activate() { mIsActive = true; }
		virtual void Deactivate() { mIsActive = false; }
	private:
		bool mIsActive;
	};

	
}