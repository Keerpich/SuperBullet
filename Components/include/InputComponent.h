#pragma once

#include "../../ModuleInput/include/InputKeys.h"
#include "Component.h"

#include <memory>

namespace SuperBullet
{
	class MovementComponent;
	class ShootingComponent;
	class InputHandler;

	class InputComponent : public Component
	{
	public:
		InputComponent(std::shared_ptr<InputHandler> inputHandler);

		//Movement Component
		void RegisterComponent(InputKey key, 
			std::shared_ptr<MovementComponent> movementComponent);
		void UnregisterComponent(InputKey key,
			std::shared_ptr<MovementComponent> movementComponent);

		//Shooting Component
		void RegisterComponent(InputKey key,
			std::shared_ptr<ShootingComponent> shootingComponent);
		void UnregisterComponent(InputKey key,
			std::shared_ptr<ShootingComponent> shootingComponent);

	private:
		std::shared_ptr<InputHandler> mInputHandler;
	};
}