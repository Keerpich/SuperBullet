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

	class Component
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;
		using ObjectPtr = std::shared_ptr<Object>;

	public:
		Component();
		Component(const Vector2f &position);

		virtual ~Component() = 0;

		virtual void Update(float deltaSeconds);
		virtual void Draw(RenderTarget& target, RenderStates states) const;
		
		void SetOwner(std::variant<ObjectPtr, ComponentPtr> owner);

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

		std::variant<ObjectPtr, ComponentPtr> mOwner;

		std::list<ComponentPtr> mComponents;
	};
}