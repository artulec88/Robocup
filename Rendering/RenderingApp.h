#pragma once

#include "Rendering.h"
#include "Renderer.h"
#include "Utils\CommandLine.h"
#include "Singleton.h"
#include <string>
#include <gl/glew.h>
#include <GLFW/glfw3.h> // inlcude GLFW

namespace Rendering
{
class RENDERING_API RenderingApp
{
public: // constructors and destructors
	RenderingApp(Utils::CommandLine& commandLine);
	virtual ~RenderingApp(void);

public: // public member functions
	void ReadConfigFile() const;
	bool HasCommandLineSwitch(const std::string& opt) const;
	std::string GetCommandLineSwitch(const std::string& opt) const;
	
	void SetMultisampling(bool bMultisampling);
	bool IsMultisamplingEnabled() const;

	void OpenWindow(const std::string& windowTitle, int width = 1024, int height = 768, bool bFullscreen = false, bool bResizable = false);

	bool IsFullscreen() const;
	bool IsOpen() const;
	void SetMouseCursorEnabled(int value);

	void SwapBuffers();
	float GetTime();

	virtual std::string WindowTitle() const;
	virtual std::string AppDirectory() const;
	virtual void CloseWindowEvent();
	virtual void ResizeWindowEvent(int width, int height);
	virtual void KeyEvent(int key, int scancode, int action, int mods);
	virtual void CharEvent(unsigned int codepoint);
	virtual void MouseInputEvent(int button, int action, int mods);

	Renderer* CreateRenderer();
	Renderer* GetRenderer() const;
public:
	static RenderingApp* GetApp();
	static void WindowCloseCallback(GLFWwindow* window);
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
	static void KeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void CharEventCallback(GLFWwindow* window, unsigned int codepoint);
	static void MouseInputCallback(GLFWwindow* window, int button, int action, int mods);
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
	static RenderingApp* s_renderingApp;
};

} /* end namespace Rendering */