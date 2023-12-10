#pragma once

#include "Application.h"

namespace OpenEngine::App {
	Application::Application(std::string project_path) :
		base_path(project_path),
		m_context(project_path),
		m_game(m_context) {}
	void Application::Run() {
		Time::Initialize();
		while (IsRunning()) {
			m_context.device->PollEvents();
			Time::Update();

			m_game.PreUpdate();
			m_game.Update();
			m_game.FixedUpdate();

			//m_context.window->testUIRender(); ui的渲染已交由UISystem处理
			m_context.window->SwapBuffers();
			
		}
	}
	bool Application::IsRunning() {
		return !m_context.window->ShouldClose();
	}
}