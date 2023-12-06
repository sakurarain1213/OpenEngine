#pragma once

#include "Game.h"

namespace OpenEngine::App {
	Game::Game(const Context& context):
		m_context(context)
	{}

	void Game::PreUpdate() {
		Object::DestroyQueuingObject();
	}

	void Game::Update() {
		m_context.worldmanager->Tick();
	}

	void Game::FixedUpdate() {}
}