#pragma once

#include <list>
#include <memory>

#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"
#include "../../Utilities/include/Vector.h"

namespace SuperBullet
{
	class Component;

	class Object : public std::enable_shared_from_this<Object>
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;

	public:
		Object();
		Object(const Vector2f &position);
		Object(const Vector2f &position, float rotation);
		Object(const Object& other) = default;
		Object(Object&& other) = default;

		virtual ~Object() = default;

		Object& operator=(const Object& other) = default;
		Object& operator=(Object&& other) = default;

		//Don't attach components in constructor. We can't get a weak_ptr or shared_ptr to the object
		//before the object is constructed so it will set the component's owner to 'empty' which, most likely,
		//will result in a crash
		void AttachComponent(ComponentPtr component);
		void AttachComponents(std::list<ComponentPtr> components);

		void RemoveComponent(ComponentPtr component);

		void Update(float deltaSeconds);
		void Draw(RenderTarget& target, RenderStates states = RenderStates::Default) const;

		virtual void SetPosition(const Vector2f& position);
		Vector2<float> GetPosition() const;

		virtual void SetRotation(const float rotation);
		float GetRotation() const;

	private:
		std::list<ComponentPtr> mComponents;
		Vector2f mPosition;
		float mRotation;
	};
}