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
	}
}