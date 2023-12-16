#pragma once

#include "Window.h"


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace OpenEngine {
	void Window::CreateGLFWWindow() {
		GLFWmonitor* selectedMonitor = nullptr;
		if (m_fullscreen) {
			selectedMonitor = glfwGetPrimaryMonitor();
		}
		glfwWindowHint(GLFW_REFRESH_RATE, m_refreshrate);
		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), selectedMonitor, nullptr);
		if (!m_window) {
			OE_ERROR("Failed to create window");
			exit(0);
		} else {
			OE_SUCCESS("Create window success");
		}

		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1); // Enable vsync

		_glfw_window_map.emplace(m_window, this);

		
	}
	Window* Window::GetInstance(GLFWwindow* glfwWindow) {
		return _glfw_window_map.find(glfwWindow) != _glfw_window_map.end() ? _glfw_window_map[glfwWindow] : nullptr;
	}
	void Window::BindOnResize() const {
		auto resizeCallback = [](GLFWwindow* glfwWindow, int width, int height) {
			Window* window = GetInstance(glfwWindow);
			if (window) {
				window->onResize.Invoke(width, height);
			}
		};
		glfwSetFramebufferSizeCallback(m_window, resizeCallback);
	}
	void Window::SetContextCurrent() const {
		glfwMakeContextCurrent(m_window);
	}
	void Window::SwapBuffers() const {
		glfwSwapBuffers(m_window);
	}
	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(m_window);
	}
	Window* Window::FindInstance(GLFWwindow* p_glfwWindow)
	{
		return _glfw_window_map.find(p_glfwWindow) != _glfw_window_map.end() ? _glfw_window_map[p_glfwWindow] : nullptr;
	}
	GLFWwindow* Window::GetGlfwWindow() const {
		return m_window;
	}
	//imgui
	void Window::testUIRender() {
		
		// Poll and handle events (inputs, window resize, etc.)
	   // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	   // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
	   // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
	   // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		//glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		{
			static int count = 0;
			if (ImGui::Button("Start")) {
				count++;
			}

		}

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		
	}
	void Window::CreateimguiContext() {
		// Setup Dear ImGui context
		const char* glsl_version = "#version 150";

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		// Load Fonts
   // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
   // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
   // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
   // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
   // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
   // - Read 'docs/FONTS.md' for more instructions and details.
   // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
   // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
   //io.Fonts->AddFontDefault();
   //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
   //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
   //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
   //IM_ASSERT(font != nullptr);

   // Our state
		
		show_another_window = false;
		clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		
	}

	//CallBack bind
	void Window::BindKeyCallBack()const {
		auto keyCallback = [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods)
		{
			Window* windowInstance = FindInstance(p_window);

			if (windowInstance)
			{
				if (p_action == GLFW_PRESS)
					windowInstance->KeyDownEvent.Invoke(p_key);

				if (p_action == GLFW_RELEASE)
					windowInstance->KeyUpEvent.Invoke(p_key);
			}
		};

		glfwSetKeyCallback(m_window, keyCallback);
	}
	void Window::BindMouseCallBack() const
	{
		auto mouseCallback = [](GLFWwindow* p_window, int p_button, int p_action, int p_mods)
		{
			Window* windowInstance = FindInstance(p_window);

			if (windowInstance)
			{
				if (p_action == GLFW_PRESS)
					windowInstance->MouseButtonDownEvent.Invoke(p_button);

				if (p_action == GLFW_RELEASE)
					windowInstance->MouseButtonUpEvent.Invoke(p_button);
			}
		};

		glfwSetMouseButtonCallback(m_window, mouseCallback);
	}
	std::unordered_map<GLFWwindow*, Window*> Window::_glfw_window_map;
}