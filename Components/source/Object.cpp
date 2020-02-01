#include "..\include\Object.h"
#include "..\include\Component.h"

SuperBullet::Object::Object() :
	Object({ 0.f, 0.f }, 0.f)
{
}

SuperBullet::Object::Object(const Vector2f& position) :
	Object(position, 0.f)
{
}

SuperBullet::Object::Object(const Vector2f & position, float rotation) :
	mPosition(position),
	mRotation(rotation)
{
}

void SuperBullet::Object::AttachComponent(ComponentPtr component)
{
	mComponents.push_back(component);
	component->SetOwner(weak_from_this());
}

void SuperBullet::Object::AttachComponents(std::list<ComponentPtr> components)
{
	for (auto& comp : components)
		comp->SetOwner(weak_from_this());
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

void SuperBullet::Object::SetPosition(const Vector2f & position)
{
	mPosition = position;
}

SuperBullet::Vector2f SuperBullet::Object::GetPosition() const
{
	return mPosition;
}

void SuperBullet::Object::SetRotation(const float rotation)
{
	mRotation = rotation;
}

float SuperBullet::Object::GetRotation() const
{
	return mRotation;
}

