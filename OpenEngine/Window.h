#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <thread>

namespace OpenEngine {
	
	class Window {
	public:
		void resize(int width, int height) {
			glViewport(0, 0, width, height);
		}
		Window(int width, int height,const char* title) {
			glfwInit();
			m_window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (m_window == NULL) {
				glfwTerminate();
				exit(-1);
			}
			glfwMakeContextCurrent(m_window);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				glfwTerminate();
				exit(-1);
			}
			glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		}
	private:
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
		GLFWwindow* m_window;
	};
}