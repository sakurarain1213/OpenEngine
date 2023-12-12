#pragma once

#include "Context.h"

namespace OpenEngine::App {
	Context::Context(std::string base_path):
		projectSetting(base_path + "\\.project")
	{
		Setting::WindowDeviceSetting deviceSetting;
		deviceSetting.contextVersionMajor = projectSetting.GetInt("device", "contextVersionMajor");
		deviceSetting.contextVersionMinor = projectSetting.GetInt("device", "contextVersionMinor");
		deviceSetting.samples = projectSetting.GetInt("device", "samples");
		device = std::make_unique<WindowDevice>(deviceSetting);
		Setting::WindowSetting windowSetting;
		windowSetting.width = projectSetting.GetInt("window", "width");
		windowSetting.height = projectSetting.GetInt("window", "height");
		windowSetting.title = projectSetting.GetString("window", "title");
		windowSetting.fullScreen = projectSetting.Getbool("window", "fullScreen");
		windowSetting.refreshRate = projectSetting.GetInt("window", "refreshRate");
		window = std::make_unique<Window>(*device, windowSetting);
		window->SetContextCurrent();
		Setting::DriverSetting driverSetting;
		driverSetting.debugMode = projectSetting.Getbool("driver", "debugMode");
		driver = std::make_unique<RenderDriver>(driverSetting);
		renderer = std::make_unique<Renderer>(*driver);

		assets = std::make_unique<Editor::AssetDatabase>(base_path + "\\Assets");
		ServiceLocator::RegisterService<Editor::AssetDatabase>(*assets);
		ServiceLocator::RegisterService<Renderer>(*renderer);
		
		assets->ImportAllAssets();

		

		//以下为初始化一个测试用World,包含一个entity

		worldmanager = std::make_unique<World>("world");
		worldmanager->Initialize();
		ServiceLocator::RegisterService<World>(*worldmanager);

		auto test_entity = worldmanager->CreateEntity("e1");
		//auto te= worldmanager->CreateEntity("e2");
		//Entity* e2 = te.get();
		Entity* e = test_entity.get();
		
		ButtonComponent* buttonc = e->AddComponent<ButtonComponent>();
		//CameraComponent* camerac = e->AddComponent<CameraComponent>();
		//TransformComponent* tranc = e->GetComponent<TransformComponent>();
		RigidBodyComponent* body = e->AddComponent<RigidBodyComponent>();

		
		//ButtonComponent* buttonc2 = e2->AddComponent<ButtonComponent>();
		
		//RigidBodyComponent* body2 = e2->AddComponent<RigidBodyComponent>();
		//transc2->SetPosition({ 0,0,0 });
		//Vec3 f = { -200,0,0 };
		//body2->SetVelocity(f);
		//buttonc2->SetText("Go!!!");
		//buttonc2->SetSize({ 200,200 });

		//camerac->SetFront({ 0,0,-1 });
		//camerac->SetUp({ 0,1,0 });
		//camerac->SetFov(0.5);
		//camerac->SetNearClip(1);
		//camerac->SetFarClip(3);
		//worldmanager->mCameraSystem->SetMainCamera(camerac);
		Eigen::Vector3f vel(1, 1, 0);
		
		buttonc->SetText("Start!!!");
		buttonc->SetSize({ 200,200 });

		
		
	}
}