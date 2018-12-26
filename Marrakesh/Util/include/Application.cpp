//#include "Application.h"
//#include "Defines.h"
//
//#include "GL/gl3w.h"
//#include "GL/glcorearb.h"
//#include "GLFW/glfw3.h"
//
//
//Application *	Application::m_app = nullptr;
//
//void Application::Run(Application * _app)
//{
//	bool running = true;
//	m_app = _app;
//
//	if (!glfwInit())
//	{
//		fprintf(stderr, "Failed to initialize GLFW\n");
//		return;
//	}
//
//	Init();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_info.majorVersion);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_info.minorVersion);
//
//#ifndef _DEBUG
//	if (m_info.flags.debug)
//#endif /* _DEBUG */
//	{
//		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
//	}
//	if (m_info.flags.robust)
//	{
//		glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
//	}
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	glfwWindowHint(GLFW_SAMPLES, m_info.samples);
//	glfwWindowHint(GLFW_STEREO, m_info.flags.stereo ? GL_TRUE : GL_FALSE);
//
//	{
//		m_window = glfwCreateWindow(m_info.windowWidth, m_info.windowHeight, m_info.title, m_info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
//		if (!m_window)
//		{
//			fprintf(stderr, "Failed to open m_window\n");
//			return;
//		}
//	}
//
//	glfwMakeContextCurrent(m_window);
//
//	glfwSetWindowSizeCallback(m_window, glfw_onResize);
//	glfwSetKeyCallback(m_window, glfw_onKey);
//	glfwSetMouseButtonCallback(m_window, glfw_onMouseButton);
//	glfwSetCursorPosCallback(m_window, glfw_onMouseMove);
//	glfwSetScrollCallback(m_window, glfw_onMouseWheel);
//
//	if (!m_info.flags.cursor)
//	{
//		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//	}
//
//	// m_info.flags.stereo = (glfwGetWindowParam(GLFW_STEREO) ? 1 : 0);
//
//	gl3wInit();
//
//#ifdef _DEBUG
//	fprintf(stderr, "VENDOR: %s\n", (char *)glGetString(GL_VENDOR));
//	fprintf(stderr, "VERSION: %s\n", (char *)glGetString(GL_VERSION));
//	fprintf(stderr, "RENDERER: %s\n", (char *)glGetString(GL_RENDERER));
//#endif
//
//	if (m_info.flags.debug)
//	{
//		if (gl3wIsSupported(4, 3))
//		{
//			glDebugMessageCallback((GLDEBUGPROC)debug_callback, this);
//			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//		}
//	}
//
//	Startup();
//
//	do
//	{
//		Render(glfwGetTime());
//
//		glfwSwapBuffers(m_window);
//		glfwPollEvents();
//
//		running &= (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
//		running &= (glfwWindowShouldClose(m_window) != GL_TRUE);
//	} while (running);
//
//	Shutdown();
//
//	glfwDestroyWindow(m_window);
//	glfwTerminate();
//}
//
//void Application::Init()
//{
//	strcpy_s(m_info.title, WINDOW_TITLE);
//	m_info.windowWidth = WINDOW_WIDTH;
//	m_info.windowHeight = WINDOW_HEIGHT;
//
//	m_info.majorVersion = MAJOR_VERSION;
//	m_info.minorVersion = MINOR_VERSION;
//	m_info.samples = 0;
//	m_info.flags.all = 0;
//	m_info.flags.cursor = 1;
//#ifdef _DEBUG
//	m_info.flags.debug = 1;
//#endif
//}
//
//void Application::Startup()
//{
//
//}
//
//void Application::Render(float curTime)
//{
//
//}
//
//void Application::Shutdown()
//{
//
//}
//
//void Application::SetWindowTitle(const char * title)
//{
//	glfwSetWindowTitle(m_window, title);
//}
//
//void Application::OnResize(int w, int h)
//{
//	m_info.windowWidth = w;
//	m_info.windowHeight = h;
//}
//
//void Application::OnKey(int key, int action)
//{
//
//}
//
//void Application::OnMouseButton(int button, int action)
//{
//
//}
//
//void Application::OnMouseMove(int x, int y)
//{
//
//}
//
//void Application::OnMouseWheel(int pos)
//{
//
//}
//
//void Application::OnDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message)
//{
//#ifdef _WIN32
//	OutputDebugStringA(message);
//	OutputDebugStringA("\n");
//#endif /* _WIN32 */
//}
//
//void Application::getMousePosition(int& x, int& y)
//{
//	double dx, dy;
//	glfwGetCursorPos(m_window, &dx, &dy);
//
//	x = static_cast<int>(floor(dx));
//	y = static_cast<int>(floor(dy));
//}
//
//void Application::glfw_onResize(GLFWwindow* m_window, int w, int h)
//{
//	m_app->OnResize(w, h);
//}
//
//void Application::glfw_onKey(GLFWwindow* m_window, int key, int scancode, int action, int mods)
//{
//	m_app->OnKey(key, action);
//}
//
//void Application::glfw_onMouseButton(GLFWwindow* m_window, int button, int action, int mods)
//{
//	m_app->OnMouseButton(button, action);
//}
//
//void Application::glfw_onMouseMove(GLFWwindow* m_window, double x, double y)
//{
//	m_app->OnMouseMove(static_cast<int>(x), static_cast<int>(y));
//}
//
//void Application::glfw_onMouseWheel(GLFWwindow* m_window, double xoffset, double yoffset)
//{
//	m_app->OnMouseWheel(static_cast<int>(yoffset));
//}
//
//void Application::SetVsync(bool enable)
//{
//	m_info.flags.vsync = enable ? 1 : 0;
//	glfwSwapInterval((int)m_info.flags.vsync);
//}
//
//void APIENTRY Application::debug_callback(GLenum source,
//	GLenum type,
//	GLuint id,
//	GLenum severity,
//	GLsizei length,
//	const GLchar* message,
//	GLvoid* userParam)
//{
//
//}