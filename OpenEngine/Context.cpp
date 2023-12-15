#pragma once

#include "Context.h"
#include <iostream>

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
		auto te= worldmanager->CreateEntity("e2");
		Entity* e2 = te.get();
		Entity* e = test_entity.get();
		
		ButtonComponent* buttonc = e->AddComponent<ButtonComponent>();
		buttonc->SetWindowid("e1");
		//CameraComponent* camerac = e->AddComponent<CameraComponent>();
		TransformComponent* tranc = e->GetComponent<TransformComponent>();
		tranc->SetPosition({ 0,0,0 });
		RigidBodyComponent* body = e->AddComponent<RigidBodyComponent>();
		body->SetMass(10); 

		Vec3 V1(-100, 0, 0);
		body->SetVelocity(V1);
		
		Vec3 minP = { 0,0,0 }; Vec3 maxP = { 100,100,100 };
		body->SetAABB(minP, maxP);
		//
		//ColliderComponent* coll1 = e->AddComponent<ColliderBox>();

		//Vec3 f1 = { 10,0,0 };
		//body->SetVelocity(f1);
		
		ButtonComponent* buttonc2 = e2->AddComponent<ButtonComponent>();
		buttonc2->SetWindowid("e2");
		TransformComponent* te2 = e2->GetComponent<TransformComponent>();
		te2->SetPosition({ 600,0,0 });
		RigidBodyComponent* body2 = e2->AddComponent<RigidBodyComponent>();
		body2->SetMass(10);

		Vec3 V2(100, 0, 0);
		body->SetVelocity(V2);

		minP = { 600,0,0 };  maxP = { 800,200,200 };  //minP  is same   as   position
		body2->SetAABB(minP, maxP);

	// 碰撞需要设置质量和碰撞盒(体积边界)   

		/*
		Eigen::Vector3f tempaabb3(1,1,0); Eigen::Vector3f tempaabb4(2, 2, 2);
		body2->SetAABB(tempaabb3, tempaabb4);
		*/
	
		buttonc2->SetText("Go!!!");
		

		//camerac->SetFront({ 0,0,-1 });
		//camerac->SetUp({ 0,1,0 });
		//camerac->SetFov(0.5);
		//camerac->SetNearClip(1);
		//camerac->SetFarClip(3);
		//worldmanager->mCameraSystem->SetMainCamera(camerac);
		Eigen::Vector3f vel(1, 1, 0);
		
		buttonc->SetText("Start!!!");
		

		
		
	}
}