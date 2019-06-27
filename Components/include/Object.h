#pragma once

#include <list>

#include "Component.h"
#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"

namespace SuperBullet
{
	using Vector2f = sf::Vector2<float>;

	class Object final
	{
	public:
		Object();
		Object(const Vector2f &position);

		void AttachComponent(ComponentPtr component);
		void AttachComponents(std::list<ComponentPtr> components);

		void RemoveComponent(ComponentPtr component);

		void Update(float deltaSeconds);
		void Draw(RenderTarget& target, RenderStates states = RenderStates::Default) const;

	private:
		std::list<ComponentPtr> mComponents;
		Vector2f mPosition;
	};
}