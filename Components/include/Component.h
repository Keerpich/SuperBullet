#pragma once

#include <list>
#include <variant>

#include "Object.h"
#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"
#include "../../ModuleRendering/include/Drawable.h"
#include "../../Utilities/include/Vector.h"

namespace SuperBullet
{
	class Object;

	class Component : public std::enable_shared_from_this<Component>
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;

	public:
		using OwnerVariant = std::variant<std::monostate, std::weak_ptr<Object>, std::weak_ptr<Component>>;

	public:
		Component();
		Component(const Vector2f &position);
		Component(const Vector2f &position, float rotation);
		Component(const Component& other) = default;
		Component(Component&& other) = default;

		virtual ~Component() = 0;

		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) = default;

		virtual void Update(float deltaSeconds);
		virtual void Draw(RenderTarget& target, RenderStates states) const;
		
		void SetOwner(OwnerVariant owner);

		void AttachComponent(ComponentPtr component);
		void AttachComponents(std::list<ComponentPtr> components);
		void RemoveComponent(ComponentPtr component);

		virtual void SetPosition(const Vector2f& position);
		virtual void SetWorldPosition(const Vector2f& position);

		OwnerVariant GetOwner() const;

		Vector2f GetPosition() const;
		Vector2f GetWorldPosition() const;
		Vector2f GetOwnerPosition() const;

		virtual void SetRotation(const float degrees);
		virtual void SetWorldRotation(const float degrees);

		float GetRotation() const;
		float GetWorldRotation() const;
		float GetOwnerRotation() const;

	private:
		Vector2f mPosition;
		float mRotation;

		mutable Vector2f mCachedWorldPosition;
		mutable bool mWorldPositionCacheDirty = true;

		mutable float mCachedWorldRotation;
		mutable bool mWorldRotationCacheDirty = true;

		OwnerVariant mOwner;

		std::list<ComponentPtr> mComponents;
	};
}