#pragma once

#include "Context.h"
#include "Object.h"

namespace OpenEngine::App {
	class Game {
	public:
		Game(const Context& context);
		void PreUpdate();
		void Update();
		void FixedUpdate();
	private:
		const Context& m_context;
	};
}