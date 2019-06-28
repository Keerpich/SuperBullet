#include "../include/Component.h"
#include "../include/Object.h"

namespace SuperBullet
{
	Component::Component() :
		mPosition(0.f, 0.f)
	{
	}

	Component::Component(const Vector2f & position) :
		mPosition(position)
	{
	}

	void Component::Draw(RenderTarget& target, RenderStates states) const
	{
		for (const DrawablePtr& drawable : mDrawables)
			target.draw(*drawable, states);
	}

	void Component::SetOwner(std::variant<ObjectPtr, ComponentPtr> owner)
	{
		mOwner = owner;
	}

	void Component::AttachComponent(ComponentPtr component)
	{
		mComponents.push_back(component);
	}

	void Component::AttachComponents(std::list<ComponentPtr> components)
	{
		mComponents.insert(mComponents.end(), components.begin(), components.end());
	}

	void Component::RemoveComponent(ComponentPtr component)
	{
		std::list<ComponentPtr>::iterator it =
			std::find(mComponents.begin(), mComponents.end(), component);

		if (it != mComponents.end())
			mComponents.erase(it);
	}

	void Component::AddDrawable(std::shared_ptr<Drawable> drawable)
	{
		mDrawables.push_back(drawable);
	}

	void Component::RemoveDrawable(std::shared_ptr<Drawable> drawable)
	{
		std::list<DrawablePtr>::iterator it =
			std::find(mDrawables.begin(), mDrawables.end(), drawable);

		if (it != mDrawables.end())
			mDrawables.erase(it);
	}

	Vector2f Component::GetPosition() const
	{
		return mPosition;
	}

	Vector2f Component::GetWorldPosition()
	{
		if (!mWorldPositionCacheDirty)
			return mCachedWorldPosition;

		if (std::holds_alternative<ComponentPtr>(mOwner))
		{
			ComponentPtr owner = std::get<ComponentPtr>(mOwner);
			mCachedWorldPosition = owner->GetWorldPosition() + mPosition;
		}
		else
		{
			ObjectPtr owner = std::get<ObjectPtr>(mOwner);
			mCachedWorldPosition = owner->GetPosition() + mPosition;
		}

		mWorldPositionCacheDirty = false;
		return mCachedWorldPosition;
	}

	Vector2f Component::GetOwnerPosition() const
	{
		if (std::holds_alternative<ComponentPtr>(mOwner))
		{
			ComponentPtr owner = std::get<ComponentPtr>(mOwner);
			return owner->GetPosition();
		}
		else
		{
			ObjectPtr owner = std::get<ObjectPtr>(mOwner);
			return owner->GetPosition();
		}
	}
}