#pragma once

#include "Rendering.h"
#include <string>

#define MAX_TEXTURE_CHANNELS 2

namespace Rendering
{
class Shader
{
public: /* constructors and destructors */
	Shader(const std::string& name, const std::string& vertexFile, const std::string& fragmentFile);

public: /* public member functions */
	bool Compile();
	void Destroy();
	std::string FindType(const std::string& name) const;
	unsigned int FindTextureByUniform(const std::string& uniform) const;

protected: /* private member variables */
	std::string m_name;
	std::string m_vertexFile;
	std::string m_fragmentFile;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_program;

	unsigned int m_positionAttribute;
	unsigned int m_normalAttribute;
	unsigned int m_tangentAttribute;
	unsigned int m_bitangentAttribute;
	unsigned int m_texCoordAttributes[MAX_TEXTURE_CHANNELS];
	unsigned int m_colorAttribute;
};
} /* end namespace Rendering */
