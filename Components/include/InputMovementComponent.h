#pragma once

#include "Component.h"

#include <functional>

namespace SuperBullet
{
	class InputMovementComponent : public Component
	{
	public:
		InputMovementComponent(
			float speedPerFrame, 
			const Vector2f& position, 
			int joystickDeadzone);

		InputMovementComponent(
			float speedPerFrame,
			const Vector2f& position,
			int joystickDeadzone,
			std::function<void(bool)> callback);

		void Update(float deltaSeconds) override;

	private:
		void SetOwnerPosition(const Vector2f& position);

		float mSpeedPerFrame;
		int mJoystickDeadzone;
		std::function<void(bool)> mCallback;
	};
}