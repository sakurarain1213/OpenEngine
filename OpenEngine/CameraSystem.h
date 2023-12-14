#pragma once

#include"ISystem.h"
#include"CameraComponent.h"


namespace OpenEngine {
	class World;
	class CameraSystem : public ISystem
	{
	public:
		CameraSystem(World* world);


		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		CameraComponent* GetMainCamera();
		void SetMainCamera(CameraComponent* camera);
		void SetRenderer();
	private:
		World* mWorld;
		CameraComponent* MainCamera;
	};
}
