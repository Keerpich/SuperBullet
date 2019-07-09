#pragma once

#include <list>
#include <memory>

#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"

namespace SuperBullet
{
	using Vector2f = sf::Vector2<float>;
	using Vector2i = sf::Vector2<int>;
	using Vector2u = sf::Vector2u;
	constexpr float FPS = 60.f;
	class Component;

	class Object : public std::enable_shared_from_this<Object>
	{
	private:
		using ComponentPtr = std::shared_ptr<Component>;

	public:
		Object();
		Object(const Vector2f &position);

		virtual ~Object() = default;

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