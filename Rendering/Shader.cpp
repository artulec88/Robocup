#include "Shader.h"
#include "RenderingApp.h"
#include "Utils\Utils.h"
#include "Utils\Log.h"
#include <stdio.h>

using namespace Rendering;
using namespace Utils;

Shader::Shader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile) :
	m_name(name),
	m_vertexFile(vertexFile),
	m_fragmentFile(fragmentFile),
	m_vertexShader(0),
	m_fragmentShader(0),
	m_program(0)
{
}

bool Shader::Compile()
{
	stdlog(Critical, LOGPLACE, "Function not yet implemented");
	return true;
}

void Shader::Destroy()
{
	glDetachShader((GLuint)m_program, (GLuint)m_vertexShader);
	glDetachShader((GLuint)m_program, (GLuint)m_fragmentShader);
	glDeleteShader((GLuint)m_vertexShader);
	glDeleteShader((GLuint)m_fragmentShader);
	glDeleteProgram((GLuint)m_program);
}

std::string Shader::FindType(const std::string& name) const
{
	stdlog(Critical, LOGPLACE, "Function not yet implemented");
	
	return "";
}

unsigned int Shader::FindTextureByUniform(const std::string& uniform) const
{
	stdlog(Critical, LOGPLACE, "Function not yet implemented");
	return 0;
}