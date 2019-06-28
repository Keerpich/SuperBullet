#pragma once

#include <list>
#include <memory>

#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"

namespace SuperBullet
{
	using Vector2f = sf::Vector2<float>;
	class Component;

	class Object final
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;

	public:
		Object();
		Object(const Vector2f &position);

		~Object() = default;

		void AttachComponent(ComponentPtr component);
		void AttachComponents(std::list<ComponentPtr> components);

		void RemoveComponent(ComponentPtr component);

		void Update(float deltaSeconds);
		void Draw(RenderTarget& target, RenderStates states = RenderStates::Default) const;

		void SetPosition(const Vector2f& position);
		Vector2f GetPosition() const;

	private:
		std::list<ComponentPtr> mComponents;
		Vector2f mPosition;
	};
}