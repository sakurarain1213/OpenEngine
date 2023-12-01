#pragma once

#include "DriverSetting.h"
#include "Logger.h"
#include "WindowDevice.h"

namespace OpenEngine {
	class RenderDriver {
	public:
		RenderDriver(const Setting::DriverSetting& setting) {
			Init();
		}
	private:
		void Init() {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				OE_ERROR("Failed to initialize GLAD");
				exit(0);
			}
			OE_SUCCESS("Loader OpenGL driver success");
		}
	};
}