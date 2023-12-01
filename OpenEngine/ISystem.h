#pragma once
#include"Object.h"
namespace OpenEngine {
	class ISystem : public IRuntimeModule {
	public:
		ISystem() :mIsActive(true) {};

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