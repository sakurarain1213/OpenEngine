#include"Input.h"
using namespace OpenEngine;

Input::Input(Window& win):mWindow(win) {
	keyDownListener = mWindow.KeyDownEvent.AddListener(std::bind(&Input::OnKeyDown, this, std::placeholders::_1));
	keyUpListener = mWindow.KeyUpEvent.AddListener(std::bind(&Input::OnKeyUp, this, std::placeholders::_1));
	mouseButtonDownListener = mWindow.MouseButtonDownEvent.AddListener(std::bind(&Input::OnMouseButtonDown, this, std::placeholders::_1));
	mouseButtonUpListener = mWindow.MouseButtonUpEvent.AddListener(std::bind(&Input::OnMouseButtonUp, this, std::placeholders::_1));

}
Input::~Input() {
	mWindow.KeyDownEvent.RemoveListener(keyDownListener);
	mWindow.KeyUpEvent.RemoveListener(keyUpListener);
	mWindow.MouseButtonDownEvent.RemoveListener(mouseButtonDownListener);
	mWindow.MouseButtonUpEvent.RemoveListener(mouseButtonUpListener);
}

EKeyState Input::GetKeyState(EKey p_key)const {
	switch (glfwGetKey(mWindow.GetGlfwWindow(), static_cast<int>(p_key)))
	{
	case GLFW_PRESS:	return EKeyState::KEY_DOWN;
	case GLFW_RELEASE:	return EKeyState::KEY_UP;
	}

	return EKeyState::KEY_UP;
}

EMouseButtonState Input::GetMouseButtonState(EMouseButton p_button)const {
	switch (glfwGetMouseButton(mWindow.GetGlfwWindow(), static_cast<int>(p_button)))
	{
	case GLFW_PRESS:	return EMouseButtonState::MOUSE_DOWN;
	case GLFW_RELEASE:	return EMouseButtonState::MOUSE_UP;
	}

	return EMouseButtonState::MOUSE_UP;
}

bool Input::GetKeyDown(EKey p_key)const {
	return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key) == EKeyState::KEY_DOWN;
}
bool Input::GetKeyUp(EKey p_key)const {
	return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key) == EKeyState::KEY_UP;
}
bool Input::GetMouseButtonDown(EMouseButton p_button)const {
	return m_mouseButtonEvents.find(p_button) != m_mouseButtonEvents.end() && m_mouseButtonEvents.at(p_button) == EMouseButtonState::MOUSE_DOWN;
}
bool Input::GetMouseButtonUp(EMouseButton p_button)const {
	return m_mouseButtonEvents.find(p_button) != m_mouseButtonEvents.end() && m_mouseButtonEvents.at(p_button) == EMouseButtonState::MOUSE_UP;
}


std::pair<double, double> Input::GetMousePosition()const {
	std::pair<double, double> result;
	glfwGetCursorPos(mWindow.GetGlfwWindow(), &result.first, &result.second);
	return result;
}





void Input::OnKeyDown(int p_key)
{
	m_keyEvents[static_cast<EKey>(p_key)] = EKeyState::KEY_DOWN;
}

void Input::OnKeyUp(int p_key)
{
	m_keyEvents[static_cast<EKey>(p_key)] = EKeyState::KEY_UP;
}

void Input::OnMouseButtonDown(int p_button)
{
	m_mouseButtonEvents[static_cast<EMouseButton>(p_button)] = EMouseButtonState::MOUSE_DOWN;
}

void Input::OnMouseButtonUp(int p_button)
{
	m_mouseButtonEvents[static_cast<EMouseButton>(p_button)] = EMouseButtonState::MOUSE_UP;
}