#pragma once

#include <list>
#include <variant>

#include "Object.h"
#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"
#include "../../ModuleRendering/include/Drawable.h"

namespace SuperBullet
{
	class Object;

	class Component : public std::enable_shared_from_this<Component>
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;
		using OwnerVariant = std::variant<std::monostate, std::weak_ptr<Object>, std::weak_ptr<Component>>;

	public:
		Component();
		Component(const Vector2f &position);

		virtual ~Component() = 0;

		virtual void Update(float deltaSeconds);
		virtual void Draw(RenderTarget& target, RenderStates states) const;
		
		void SetOwner(OwnerVariant owner);

		void AttachComponent(ComponentPtr component);
		void AttachComponents(std::list<ComponentPtr> components);
		void RemoveComponent(ComponentPtr component);

		void SetPosition(const Vector2f& position);
		void SetWorldPosition(const Vector2f& position);

		Vector2f GetPosition() const;
		Vector2f GetWorldPosition();
		Vector2f GetOwnerPosition() const;

	private:
		Vector2f mPosition;

		Vector2f mCachedWorldPosition;
		bool mWorldPositionCacheDirty = true;

		OwnerVariant mOwner;

		std::list<ComponentPtr> mComponents;
	};
}