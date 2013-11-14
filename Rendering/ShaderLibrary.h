#pragma once

#include "Rendering.h"
#include "Singleton.h"
#include "Shader.h"

#include <string>
#include <map>
#include <vector>

namespace Rendering
{
// TODO: This class should be a singleton
class RENDERING_API ShaderLibrary
{
public: /* constructors and destructors */
	ShaderLibrary(void);
	~ShaderLibrary(void);
public: /* static functions */
	static ShaderLibrary* GetShaderLibrary();
	static void AddShader(const std::string& strShaderName);
public: /* public function members */
	bool IsCompiled() const;
protected: /* protected member variables */
	std::map<std::string, unsigned int> m_shaderNames;
	std::vector<Shader> m_shaders;
	bool m_isCompiled;

	static ShaderLibrary* s_shaderLibrary;
};
} /* end namespace Rendering */