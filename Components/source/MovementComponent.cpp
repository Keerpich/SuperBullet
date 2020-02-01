#include "..\include\MovementComponent.h"
#include "..\..\Utilities\include\Vector.h"
#include "..\..\ModuleInput\include\InputHandler.h"
#include "..\..\Utilities\include\Constants.h"

#include <memory>

namespace SuperBullet
{
	MovementComponent::MovementComponent(
		float speedPerFrame,
		const Vector2f & position) :
		MovementComponent(speedPerFrame, position, nullptr, nullptr)
	{
	}

	MovementComponent::MovementComponent(
		float speedPerFrame,
		const Vector2f &position,
		std::function<void(bool)> moveementCallback,
		std::function<void(float)> facingCallback) :
		Component(),
		mSpeedPerFrame(speedPerFrame),
		mMoveCallback(moveementCallback),
		mFacingCallback(facingCallback),
		mMovementDirectionVector(0, 0)
	{
		SetPosition(position);
	}

	void MovementComponent::SetMovementDirection(float x, float y)
	{
		this->mMovementDirectionVector.x = x;
		this->mMovementDirectionVector.y = y;
	}

	void MovementComponent::SetFacingDirection(float x, float y)
	{
		this->mFacingDirectionVector.x = x;
		this->mFacingDirectionVector.y = y;
	}

	void MovementComponent::Update(float deltaSeconds)
	{
		UpdateForMovement(deltaSeconds);
		UpdateForFacing(deltaSeconds);
	}

	void MovementComponent::UpdateForMovement(float deltaSeconds)
	{
		const Vector2f direction = mMovementDirectionVector.Normalize();
		const Vector2f currentPosition = GetOwnerPosition();
		const Vector2f newPosition =
			currentPosition + direction * mSpeedPerFrame * deltaSeconds;

		SetOwnerPosition(newPosition);

		if (mMoveCallback != nullptr)
			mMoveCallback(currentPosition != newPosition);

		//reset for next update
		mMovementDirectionVector.x = 0.f;
		mMovementDirectionVector.y = 0.f;
	}

	void MovementComponent::UpdateForFacing(float deltaSeconds)
	{
		const Vector2f direction = mFacingDirectionVector.Normalize();
		float radians = 0.f;

		if (direction.x >= 0.f)
		{
			if (direction.y >= 0.f)
			{
				radians = asinf(direction.y);
			}
			else
			{
				radians = 2 * PI_F + asinf(direction.y);
			}
		}
		else
		{
			radians = PI_F - asinf(direction.y);
		}

		const float degrees = radians * RADIANS_TO_DEGREES_F;

		SetOwnerRotation(degrees);

		if (mFacingCallback != nullptr)
			mFacingCallback(degrees);
	}

	void MovementComponent::SetOwnerPosition(const Vector2f& position)
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

	void MovementComponent::SetOwnerRotation(const float degrees)
	{
		Component::OwnerVariant owner = GetOwner();

		if (std::holds_alternative<std::weak_ptr<Component>>(owner))
		{
			std::shared_ptr<Component> component_owner = std::get<std::weak_ptr<Component>>(owner).lock();
			return component_owner->SetRotation(degrees);
		}
		else
		{
			std::shared_ptr<Object> object_owner = std::get <std::weak_ptr<Object>>(owner).lock();
			return object_owner->SetRotation(degrees);
		}
	}
}