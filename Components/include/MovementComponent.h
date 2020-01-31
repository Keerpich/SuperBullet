#pragma once

#include "Component.h"
#include "../../ModuleInput/include/InputHandler.h"

#include <functional>
#include <memory>

namespace SuperBullet
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(
			float speedPerFrame,
			const Vector2f& position
			);

		MovementComponent(
			float speedPerFrame,
			const Vector2f& position,
			std::function<void(bool)> callback);

		void SetMovementDirection(float x, float y);
		void Update(float deltaSeconds) override;

	private:
		void SetOwnerPosition(const Vector2f& position);

		float mSpeedPerFrame;
		std::function<void(bool)> mCallback;

		Vector2f mInputVector;
	};
}