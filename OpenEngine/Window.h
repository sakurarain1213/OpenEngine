#pragma once

#include "WindowSetting.h"
#include "Action.h"
#include "WindowDevice.h"
//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
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
			
			CreateimguiContext();
			

			BindOnResize();
			onResize.AddListener(std::bind(&Window::updateSizeAfterResize, this, std::placeholders::_1, std::placeholders::_2));
		}
		~Window() {
			glfwDestroyWindow(m_window);
		}
		void SetContextCurrent() const;
		void SwapBuffers() const;
		bool ShouldClose() const;
		void testUIRender();
	private:
		void CreateGLFWWindow();
		static Window* GetInstance(GLFWwindow* glfwWindow);
		void BindOnResize() const;
		void updateSizeAfterResize(uint16_t width, uint16_t height)
		{
			m_width = width;
			m_height = height;
		}

		//test gui
		
		void CreateimguiContext();
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

		//imgui
		
		bool show_another_window;
		ImVec4 clear_color;
		ImGuiIO io;
	};
}