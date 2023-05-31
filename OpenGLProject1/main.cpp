#include <glad/glad.h>// must be placed before glfw
#include <GLFW/glfw3.h>
#include <glad.c>



namespace idealand
{
	namespace opengl
	{
		class Window
		{
		public:
			GLFWwindow* win = 0;
			int w = 0; int h = 0;
			char* title = 0;

			char* glsl_version = (char*)"#version 460";
			int SwapInterval = 1;

			static void glfw_error_callback(int error, const char* description)
			{
				fprintf(stderr, "Glfw Error %d: %s\n", error, description);
			}

			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
			}

			static void setup_opengl_viewport(int width, int height)
			{
				glViewport(0, 0, width, height);
			}

			static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
			{
				setup_opengl_viewport(width, height);
			}

			Window(char* title, int w = 800, int h = 800, int OpenGLVersionMajor = 4, int OpenGLVersionMinor = 6) : title(title), w(w), h(h)
			{
				glfwSetErrorCallback(glfw_error_callback); if (!glfwInit()) { return; }
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor); glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // GLFW_OPENGL_COMPAT_PROFILE GLFW_OPENGL_CORE_PROFILE
				// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for mac os it's needed
				glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
				// glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // for debug

				win = glfwCreateWindow(w, h, title, NULL, NULL); if (!win) { printf("Failed to create GLFW window\n"); close(-1); return; } glfwMakeContextCurrent(win);
				if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { printf("Failed to initialize GLAD\n"); close(-1); return; }
				setup_opengl_viewport(w, h);
				glfwSwapInterval(SwapInterval); //must be used after current context set, the default is 0, which means show the new content once available, 1 is the prefered value
				glfwSetFramebufferSizeCallback(win, Window::framebuffer_size_callback); glfwSetKeyCallback(win, key_callback);

				//------------- opengl global settings ----------------
				// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				// glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA); glEnable(GL_BLEND); //glEnable(GL_DEPTH_TEST);

			}
			~Window()
			{
				close(0);
			}

			int close(int r)
			{
				if (win) glfwDestroyWindow(win); glfwTerminate(); return r;
			}

		};

		void company()
		{
			int w = 800, h = 800;
			opengl::Window win((char*)"Lines And Chars", w, h);
			while (!glfwWindowShouldClose(win.win))
			{
				glClearColor(1.0, 0.0, 0.0, 0.0); glClear(GL_COLOR_BUFFER_BIT); // 填充红色背景

				glColor3f(0.0f, 0.0f, 1.0f); // 设置线的颜色为蓝色
				glLineWidth(5.0f); // 设置线的宽度
				glBegin(GL_LINES);
				glVertex3f(0, 0, 0);
				glVertex3f(0, 0.5, 0);
				glEnd();

				glColor3f(0.0f, 1.0f, 0.0f); // 设置线的颜色为绿色
				glLineWidth(15.0f); // 设置线的宽度
				glBegin(GL_LINES);
				glVertex3f(-0.5, -0.5, 0);
				glVertex3f(-0.3, 0.3, 0);
				glEnd();

				glFlush();

				glfwSwapBuffers(win.win); // swap buffer to show new content
				glfwPollEvents(); // response to user operations on the window, process the events by default handlers
				// glfwWaitEvents(); // for static rendering content
			}
		}
	}

}

int main()
{
	idealand::opengl::company();
}