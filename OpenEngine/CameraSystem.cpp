#include "CameraSystem.h"

OpenEngine::CameraSystem::CameraSystem(World* world) {
	mWorld = world;
}

int OpenEngine::CameraSystem::Initialize()noexcept {

	return 0;

}

void OpenEngine::CameraSystem::Tick()noexcept {

	



}

void OpenEngine::CameraSystem::Finalize()noexcept {


}

std::shared_ptr<OpenEngine::CameraComponent> OpenEngine::CameraSystem::GetMainCamera() {
	return MainCamera;
}

void OpenEngine::CameraSystem::SetMainCamera(std::shared_ptr<OpenEngine::CameraComponent> camera) {
	MainCamera = camera;
}