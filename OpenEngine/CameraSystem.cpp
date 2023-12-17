#include "CameraSystem.h"
#include"ServiceLocator.h"
#include"Renderer.h"

OpenEngine::CameraSystem::CameraSystem(World* world) {
	mWorld = world;
}

int OpenEngine::CameraSystem::Initialize()noexcept {

	return 0;

}

void OpenEngine::CameraSystem::Tick()noexcept {

	SetRenderer();



}

void OpenEngine::CameraSystem::Finalize()noexcept {


}

OpenEngine::CameraComponent* OpenEngine::CameraSystem::GetMainCamera() {
	return MainCamera;
}

void OpenEngine::CameraSystem::SetMainCamera(CameraComponent* camera) {
	MainCamera = camera;
}

void OpenEngine::CameraSystem::SetRenderer() {
	if (!MainCamera)return;
	OESERVICE(Renderer).SetViewMatrix(MainCamera->GetViewMatrix());
	OESERVICE(Renderer).SetProjectionMatrix(MainCamera->GetProjectionMatrix());
	OESERVICE(Renderer).SetCameraPosition(MainCamera->GetPosition());
}

