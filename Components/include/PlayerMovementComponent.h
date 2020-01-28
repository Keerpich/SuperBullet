#pragma once

#include "Component.h"
#include "../../ModuleInput/include/InputHandler.h"

#include <functional>
#include <memory>

namespace SuperBullet
{
	class PlayerMovementComponent : public Component
	{
	public:
		PlayerMovementComponent(
			std::shared_ptr<InputHandler> &inputHandler,
			float speedPerFrame,
			const Vector2f& position
			);

		PlayerMovementComponent(
			std::shared_ptr<InputHandler> &inputHandler,
			float speedPerFrame,
			const Vector2f& position,
			std::function<void(bool)> callback);

		~PlayerMovementComponent();

		void Update(float deltaSeconds) override;

	private:
		void SetOwnerPosition(const Vector2f& position);

		std::shared_ptr<InputHandler> mInputHandler;
		float mSpeedPerFrame;
		std::function<void(bool)> mCallback;

		Vector2f mInputVector;
	};
}