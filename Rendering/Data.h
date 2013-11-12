#pragma once
#include "Rendering.h"
#include "Maths\Vector.h"

#include <string>
#include <vector>

namespace Rendering
{
class Data
{
public: /* constructors and destructors */
	Data(void);
	Data(std::string key, std::string value);
	~Data(void);
public: /* public function members */
	Data* AddChild(std::string key);
	Data* AddChild(std::string key, std::string value);
	Data* GetParent() const;
	void SetParent(Data* pDataParent);
	std::string GetKey() const;
	void SetKey(const std::string& key);
	
	int FindChildIndex(const std::string& key) const;
	Data* FindChild(const std::string& key) const;
	std::string FindChildValueString(const std::string& key, const std::string& sDefault="") const;
	bool FindChildValueBool(const std::string& key, bool bDefault=false) const;
	int FindChildValueInt(const std::string& key, int iDefault=0) const;
	unsigned int FindChildValueUInt(const std::string& key, unsigned int uiDefault=0) const;
	float FindChildValueFloat(const std::string& key, float fDefault=0.0f) const;
	Maths::Vector2Df FindChildValueVector2D(const std::string& key, Maths::Vector2Df vecDefault=Maths::Vector2Df()) const;

	std::string GetValueString() const;
	bool GetValueBool() const;
	int GetValueInt() const;
	unsigned int GetValueUInt() const;
	float GetValueFloat() const;
	Maths::Vector2Df GetValueVector2D() const;
	Maths::Vector3Df GetValueVector3D() const;
	Maths::Vector4Df GetValueVector4D() const;

	void SetValue(const std::string& value);
	void SetValue(bool);
	void SetValue(int);
	//void SetValue(unsigned int);
	void SetValue(float);
	void SetValue(const Maths::Vector2Df&);

	unsigned int GetChildrenCount() const;
	Data* GetChild(unsigned int index) const;

	std::vector<Data*>::const_iterator ChildrenBegin() const;
	std::vector<Data*>::const_iterator ChildrenEnd() const;
protected: /* protected member variables */
	Data* m_parent;
	std::string m_key;
	std::string m_value;
	std::vector<Data*> m_children;
};
} /* end namespace Rendering */

