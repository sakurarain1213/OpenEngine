#pragma once
#include"ISystem.h"
#include<set>
#include"ButtonComponent.h"

//imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

namespace OpenEngine {
	class World;
	class UISystem : public ISystem {
	public:
		UISystem(World* world);


		virtual int Initialize() noexcept;
		virtual void Finalize() noexcept;
		virtual void Tick() noexcept;

		virtual void AddComponent(ButtonComponent* comp);
		virtual void DeleteComponent(ButtonComponent* comp);

		void ShowButton(ButtonComponent* comp);
	private:
		std::set<ButtonComponent*> components;
		World* mWorld;
		//imgui
		
	
		ImVec4 clear_color;
		ImGuiIO io;
	
		int window_id;
		bool no_titlebar = false;
		bool no_scrollbar = false;
		bool no_menu = false;
		bool no_move = false;
		bool no_resize = true;
		bool no_collapse = false;
		bool no_close = false;
		bool no_nav = false;
		bool no_background = false;
		bool no_bring_to_front = false;
		bool unsaved_document = false;

		ImGuiWindowFlags window_flags = 0;
	};
}