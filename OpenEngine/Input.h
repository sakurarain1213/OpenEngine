#pragma once

#include<unordered_map>

#include"Window.h"
#include"EKey.h"
#include"EKeyState.h"
#include"EMouseButton.h"
#include"EMouseButtonState.h"

namespace OpenEngine {

	

	class Input {
	public:

		Input(Window& win);
		~Input();

		void SetGLFWwindow(GLFWwindow* win);
		GLFWwindow* GetWindow();

		
		EKeyState GetKeyState(EKey p_key)const;
		EMouseButtonState GetMouseButtonState(EMouseButton p_button)const;

		std::pair<double, double> GetMousePosition()const;

		bool GetKeyDown(EKey p_key)const;
		bool GetKeyUp(EKey p_key)const;
		bool GetMouseButtonDown(EMouseButton p_button)const;
		bool GetMouseButtonUp(EMouseButton p_button)const;
	private:
		void OnKeyDown(int p_key);
		void OnKeyUp(int p_key);
		void OnMouseButtonDown(int p_button);
		void OnMouseButtonUp(int p_button);


	private:
		Window& mWindow;
		ListenerID keyDownListener;
		ListenerID keyUpListener;
		ListenerID mouseButtonDownListener;
		ListenerID mouseButtonUpListener;

		
		std::unordered_map<EKey, EKeyState>					m_keyEvents;
		std::unordered_map<EMouseButton, EMouseButtonState>	m_mouseButtonEvents;

		
	};


}