#pragma once

#include "Component.h"

namespace SuperBullet
{
	class InputMovementComponent : public Component
	{
	public:
		InputMovementComponent(float speedPerFrame);
		InputMovementComponent(float speedPerFrame, const Vector2f& position);

		void Update(float deltaSeconds) override;

	private:
		void SetOwnerPosition(const Vector2f& position);

		float mSpeedPerFrame = 0.f;
	};
}