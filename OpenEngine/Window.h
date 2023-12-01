#pragma once

#include "WindowSetting.h"
#include "Action.h"
#include "WindowDevice.h"

namespace OpenEngine {
	
	class Window {
	public:
		Window(const WindowDevice& device, const Setting::WindowSetting& setting) :
			device(device),
			m_width(setting.width),
			m_height(setting.height),
			m_title(setting.title),
			m_fullscreen(setting.fullScreen),
			m_refreshrate(setting.refreshRate)
		{
			CreateGLFWWindow();
			BindOnResize();
			onResize.AddListener(std::bind(&Window::updateSizeAfterResize, this, std::placeholders::_1, std::placeholders::_2));
		}
		~Window() {
			glfwDestroyWindow(m_window);
		}
		void SetContextCurrent() const;
		void SwapBuffers() const;
		bool ShouldClose() const;
	private:
		void CreateGLFWWindow();
		static Window* GetInstance(GLFWwindow* glfwWindow);
		void BindOnResize() const;
		void updateSizeAfterResize(uint16_t width, uint16_t height)
		{
			m_width = width;
			m_height = height;
		}
	public:
		Action<uint16_t, uint16_t> onResize;
	private:
		static std::unordered_map<GLFWwindow*, Window*> _glfw_window_map;
		const WindowDevice& device;
		GLFWwindow* m_window;
		uint16_t m_width;
		uint16_t m_height;
		std::string m_title;
		bool m_fullscreen;
		uint32_t m_refreshrate;
	};
}