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
			std::function<void(bool)> moveementCallback,
			std::function<void(float)> facingCallback);

		void SetMovementDirection(float x, float y);
		void SetFacingDirection(float x, float y);

		void Update(float deltaSeconds) override;
		void UpdateForMovement(float deltaSeconds);
		void UpdateForFacing(float deltaSeconds);

	private:
		void SetOwnerPosition(const Vector2f& position);
		void SetOwnerRotation(const float degrees);

		float mSpeedPerFrame;
		std::function<void(bool)> mMoveCallback;
		std::function<void(float)> mFacingCallback;

		Vector2f mMovementDirectionVector;
		Vector2f mFacingDirectionVector = Vector2f::Right;
	};
}