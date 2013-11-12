#include "ShaderLibrary.h"
#include "Data.h"
#include "DataSerializer.h"
#include "Utils\Log.h"

#include <fstream>
#include <assert.h>

using namespace Rendering;
using namespace Utils;

ShaderLibrary::ShaderLibrary(void) :
	m_isCompiled(false)
{
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
	if (GetSingletonPtr() == NULL)
		return;

	if (GetSingletonPtr()->IsCompiled())
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

	GetSingletonPtr()->m_shaders.push_back(Shader(pName->GetValueString(), pVertex->GetValueString(), pFragment->GetValueString()));
	GetSingletonPtr()->m_shaderNames[pName->GetValueString()] = GetSingletonPtr()->m_shaders.size() - 1;

	auto& oShader = GetSingletonPtr()->m_shaders.back();

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