#pragma once

#include "Context.h"
#include "Time.h"

namespace OpenEngine::App {
	class Application {
	public:
		Application(std::string project_path);
		void Run();
	private:
		bool IsRunning();
	private:
		std::string base_path;
		Context m_context;
	};
}