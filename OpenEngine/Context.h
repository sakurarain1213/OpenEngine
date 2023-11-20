#pragma once
#include <memory>
#include "WindowDevice.h"
#include "WindowDeviceSetting.h"
#include "Window.h"
#include "WindowSetting.h"
#include "IniFile.h"

namespace OpenEngine::App {
	class Context {
	public:
		Context(std::string base_path);
	public:
		std::unique_ptr<WindowDevice> device;
		std::unique_ptr<Window> window;
		IniFile projectSetting;
	};
}