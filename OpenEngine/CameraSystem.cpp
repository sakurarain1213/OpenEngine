#include "CameraSystem.h"
#include"ServiceLocator.h"
#include"Renderer.h"
#include"Input.h"
OpenEngine::CameraSystem::CameraSystem(World* world) {
	mWorld = world;
}

int OpenEngine::CameraSystem::Initialize()noexcept {

	return 0;

}

void OpenEngine::CameraSystem::Tick()noexcept {
	Vec3 temp={0,0,0};
	
	if (OESERVICE(Input).GetKeyDown(EKey::KEY_A)) {
		temp = { -0.1,0,0 };
	}
	else if (OESERVICE(Input).GetKeyDown(EKey::KEY_D)) {
		temp = { 0.1,0,0 };
	}
	else if (OESERVICE(Input).GetKeyDown(EKey::KEY_W)) {
		temp = { 0,0.1,0 };
	}
	else if (OESERVICE(Input).GetKeyDown(EKey::KEY_S)) {
		temp = { 0,-0.1,0 };
	}

	Vec3 newposi = MainCamera->Position + temp;
	MainCamera->SetPosition(newposi);
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

