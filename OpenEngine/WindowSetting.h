#pragma once

#include <string>

namespace OpenEngine::Setting {
	class WindowSetting {
	public:
		/*
		* Width in pixels of the window
		*/
		uint16_t width = 900;
		/*
		* Height in pixels of the window
		*/
		uint16_t height = 600;
		/*
		* Title of the window
		*/
		std::string title;
		/*
		* Specifies whether the window display in fullscreen mode
		*/
		bool fullScreen = false;
		/*
		* Specifies the desired refresh rate for full screen windows.
		* If set to -1, refresh rate will not be limited.
		* This hint is ignored for windowed mode windows.
		*/
		uint32_t refreshRate = -1;
	};
}