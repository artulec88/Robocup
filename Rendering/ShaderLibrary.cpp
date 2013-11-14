#include "ShaderLibrary.h"
#include "Data.h"
#include "DataSerializer.h"
#include "Utils\Log.h"

#include <fstream>
#include <assert.h>

using namespace Rendering;
using namespace Utils;

/* static */ ShaderLibrary* ShaderLibrary::s_shaderLibrary = NULL;

/* static */ ShaderLibrary* ShaderLibrary::GetShaderLibrary()
{
	return s_shaderLibrary;
}

ShaderLibrary::ShaderLibrary(void) :
	m_isCompiled(false)
{
	if (s_shaderLibrary == NULL)
	{
		s_shaderLibrary = this;
	}
}


ShaderLibrary::~ShaderLibrary(void)
{
}

bool ShaderLibrary::IsCompiled() const
{
	return m_isCompiled;
}

/* static */void ShaderLibrary::AddShader(const std::string& strShaderName)
{
	if (GetShaderLibrary() == NULL)
		return;

	if (GetShaderLibrary()->IsCompiled())
	{
		stdlog(Warning, LOGPLACE, "Shader library is already compiled");
		return;
	}

	std::basic_ifstream<char> f(strShaderName.c_str());
	if (!f.is_open())
	{
		stdlog(Error, LOGPLACE, "Could not open shader file %s", strShaderName.c_str());
		return;
	}

	std::shared_ptr<Data> pData(new Data());
	DataSerializer::Read(f, pData.get());

	Data* pName = pData->FindChild("Name");
	Data* pVertex = pData->FindChild("Vertex");
	Data* pFragment = pData->FindChild("Fragment");
	
	if (pName == NULL)
	{
		stdlog(Error, LOGPLACE, "pName object is NULL");
		return;
	}

	if (pVertex == NULL)
	{
		stdlog(Error, LOGPLACE, "pVertex object is NULL");
		return;
	}

	if (pFragment == NULL)
	{
		stdlog(Error, LOGPLACE, "pFragment object is NULL");
		return;
	}

	GetShaderLibrary()->m_shaders.push_back(Shader(pName->GetValueString(), pVertex->GetValueString(), pFragment->GetValueString()));
	GetShaderLibrary()->m_shaderNames[pName->GetValueString()] = GetShaderLibrary()->m_shaders.size() - 1;

	auto& oShader = GetShaderLibrary()->m_shaders.back();

	for (std::vector<Data*>::const_iterator itr = pData->ChildrenBegin(); itr != pData->ChildrenEnd(); ++itr)
	{
		if ((*itr)->GetKey() == "Parameter")
		{
		}
		else if ((*itr)->GetKey() == "Defaults")
		{
		}
	}
}