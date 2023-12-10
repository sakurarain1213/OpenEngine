#include"UISystem.h"
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
OpenEngine::UISystem::UISystem(World* world) {
	mWorld = world;
}

int OpenEngine::UISystem::Initialize()noexcept {
	return 0;
}

void OpenEngine::UISystem::Finalize()noexcept {

}

void OpenEngine::UISystem::Tick()noexcept {
	for (ButtonComponent* t : components) {

		
	}
}
void OpenEngine::UISystem::AddComponent(ButtonComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.insert(comp);
}
void OpenEngine::UISystem::DeleteComponent(ButtonComponent* comp) {
	if (nullptr == comp)
	{
		return;
	}

	components.erase(comp);
}