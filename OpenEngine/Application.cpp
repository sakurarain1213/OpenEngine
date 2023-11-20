#include "Application.h"

namespace OpenEngine::App {
	Application::Application(std::string project_path) :
		base_path(project_path),
		m_context(project_path) {}
	void Application::Run() {
		Time::Initialize();
		while (IsRunning()) {
			m_context.device->PollEvents();
			Time::Update();
			m_context.window->SwapBuffers();
		}
	}
	bool Application::IsRunning() {
		return !m_context.window->ShouldClose();
	}
}