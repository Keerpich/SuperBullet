#include "..\include\PlayerMovementComponent.h"
#include "..\..\Utilities\include\Vector.h"
#include "..\..\ModuleInput\include\InputHandler.h"

#include <memory>

namespace SuperBullet
{
	PlayerMovementComponent::PlayerMovementComponent(
		std::shared_ptr<InputHandler> &inputHandler,
		float speedPerFrame,
		const Vector2f & position) :
		PlayerMovementComponent(inputHandler, speedPerFrame, position, nullptr)
	{
	}

	PlayerMovementComponent::PlayerMovementComponent(
		std::shared_ptr<InputHandler> &inputHandler,
		float speedPerFrame,
		const Vector2f &position,
		std::function<void(bool)> callback) :
		Component(),
		mInputHandler(inputHandler),
		mSpeedPerFrame(speedPerFrame),
		mCallback(callback),
		mInputVector(0, 0)
	{
		SetPosition(position);

		mInputHandler->RegisterCallback(InputKey::JoystickLeftStick,
			[this](float x, float y) -> void
		{
			this->mInputVector.x = x;
			this->mInputVector.y = y;
		});
	}

	PlayerMovementComponent::~PlayerMovementComponent()
	{
		mInputHandler->UnregisterCallback(InputKey::JoystickLeftStick);
	}

	void PlayerMovementComponent::Update(float deltaSeconds)
	{
		const Vector2f direction = mInputVector.Normalize();
		const Vector2f currentPosition = GetOwnerPosition();
		const Vector2f newPosition = 
			currentPosition + direction * mSpeedPerFrame * deltaSeconds;

		SetOwnerPosition(newPosition);
		mCallback(currentPosition != newPosition);

		//reset for next update
		mInputVector.x = 0.f;
		mInputVector.y = 0.f;
	}

	void PlayerMovementComponent::SetOwnerPosition(const Vector2f& position)
	{
		Component::OwnerVariant owner = GetOwner();

		if (std::holds_alternative<std::weak_ptr<Component>>(owner))
		{
			std::shared_ptr<Component> component_owner = std::get<std::weak_ptr<Component>>(owner).lock();
			return component_owner->SetPosition(position);
		}
		else
		{
			std::shared_ptr<Object> object_owner = std::get <std::weak_ptr<Object>>(owner).lock();
			return object_owner->SetPosition(position);
		}
	}
}