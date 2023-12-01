#pragma once

#include "Window.h"

namespace OpenEngine {
	void Window::CreateGLFWWindow() {
		GLFWmonitor* selectedMonitor = nullptr;
		if (m_fullscreen) {
			selectedMonitor = glfwGetPrimaryMonitor();
		}
		glfwWindowHint(GLFW_REFRESH_RATE, m_refreshrate);
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), selectedMonitor, nullptr);
		if (!m_window) {
			OE_ERROR("Failed to create window");
			exit(0);
		} else {
			OE_SUCCESS("Create window success");
		}
		_glfw_window_map.emplace(m_window, this);
	}
	Window* Window::GetInstance(GLFWwindow* glfwWindow) {
		return _glfw_window_map.find(glfwWindow) != _glfw_window_map.end() ? _glfw_window_map[glfwWindow] : nullptr;
	}
	void Window::BindOnResize() const {
		auto resizeCallback = [](GLFWwindow* glfwWindow, int width, int height) {
			Window* window = GetInstance(glfwWindow);
			if (window) {
				window->onResize.Invoke(width, height);
			}
		};
		glfwSetFramebufferSizeCallback(m_window, resizeCallback);
	}
	void Window::SetContextCurrent() const {
		glfwMakeContextCurrent(m_window);
	}
	void Window::SwapBuffers() const {
		glfwSwapBuffers(m_window);
	}
	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(m_window);
	}
	std::unordered_map<GLFWwindow*, Window*> Window::_glfw_window_map;
}