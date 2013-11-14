#include "RenderingApp.h"

#include "Renderer.h"

#include "Utils\Log.h"
#include "Utils\Config.h"

#include <assert.h>
#include <iostream>
#include <Windows.h>

using namespace Rendering;
using namespace Utils;

RenderingApp* RenderingApp::s_renderingApp = NULL;

/* static */ RenderingApp* RenderingApp::GetApp()
{
	return s_renderingApp;
}

RenderingApp::RenderingApp(CommandLine& commandLine) :
	m_window(NULL),
	m_windowWidth(0),
	m_windowHeight(0),
	m_windowTitle("Application"),
	m_fullscreen(false),
	m_opened(false),
	m_multisampling(false),
	m_mouseEnabled(false),
	m_commandLine(commandLine),
	m_renderer(NULL)
{
	stdlog(Debug, LOGPLACE, "Rendering application construction started");
	if (s_renderingApp == NULL)
	{
		s_renderingApp = this;
	}
	stdlog(Debug, LOGPLACE, "Rendering application construction finished");
}

RenderingApp::~RenderingApp(void)
{
	stdlog(Debug, LOGPLACE, "RenderingApp destruction started");
	// TODO: Add m_window termination and resource deallocation
	glfwTerminate();
	//if (m_window != NULL)
	//{
	//	delete m_window;
	//	stdlog(Info, LOGPLACE, "delete m_window finished");
	//	m_window = NULL;
	//	stdlog(Info, LOGPLACE, "m_window = NULL");
	//}
	stdlog(Debug, LOGPLACE, "RenderingApp destruction finished");
}

void RenderingApp::ReadConfigFile() const
{
	Config::LoadFromFile(m_commandLine.Get("-config", "C:\\Users\\Artur\\Documents\\Visual Studio 2010\\Projects\\Robocup\\x64\\Debug\\Config.cfg"));
}

bool RenderingApp::HasCommandLineSwitch(const std::string& opt) const
{
	//assert(m_commandLine);

	return m_commandLine.IsPresent(opt);
}

std::string RenderingApp::GetCommandLineSwitch(const std::string& opt) const
{
	//assert(m_commandLine);

	return m_commandLine.Get(opt, ""); //<std::string>(opt, "");
}

void RenderingApp::SetMultisampling(bool multisampling)
{
	m_multisampling = multisampling;
}

bool RenderingApp::IsMultisamplingEnabled() const
{
	return m_multisampling;
}

bool RenderingApp::IsFullscreen() const
{
	return m_fullscreen;
}

