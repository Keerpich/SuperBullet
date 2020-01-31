#include "..\include\InputComponent.h"

#include "..\..\ModuleInput\include\InputHandler.h"
#include "..\include\MovementComponent.h"
#include "..\include\ShootingComponent.h"

namespace SuperBullet
{
	InputComponent::InputComponent(std::shared_ptr<InputHandler> inputHandler) :
		mInputHandler(inputHandler)
	{
	}

	void InputComponent::RegisterComponent(InputKey key, std::shared_ptr<MovementComponent> movementComponent)
	{
		mInputHandler->RegisterCallback(key,
			std::bind(&MovementComponent::SetMovementDirection,
				movementComponent,
				std::placeholders::_1,
				std::placeholders::_2));
	}

	void InputComponent::UnregisterComponent(InputKey key, 
		std::shared_ptr<MovementComponent> movementComponent)
	{
		mInputHandler->UnregisterCallback(key);
	}

	void InputComponent::RegisterComponent(InputKey key, 
		std::shared_ptr<ShootingComponent> shootingComponent)
	{
		mInputHandler->RegisterCallback(key,
			std::bind(&ShootingComponent::Shoot,
				shootingComponent,
				std::placeholders::_1,
				std::placeholders::_2));
	}

	void InputComponent::UnregisterComponent(InputKey key,
		std::shared_ptr<ShootingComponent> shootingComponent)
	{
		mInputHandler->UnregisterCallback(key);
	}
}
