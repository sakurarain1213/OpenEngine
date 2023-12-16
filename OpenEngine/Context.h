#pragma once

#include <memory>
#include "WindowDevice.h"
#include "Window.h"
#include"Input.h"
#include "RenderDriver.h"
#include "Renderer.h"
#include "AssetDatabase.hpp"
#include "ServiceLocator.h"
#include "IniFile.h"
#include "World.h"
#include "Entity.h"
namespace OpenEngine::App {
	class Context {
	public:
		Context(std::string base_path);
	public:
		std::unique_ptr<WindowDevice> device;
		std::unique_ptr<Window> window;
		std::unique_ptr<RenderDriver> driver;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<Editor::AssetDatabase> assets;
		std::unique_ptr<World> worldmanager;
		std::unique_ptr<Input>inputMgr;
		IniFile projectSetting;

	};
}