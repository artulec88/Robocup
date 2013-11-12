#include "Renderer.h"
#include "Maths\Vector.h"

#include <vector>
#include <assert.h>
#include "Utils\Utils.h"
#include "Utils\Log.h"

#include <gl/glew.h>
//#include <GLFW/glfw3.h>
//#include <GL/glu.h>
//#include <GL/glfw.h>

using namespace Rendering;
using namespace Maths;
using namespace Utils;
using namespace std;

// TODO: Replace some default values with Config::GetValue
Renderer::Renderer(int windowWidth, int windowHeight) :
	m_windowWidth(windowWidth),
	m_windowHeight(windowHeight),
	m_renderOrtographicEnabled(false),
	m_drawingBackgroundEnabled(true),
	m_MultisampleTexturesEnabled(!!glTexImage2DMultisample) // TRUE if not zero and FALSE otherwise
{
	stdlog(Info, LOGPLACE, "Renderer construction started");
	if (!IsHardwareSupported())
	{
		stdlog(Critical, LOGPLACE, "Hardware is not supported");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glGetIntegerv(GL_SAMPLES, &m_iScreenSamples);

	SetSize(windowWidth, windowHeight);
	stdlog(Info, LOGPLACE, "Renderer construction finished");
}


Renderer::~Renderer(void)
{
	stdlog(Info, LOGPLACE, "Renderer destruction started");
	stdlog(Info, LOGPLACE, "Renderer destruction finished");
}

bool Renderer::IsHardwareSupported()
{
	//glGetString(GL_VERSION);
	if (!glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
		return false;

	return true;
//	//if (!gl3wIsSupported(3, 0))
//	//		return false;
//
//	// Compile a test shader. If it fails we don't support shaders.
//	const char* pszVertexShader =
//			"#version 130\n"
//			"void main()"
//			"{"
//			"        gl_Position = vec4(0.0, 0.0, 0.0, 0.0);"
//			"}";
//
//	const char* pszFragmentShader =
//			"#version 130\n"
//			"out vec4 vecFragColor;"
//			"void main()"
//			"{"
//			"        vecFragColor = vec4(1.0, 1.0, 1.0, 1.0);"
//			"}";
//
//
//
//	GLuint iVShader = glCreateShader(GL_VERTEX_SHADER);
//	GLuint iFShader = glCreateShader(GL_FRAGMENT_SHADER);
//	GLuint iProgram = glCreateProgram();
//
//	glShaderSource(iVShader, 1, &pszVertexShader, NULL);
//	glCompileShader(iVShader);
//
//	int iVertexCompiled;
//	glGetShaderiv(iVShader, GL_COMPILE_STATUS, &iVertexCompiled);
//
//	glShaderSource(iFShader, 1, &pszFragmentShader, NULL);
//	glCompileShader(iFShader);
//
//	int iFragmentCompiled;
//	glGetShaderiv(iFShader, GL_COMPILE_STATUS, &iFragmentCompiled);
//
//	glAttachShader(iProgram, iVShader);
//	glAttachShader(iProgram, iFShader);
//	glLinkProgram(iProgram);
//
//	int iProgramLinked;
//	glGetProgramiv(iProgram, GL_LINK_STATUS, &iProgramLinked);
//
//	glDetachShader(iProgram, iVShader);
//	glDetachShader(iProgram, iFShader);
//	glDeleteShader(iVShader);
//	glDeleteShader(iFShader);
//	glDeleteProgram(iProgram);
//
//	return iVertexCompiled == GL_TRUE && iFragmentCompiled == GL_TRUE && iProgramLinked == GL_TRUE;
}

void Renderer::SetSize(int windowWidth, int windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_vecFullscreenTexCoords[0] = Vector2Df(0, 1);
	m_vecFullscreenTexCoords[1] = Vector2Df(1, 0);
	m_vecFullscreenTexCoords[2] = Vector2Df(0, 0);
	m_vecFullscreenTexCoords[3] = Vector2Df(0, 1);
	m_vecFullscreenTexCoords[4] = Vector2Df(1, 1);
	m_vecFullscreenTexCoords[5] = Vector2Df(1, 0);

	m_vecFullscreenVertices[0] = Vector3Df(-1.0f, -1.0f, 0.0f);
	m_vecFullscreenVertices[1] = Vector3Df(1.0f, 1.0f, 0.0f);
	m_vecFullscreenVertices[2] = Vector3Df(-1.0f, 1.0f, 0.0f);
	m_vecFullscreenVertices[3] = Vector3Df(-1.0f, -1.0f, 0.0f);
	m_vecFullscreenVertices[4] = Vector3Df(1.0f, -1.0f, 0.0f);
	m_vecFullscreenVertices[5] = Vector3Df(1.0f, 1.0f, 0.0f);
}

void Renderer::Init()
{
	stdlog(Delocust, LOGPLACE, "Initializing Renderer started");
	LoadShaders();
	//ShaderLibrary::CompileShaders(m_screenSamples);
	ResizeWindow(m_windowWidth, m_windowHeight);
	//if (!ShaderLibrary::IsCompiled())
	//{
	//	stdlog(Emergency, LOGPLACE, "Shaders have not been compiled correctly");
	//}
	stdlog(Delocust, LOGPLACE, "Initializing Renderer finished");
}

// TODO: Fix this function
void Renderer::LoadShaders()
{
	stdlog(Delocust, LOGPLACE, "Loading shaders started");
	vector<string> asShaders;
	Utils::Utility::ListAllFilesInDir("C:\\Users\\Artur\\Documents\\Visual Studio 2010\\Projects\\Robocup\\Shaders", asShaders);

	for (vector<string>::iterator itr = asShaders.begin(); itr != asShaders.end(); ++itr)
	{
		if (!Utils::Utility::StrEndsWith((*itr), ".txt"))
			continue;

		//ShaderLibrary::AddShader("Shaders/" + (*itr));
	}
	stdlog(Delocust, LOGPLACE, "Loading shaders finished");
}

void Renderer::ResizeWindow(int windowWidth, int windowHeight)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
}

//void Renderer::RenderGrid(const PointF &lower, const PointF &upper, float density, float level /* = 0.0f */, float start /* = 0.0f */, float end /* = 1.0f */) const
//{
//	float s = density * start;
//	float e = density * end;
// 	glBegin(GL_LINES);
//	for (float z = lower.GetZ(); z <= upper.GetZ(); z+=density)
//	{
//		for (float x = lower.GetX(); x <= upper.GetX(); x+=density)
//		{
//			glVertex3f(x, 0, z + s);
//			glVertex3f(x, 0, z + e);
//		
//			glVertex3f(x + s, 0, z);
//			glVertex3f(x + e, 0, z);
//		}
//		
//	}
//	glEnd();
//}