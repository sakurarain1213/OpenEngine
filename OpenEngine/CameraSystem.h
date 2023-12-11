#pragma once

#include"ISystem.h"
#include"CameraComponent.h"

#include<set>
namespace OpenEngine {
	class World;
	class CameraSystem : public ISystem
	{
	public:
		CameraSystem(World* world);


		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		std::shared_ptr<CameraComponent> GetMainCamera();
		void SetMainCamera(std::shared_ptr<CameraComponent> camera);
		void SetRenderer();
	private:
		World* mWorld;
		std::shared_ptr<CameraComponent> MainCamera;
	};
}
