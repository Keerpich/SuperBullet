#include "../include/Component.h"
#include "../include/Object.h"

namespace SuperBullet
{
	Component::Component() :
		Component({ 0.f, 0.f })
	{
	}

	Component::Component(const Vector2f & position) :
		Component(position, 0.f)
	{
	}

	Component::Component(const Vector2f & position, float rotation) :
		mPosition(position),
		mRotation(rotation)
	{
	}

	Component::~Component()
	{
	}

	void Component::Update(float deltaSeconds)
	{
		for (const ComponentPtr& comp : mComponents)
			comp->Update(deltaSeconds);
	}

	void Component::Draw(RenderTarget& target, RenderStates states) const
	{
		for (const ComponentPtr& comp : mComponents)
			comp->Draw(target, states);
	}

	void Component::SetOwner(OwnerVariant owner)
	{
		mOwner = owner;
	}

	void Component::AttachComponent(ComponentPtr component)
	{
		mComponents.push_back(component);
		component->SetOwner(weak_from_this());
	}

	void Component::AttachComponents(std::list<ComponentPtr> components)
	{
		for (auto& comp : components)
			comp->SetOwner(weak_from_this());
		mComponents.insert(mComponents.end(), components.begin(), components.end());
	}

	void Component::RemoveComponent(ComponentPtr component)
	{
		std::list<ComponentPtr>::iterator it =
			std::find(mComponents.begin(), mComponents.end(), component);

		if (it != mComponents.end())
			mComponents.erase(it);
	}

	void Component::SetPosition(const Vector2f & position)
	{
		mWorldPositionCacheDirty = true;
		mPosition = position;
	}

	void Component::SetWorldPosition(const Vector2f & position)
	{
		mPosition = position - GetOwnerPosition();
		mCachedWorldPosition = position;
	}

	Component::OwnerVariant Component::GetOwner() const
	{
		return mOwner;
	}

	Vector2f Component::GetPosition() const
	{
		return mPosition;
	}

	Vector2f Component::GetWorldPosition() const
	{
		//Disabled this because we don't invaldiate position cache when parent's position
		//is changed. We also might not need caching
		/*if (!mWorldPositionCacheDirty)
			return mCachedWorldPosition;*/

		if (std::holds_alternative<std::weak_ptr<Component>>(mOwner))
		{
			std::shared_ptr<Component> owner = std::get<std::weak_ptr<Component>>(mOwner).lock();
			mCachedWorldPosition = owner->GetWorldPosition() + mPosition;
		}
		else
		{
			std::shared_ptr<Object> owner = std::get<std::weak_ptr<Object>>(mOwner).lock();
			mCachedWorldPosition = owner->GetPosition() + mPosition;
		}

		mWorldPositionCacheDirty = false;
		return mCachedWorldPosition;
	}

	Vector2f Component::GetOwnerPosition() const
	{
		if (std::holds_alternative<std::weak_ptr<Component>>(mOwner))
		{
			std::shared_ptr<Component> owner = std::get<std::weak_ptr<Component>>(mOwner).lock();
			return owner->GetPosition();
		}
		else
		{
			std::shared_ptr<Object> owner = std::get <std::weak_ptr<Object>>(mOwner).lock();
			return owner->GetPosition();
		}
	}

	void Component::SetRotation(const float degrees)
	{
		mWorldRotationCacheDirty = true;
		mRotation = degrees;
	}

	void Component::SetWorldRotation(const float degrees)
	{
		mRotation = degrees - GetOwnerRotation();
		mCachedWorldRotation = degrees;
	}

	float Component::GetRotation() const
	{
		return mRotation;
	}

	float Component::GetWorldRotation() const
	{
		//Disabled this because we don't invaldiate rotation cache when parent's position
		//is changed. We also might not need caching
		/*if (!mWorldRotationCacheDirty)
			return mCachedWorldRotation;*/

		if (std::holds_alternative<std::weak_ptr<Component>>(mOwner))
		{
			std::shared_ptr<Component> owner = std::get<std::weak_ptr<Component>>(mOwner).lock();
			mCachedWorldRotation = owner->GetWorldRotation() + GetRotation();
		}
		else
		{
			std::shared_ptr<Object> owner = std::get<std::weak_ptr<Object>>(mOwner).lock();
			mCachedWorldRotation = owner->GetRotation() + GetRotation();
		}

		mWorldRotationCacheDirty = false;
		return mCachedWorldRotation;
	}

	float Component::GetOwnerRotation() const
	{
		if (std::holds_alternative<std::weak_ptr<Component>>(mOwner))
		{
			std::shared_ptr<Component> owner = std::get<std::weak_ptr<Component>>(mOwner).lock();
			return owner->GetRotation();
		}
		else
		{
			std::shared_ptr<Object> owner = std::get <std::weak_ptr<Object>>(mOwner).lock();
			return owner->GetRotation();
		}
	}
}