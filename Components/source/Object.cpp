#include "..\include\Object.h"

SuperBullet::Object::Object() :
	mPosition(0.f, 0.f)
{
}

SuperBullet::Object::Object(const Vector2f& position) :
	mPosition(position.x, position.y)
{
}

void SuperBullet::Object::AttachComponent(ComponentPtr component)
{
	mComponents.push_back(component);
}

void SuperBullet::Object::AttachComponents(std::list<ComponentPtr> components)
{
	mComponents.insert(mComponents.end(), components.begin(), components.end());
}

void SuperBullet::Object::RemoveComponent(ComponentPtr component)
{
	std::list<ComponentPtr>::iterator it = 
		std::find(mComponents.begin(), mComponents.end(), component);

	if (it != mComponents.end())
		mComponents.erase(it);
}

void SuperBullet::Object::Update(float deltaSeconds)
{
	for (ComponentPtr& component_ptr : mComponents)
	{
		component_ptr->Update(deltaSeconds);
	}
}

void SuperBullet::Object::Draw(RenderTarget& target, RenderStates states) const
{
	for (const ComponentPtr& component_ptr : mComponents)
	{
		component_ptr->Draw(target, states);
	}
}