void RenderingApp::OpenWindow(const std::string& windowTitle,
							  int windowWidth /* = 1024*/,
							  int windowHeight /* = 768 */,
							  bool isFullscreen /* = false */,
							  bool isResizable /* = false */)
{
	stdlog(Debug, LOGPLACE, "OpenWindow() function started");
	int status = glfwInit();
	if ( status == GL_FALSE )
	{
		stdlog(Critical, LOGPLACE, "Failed to initialize GLFW");
		exit(EXIT_FAILURE);
	}
	stdlog(Debug, LOGPLACE, "GLFW initialized successfully");

	m_fullscreen = isFullscreen;

	if (HasCommandLineSwitch("/fullscreen"))
	{
		m_fullscreen = true;
		stdlog(Delocust, LOGPLACE, "Fullscreen mode enabled");
	}
	if (HasCommandLineSwitch("/windowed"))
	{
		m_fullscreen = false;
		stdlog(Delocust, LOGPLACE, "Windowed mode enabled");
	}

	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

	if (IsMultisamplingEnabled())
		glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);

	m_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	if (!m_window)
	{
		stdlog(Critical, LOGPLACE, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		stdlog(Critical, LOGPLACE, "Failed to initialize GLEW");
		stdlog(Debug, LOGPLACE, "Error message: %s", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (!IsFullscreen())
	{
		// The taskbar is at the bottom of the screen. Pretend the screen is smaller so the window doesn't clip down into it.
		// Also the window's title bar at the top takes up space.
		screenHeight -= 70;

		int windowX = (int)(screenWidth / 2 - m_windowWidth / 2);
		int windowY = (int)(screenHeight / 2 - m_windowHeight / 2);
		windowY -= 80;    // Move it up a tad so that we can see it better in the videos.
		glfwSetWindowPos(m_window, windowX, windowY);
	}

	glfwSetWindowCloseCallback(m_window, RenderingApp::WindowCloseCallback);
	glfwSetWindowSizeCallback(m_window, RenderingApp::WindowResizeCallback);
	glfwSetKeyCallback(m_window, RenderingApp::KeyEventCallback);
	glfwSetCharCallback(m_window, RenderingApp::CharEventCallback);
	//glfwSetMousePosCallback(m_window, RenderingApp::MouseMotionCallback);
	glfwSetMouseButtonCallback(m_window, RenderingApp::MouseInputCallback);
	glfwSwapInterval( 1 );
	glfwSetTime( 0.0 );

	SetMouseCursorEnabled(Config::GetValue("Cursor_input_mode", GLFW_CURSOR_HIDDEN));

	// Enable depth test
	glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
	glLineWidth(1.0);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	m_opened = true;
	m_renderer = CreateRenderer();
	m_renderer->Init();
	stdlog(Debug, LOGPLACE, "OpenWindow() function finished");
}

inline class Renderer* RenderingApp::CreateRenderer()
{
	return new Renderer(m_windowWidth, m_windowHeight);
}

class Renderer* RenderingApp::GetRenderer() const
{
	return m_renderer;
}

void RenderingApp::SetMouseCursorEnabled(int value)
{
	switch (value)
	{
	case GLFW_CURSOR_DISABLED:
	case GLFW_CURSOR_HIDDEN:
	case GLFW_CURSOR_NORMAL:
		glfwSetInputMode(m_window, GLFW_CURSOR, value);
		break;
	default:
		stdlog(Warning, LOGPLACE, "Wrong value %d given for input mode", value);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}

bool RenderingApp::IsOpen() const
{
	return true;
}

std::string RenderingApp::WindowTitle() const
{
	return m_windowTitle;
}

std::string RenderingApp::AppDirectory() const
{
	return "C:\\Users\\Artur\\Documents\\Visual Studio 2010\\Projects\\Robocup";
}

void RenderingApp::SwapBuffers()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

float RenderingApp::GetTime()
{
	return static_cast<float>(glfwGetTime());
}

void RenderingApp::CloseWindowEvent()
{
	//return GL_TRUE;
	//if (!timeToClose)
	//{
	//	glfwSetWindowShouldClose(m_window, GL_FALSE);
	//}
	glfwSetWindowShouldClose(m_window, GL_TRUE);
}

void RenderingApp::ResizeWindowEvent(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;

	//if (m_renderer != NULL)
	//{
	//	m_renderer->ResizeWindow(width, height);
	//}
	//Render();
	//SwapBuffers();
}

/**
 * @param key the keyboard key that was pressed or released
 * @param scancode the system-specific scancode of the key
 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
 * @param mods Bit field describing which modifier keys were held down
 */
void RenderingApp::KeyEvent(int key, int scancode, int action, int mods)
{
	// see http://www.glfw.org/docs/3.0/group__keys.html
	if (key == GLFW_KEY_SPACE)
	{
		exit(EXIT_SUCCESS);
	}
}

void RenderingApp::CharEvent(unsigned int codepoint)
{
	//if (codepoint == TINKER_KEY_F4 && IsAltDown())
	//{
	//	exit(0);
	//}

	//return DoKeyPress(codepoint);
}

/**
 * @param button the mouse button that was pressed or released
 * @param action GLFW_PRESS or GLFW_RELEASE
 * @param mods Bit field representing which modifier keys were held down
 */
void RenderingApp::MouseInputEvent(int button, int action, int mods)
{
}

/**
 * If you wish to be notified when the user attempts to close a window,
 * you can set the close callback with glfwSetWindowCloseCallback. This callback is called
 * directly after the close flag has been set. The callback function can be used for example
 * to filter close requests and clear the close flag again unless certain conditions are met.
 */
/* static */ void RenderingApp::WindowCloseCallback(GLFWwindow* window)
{
	GetApp()->CloseWindowEvent();
	//GetApp()->CloseWindowEvent();
}

/* static */ void RenderingApp::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	GetApp()->ResizeWindowEvent(width, height);
	//GetApp()->ResizeWindowEvent(width, height);
}

/* static */ void RenderingApp::KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GetApp()->KeyEvent(key, scancode, action, mods);
	//GetApp()->KeyEvent(key, scancode, action, mods);
}

/* static */ void RenderingApp::CharEventCallback(GLFWwindow* window, unsigned int codepoint)
{
	GetApp()->CharEvent(codepoint);
	//GetApp()->CharEvent(codepoint);
}

/* static */ void RenderingApp::MouseInputCallback(GLFWwindow* window, int button, int action, int mods)
{
	GetApp()->MouseInputEvent(button, action, mods);
	//GetApp()->MouseInputEvent(button, action, mods);
}