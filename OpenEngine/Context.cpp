#pragma once

#include "Context.h"
#include"Input.h"
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
		
		inputMgr = std::make_unique<Input>(*window);
		ServiceLocator::RegisterService<Input>(*inputMgr);
		ServiceLocator::RegisterService<Editor::AssetDatabase>(*assets);
		ServiceLocator::RegisterService<Renderer>(*renderer);

		//以下为初始化一个测试用World,包含一个entity

		worldmanager = std::make_unique<World>("world");
		ServiceLocator::RegisterService<World>(*worldmanager);
		worldmanager->Initialize();
		

		assets->ImportAllAssets();

		auto entity1 = worldmanager->CreateEntity("e1");
		auto entity2= worldmanager->CreateEntity("e2");
		auto entity3 = worldmanager->CreateEntity("e3");
		auto entity4 = worldmanager->CreateEntity("e4");
		Entity* e1 = entity1.get();
		Entity* e2 = entity2.get();
		Entity* e3 = entity3.get();
		Entity* e4 = entity4.get();
		

		//建议速度不要超过400   要测static 
		ButtonComponent* buttonc = e1->AddComponent<ButtonComponent>();
		buttonc->SetWindowid("e1");
		buttonc->SetSize({ 100,100 });
		TransformComponent* tc1 = e1->GetComponent<TransformComponent>();
		tc1->SetPosition({ 0,0,0 });
		RigidBodyComponent* body1 = e1->AddComponent<RigidBodyComponent>();
		body1->SetMass(10); 
		Vec3 V1(10, 200, 0);
		body1->SetVelocity(V1);
		Vec3 tiji(100, 100, 100);
		Vec3 minP = tc1->GetPosition(); Vec3 maxP = tc1->GetPosition() + tiji;
		body1->SetAABB(minP, maxP);

		
		ButtonComponent* buttonc2 = e2->AddComponent<ButtonComponent>();
		buttonc2->SetWindowid("e2");
		buttonc2->SetSize({ 100,100 });
		TransformComponent* tc2 = e2->GetComponent<TransformComponent>();
		tc2->SetPosition({ 600,0,0 });
		RigidBodyComponent* body2 = e2->AddComponent<RigidBodyComponent>();
		body2->SetMass(1);
		Vec3 V2(100, 0, 0);
		body2->SetVelocity(V2);
		tiji << 100, 100, 100;
		minP = tc2->GetPosition();  maxP = tc2->GetPosition() + tiji;
		body2->SetAABB(minP, maxP);

		ButtonComponent* buttonc3 = e3->AddComponent<ButtonComponent>();
		buttonc3->SetWindowid("eklj3");
		buttonc3->SetText("e3!!!");
		buttonc3->SetSize({ 100,100 });
		TransformComponent* tc3 = e3->GetComponent<TransformComponent>();
		tc3->SetPosition({ 1800,0,0 });
		RigidBodyComponent* body3 = e3->AddComponent<RigidBodyComponent>();
		body3->SetMass(10);
		Vec3 V3(-100, 0, 0);
		body3->SetVelocity(V3);
		tiji << 100, 100, 100;
		minP = tc3->GetPosition();  maxP = tc3->GetPosition() + tiji;
		body3->SetAABB(minP, maxP);

		

		//4 是 static
		ButtonComponent* buttonc4 = e4->AddComponent<ButtonComponent>();
		buttonc4->SetWindowid("e   j3");
		buttonc4->SetText("e3   !");
		buttonc4->SetSize({ 100,100 });
		TransformComponent* tc4 = e4->GetComponent<TransformComponent>();
		tc4->SetPosition({ -10000,1000,0 });
		RigidBodyComponent* body4 = e4->AddComponent<RigidBodyComponent>();
		body4->SetMass(10000);
		Vec3 V4(0, 0, 0);
		body4->SetVelocity(V4);
		tiji << 20000, 200, 200;
		body4->SetStatic(true);   //先设静态  
		minP = tc4->GetPosition();  maxP = tc4->GetPosition() + tiji;
		body4->aabb.minPoint = minP; body4->aabb.maxPoint = maxP;  //静态的AABB不要用set
		//body4->SetAABB(minP, maxP);

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