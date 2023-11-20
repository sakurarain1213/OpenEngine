#pragma once
#include"IRuntimeModule.h"
namespace My {
	class InputManager : _implements_ IRuntimeModule
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();

		void UpArrowKeyDown();
		void UpArrowKeyUp();
		void DownArrowKeyDown();
		void DownArrowKeyUp();
		void LeftArrowKeyDown();
		void LeftArrowKeyUp();
		void RightArrowKeyDown();
		void RightArrowKeyUp();
	};
	extern InputManager* g_pInputManager;
}

