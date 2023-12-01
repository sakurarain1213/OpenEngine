#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowDeviceSetting.h"
#include "Logger.h"

namespace OpenEngine {
	class WindowDevice {
	public:
		WindowDevice(const Setting::WindowDeviceSetting& setting) {
			if (glfwInit() == GLFW_FALSE) {
				OE_ERROR("Failed to Init GLFW");
				glfwTerminate();
				exit(0);
			}
			else {
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, setting.contextVersionMajor);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, setting.contextVersionMinor);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_SAMPLES, setting.samples);
			}
			OE_SUCCESS("Init GLFW successs");
		}
		~WindowDevice() {
			glfwTerminate();
		}
		void PollEvents() {
			glfwPollEvents();
		}
	};
}