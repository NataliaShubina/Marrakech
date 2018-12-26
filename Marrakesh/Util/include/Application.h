#pragma once


#include <Windows.h>

#define _CRT_SECURE_NO_WARNINGS 1
#define WIN32_LEAN_AND_MEAN 1


#include <stdio.h>
#include <math.h>
#include <string.h>

class Application
{
public:
	Application() {}
	virtual ~Application() {}

	virtual void Run(Application * m_app) {};
	virtual void Init() {};
	virtual void Startup() {};
	virtual void Render(float curTime) {};
	virtual void Shutdown() {};
	void		 SetWindowTitle(const char * title) {};
	virtual void OnResize(int w, int h) {};
	virtual void OnKey(int key, int action) {};
	virtual void OnMouseButton(int button, int action) {};
	virtual void OnMouseMove(int x, int y) {};
	virtual void OnMouseWheel(int pos) {};
	//virtual void OnDebugMessage(GLenum source,
	//	GLenum type,
	//	GLuint id,
	//	GLenum severity,
	//	GLsizei length,
	//	const GLchar * message);
	virtual void getMousePosition(int& x, int& y) {};

public:
	struct APPINFO
	{
		char title[128];
		int windowWidth;
		int windowHeight;
		int majorVersion;
		int minorVersion;
		int samples;
		union
		{
			struct
			{
				unsigned int    fullscreen : 1;
				unsigned int    vsync : 1;
				unsigned int    cursor : 1;
				unsigned int    stereo : 1;
				unsigned int    debug : 1;
				unsigned int    robust : 1;
			};
			unsigned int        all;
		} flags;
	};

protected:
	APPINFO					m_info;
	//static Application *	m_app;
	//GLFWwindow *			m_window;

	//static void glfw_onResize(GLFWwindow* m_window, int w, int h);
	//static void glfw_onKey(GLFWwindow* m_window, int key, int scancode, int action, int mods);
	//static void glfw_onMouseButton(GLFWwindow* m_window, int button, int action, int mods);
	//static void glfw_onMouseMove(GLFWwindow* m_window, double x, double y);
	//static void glfw_onMouseWheel(GLFWwindow* m_window, double xoffset, double yoffset);

	void SetVsync(bool enable) {};
};
