#pragma once

#include "Context.h"

namespace OpenEngine::App {
	Context::Context(std::string base_path):
		projectSetting(base_path + "/.project")
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

		assets = std::make_unique<Editor::AssetDatabase>(base_path + "/Assets");
		ServiceLocator::RegisterService<Editor::AssetDatabase>(*assets);

		assets->ImportAllAssets();

		

		//以下为初始化一个测试用World,包含一个entity

		worldmanager = std::make_unique<World>("world");
		worldmanager->Initialize();
		auto test_entity = worldmanager->CreateEntity("e1");
		Entity* e = test_entity.get();
		TransformComponent* transc = e->AddComponent<TransformComponent>();
		ButtonComponent* buttonc = e->AddComponent<ButtonComponent>();
		Eigen::Vector3f vel(1, 1, 0);
		transc->SetLinearVelocity({ 5,5,0 });
		buttonc->SetText("Start!!!");
		buttonc->SetSize({ 200,200 });
		
		
	}
}