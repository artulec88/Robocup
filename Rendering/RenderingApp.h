#pragma once

#include "Rendering.h"
#include "Utils\CommandLine.h"
#include "Singleton.h"
#include <string>
#include <gl/glew.h>
#include <GLFW/glfw3.h> // inlcude GLFW

namespace Rendering
{
class RenderingApp : public Singleton<RenderingApp>
{
public: // constructors and destructors
	RENDERING_API RenderingApp(Utils::CommandLine& commandLine);
	RENDERING_API virtual ~RenderingApp(void);

public: // public member functions
	RENDERING_API void ReadConfigFile() const;
	RENDERING_API bool HasCommandLineSwitch(const std::string& opt) const;
	RENDERING_API std::string GetCommandLineSwitch(const std::string& opt) const;
	
	RENDERING_API void SetMultisampling(bool bMultisampling);
	RENDERING_API bool IsMultisamplingEnabled() const;

	RENDERING_API void OpenWindow(const std::string& windowTitle, int width = 1024, int height = 768, bool bFullscreen = false, bool bResizable = false);

	RENDERING_API bool IsFullscreen() const;
	RENDERING_API bool IsOpen() const;
	RENDERING_API void SetMouseCursorEnabled(int value);

	RENDERING_API void SwapBuffers();
	RENDERING_API float GetTime();

	virtual RENDERING_API std::string WindowTitle() const;
	virtual RENDERING_API std::string AppDirectory() const;
	virtual RENDERING_API void CloseWindowEvent();
	virtual RENDERING_API void ResizeWindowEvent(int width, int height);
	virtual RENDERING_API void KeyEvent(int key, int scancode, int action, int mods);
	virtual RENDERING_API void CharEvent(unsigned int codepoint);
	virtual RENDERING_API void MouseInputEvent(int button, int action, int mods);

	class Renderer* CreateRenderer();
	class Renderer* GetRenderer() const;
public:
	//static RenderingApp* GetApp() { return s_renderingApp; };
	RENDERING_API static void WindowCloseCallback(GLFWwindow* window);
	RENDERING_API static void WindowResizeCallback(GLFWwindow* window, int width, int height);
	RENDERING_API static void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	RENDERING_API static void CharEventCallback(GLFWwindow* window, unsigned int codepoint);
	RENDERING_API static void MouseInputCallback(GLFWwindow* window, int button, int action, int mods);
protected:
	GLFWwindow* m_window;
	int m_windowWidth;
	int m_windowHeight;
	std::string m_windowTitle;

	bool m_fullscreen;
	bool m_opened;
	bool m_multisampling;
	bool m_mouseEnabled;

	Utils::CommandLine& m_commandLine;
	Renderer* m_renderer;
	//static RenderingApp* s_renderingApp;
};

} /* end namespace Rendering */