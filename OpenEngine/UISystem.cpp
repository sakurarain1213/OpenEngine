#include"UISystem.h"
#include"Math.h"
#include"Entity.h"
#include<iostream>
OpenEngine::UISystem::UISystem(World* world) :window_id(0) {
	mWorld = world;
}

int OpenEngine::UISystem::Initialize()noexcept {

	
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	
	clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	return 0;
}

void OpenEngine::UISystem::Finalize()noexcept {

}

void OpenEngine::UISystem::Tick()noexcept {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	
	for (ButtonComponent* comp : components) {
		
		ShowButton(comp);
		
	}

	// Rendering
	ImGui::Render();

	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

void OpenEngine::UISystem::ShowButton(ButtonComponent* comp) {
	bool is = comp->IsActive();
	Vec3 posi=comp->GetPosition();
	Vec2 size = comp->GetSize();
	float sx=size.x(),sy=size.y();
	std::string temptext = comp->GetText();
	char* text = (char*)temptext.c_str();
	std::string tempname = comp->GetText();
	char* name = (char*)tempname.c_str();
	
	ImGui::SetNextWindowPos(ImVec2(posi.x(), posi.y()), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(sx+200, sy+200), ImGuiCond_Always);
	
	
	// Main body of the Demo window starts here.
	ImGui::Begin(name, &is, window_flags);
	ImGui::Button(text, ImVec2(sx, sy));
	ImGui::End();
}