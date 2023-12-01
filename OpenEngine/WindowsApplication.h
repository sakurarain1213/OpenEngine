#pragma once


#include"BaseApplication.h"
#include<Windows.h>

#include<tchar.h>

namespace My {
	class WindowsApplication : _implements_ BaseApplication
	{
	public:
		WindowsApplication();
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		virtual int GetName();
		HWND GetWindowsHandler();
	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		void CreateMainWindow();
		
	private:
		HWND mHWND;
		
	};
}

