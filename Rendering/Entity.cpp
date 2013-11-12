#include "Entity.h"

using namespace Rendering;

Entity::Entity(void) : m_id(INVALID_ID)
{
	Clear();
}


Entity::~Entity(void)
{
	Destroy();
}

void Entity::Clear()
{
	m_id = INVALID_ID;
}

bool Entity::Create()
{
	return true;
}

void Entity::Update()
{
}

void Entity::Destroy()
{
}

//void Entity::Render(const Renderer& renderer)
//{
//}