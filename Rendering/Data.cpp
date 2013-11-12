#include "Data.h"
#include "Utils\Utils.h"

#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace Rendering;
using namespace std;

Data::Data(void) :
	m_parent(NULL)
{
}

Data::Data(string key, string value) :
	m_parent(NULL),
	m_key(key),
	m_value(value)
{
}

Data::~Data(void)
{
	for (vector<Data*>::iterator itr = m_children.begin(); itr != m_children.end(); ++itr)
	{
		delete *itr;
	}
	m_children.clear();
}

Data* Data::GetParent() const
{
	return m_parent;
}

void Data::SetParent(Data* pDataParent)
{
	m_parent = pDataParent;
}

std::string Data::GetKey() const
{
	return m_key;
}

void Data::SetKey(const std::string& key)
{
	m_key = key;
}

void Data::SetValue(const std::string& value)
{
	m_value = value;
}

void Data::SetValue(bool bValue)
{
	m_value = bValue ? "true" : "false";
}

void Data::SetValue(int iValue)
{
	m_value = std::to_string(static_cast<LONGLONG>(iValue));
}

void Data::SetValue(float fValue)
{
	m_value = std::to_string(static_cast<long double>(fValue));
}

void Data::SetValue(const Maths::Vector2Df& vecValue)
{
	std::stringstream s("");
	s << vecValue.GetX() << ", " << vecValue.GetY();
	m_value = s.str();
}

unsigned int Data::GetChildrenCount() const
{
	return static_cast<unsigned int>(m_children.size());
}

Data* Data::GetChild(unsigned int index) const
{
	return m_children[index];
}

std::vector<Data*>::const_iterator Data::ChildrenBegin() const
{
	return m_children.begin();
}

std::vector<Data*>::const_iterator Data::ChildrenEnd() const
{
	return m_children.end();
}

std::string Data::GetValueString() const
{
	return m_value;
}

bool Data::GetValueBool() const
{
	string tempValue = GetValueString();
	string value;
	std::transform(tempValue.begin(), tempValue.end(), value.begin(), ::toupper);

	return !( (value == "FALSE") || (value == "F") ||
			  (value == "NO") || (value == "N") ||
			  (value == "0") || (value == "NONE") ||
			  (value == "OFF") || (value == "DISABLED") );
}

int Data::GetValueInt() const
{
	return static_cast<int>(std::stoi(GetValueString()));
}

unsigned int Data::GetValueUInt() const
{
	return static_cast<unsigned int>(std::stoi(GetValueString()));
}

float Data::GetValueFloat() const
{
	return static_cast<float>(std::stof(GetValueString()));
}

Maths::Vector2Df Data::GetValueVector2D() const
{
	vector<string> asTokens;
	Utils::Utility::CutToTokens(GetValueString(), asTokens);

	Maths::Vector2Df vecResult;
	if (asTokens.size() > 0)
	{
		vecResult.SetX(static_cast<float>(std::stof(asTokens[0])));
		if (asTokens.size() > 1)
		{
			vecResult.SetY(static_cast<float>(std::stof(asTokens[1])));
		}
	}
	return vecResult;
}

Maths::Vector3Df Data::GetValueVector3D() const
{
	vector<string> asTokens;
	Utils::Utility::CutToTokens(GetValueString(), asTokens);

	Maths::Vector3Df vecResult;
	if (asTokens.size() > 0)
	{
		vecResult.SetX(static_cast<float>(std::stof(asTokens[0])));
		if (asTokens.size() > 1)
		{
			vecResult.SetY(static_cast<float>(std::stof(asTokens[1])));
			if (asTokens.size() > 2)
			{
				vecResult.SetZ(static_cast<float>(std::stof(asTokens[2])));
			}
		}
	}
	return vecResult;
}

Data* Data::AddChild(string key)
{
	return AddChild(key, "");
}

Data* Data::AddChild(string key, string value)
{
	Data* pData = new Data(key, value);
	m_children.push_back(pData);
	pData->SetParent(this);
	return pData;
}

int Data::FindChildIndex(const string& key) const
{
	unsigned int index = 0;
	for (vector<Data*>::const_iterator citr = m_children.begin(); citr != m_children.end(); ++citr, ++index)
	{
		if ((*citr)->GetKey() == key)
			return index;
	}
	return INVALID_VALUE;
}

Data* Data::FindChild(const string& key) const
{
	unsigned int index = FindChildIndex(key);
	if (index == INVALID_VALUE)
		return NULL;
	assert(index >= 0);
	assert(index < m_children.size());

	return m_children[index];
}

string Data::FindChildValueString(const string& key, const string& sDefault /* = "" */) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return sDefault;

	return pChild->GetValueString();
}

bool Data::FindChildValueBool(const string& key, bool bDefault /* = false */) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return bDefault;

	return pChild->GetValueBool();
}

int Data::FindChildValueInt(const string& key, int iDefault /* = 0 */) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return iDefault;

	return pChild->GetValueInt();
}

unsigned int Data::FindChildValueUInt(const string& key, unsigned int uiDefault /* = 0 */) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return uiDefault;

	return pChild->GetValueUInt();
}

float Data::FindChildValueFloat(const string& key, float fDefault /* = 0.0f */) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return fDefault;

	return pChild->GetValueFloat();
}

Maths::Vector2Df Data::FindChildValueVector2D(const std::string& key, Maths::Vector2Df vecDefault /*=Maths::Vector2Df()*/) const
{
	Data* pChild = FindChild(key);
	if (pChild == NULL)
		return vecDefault;

	return pChild->GetValueVector2D();
}