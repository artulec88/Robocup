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
class ShaderLibrary : public Singleton<ShaderLibrary>
{
public: /* constructors and destructors */
	RENDERING_API ShaderLibrary(void);
	RENDERING_API ~ShaderLibrary(void);
public: /* static functions */
	static void AddShader(const std::string& strShaderName);
public: /* public function members */
	RENDERING_API bool IsCompiled() const;
protected: /* protected member variables */
	std::map<std::string, unsigned int> m_shaderNames;
	std::vector<Shader> m_shaders;
	bool m_isCompiled;
};
} /* end namespace Rendering */