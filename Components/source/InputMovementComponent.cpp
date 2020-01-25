#include "..\include\InputMovementComponent.h"
#include "..\..\Utilities\include\Vector.h"


SuperBullet::InputMovementComponent::InputMovementComponent(
	float speedPerFrame,
	const Vector2f & position,
	int joystickDeadzone) :
	InputMovementComponent(speedPerFrame, position, joystickDeadzone, nullptr)
{
}

SuperBullet::InputMovementComponent::InputMovementComponent(
	float speedPerFrame,
	const Vector2f &position,
	int joystickDeadzone,
	std::function<void(bool)> callback) :
	Component(),
	mSpeedPerFrame(speedPerFrame),
	mJoystickDeadzone(joystickDeadzone),
	mCallback(callback)
{
	SetPosition(position);
}

void SuperBullet::InputMovementComponent::Update(float deltaSeconds)
{
	float x = 0, y = 0;

	//TODO: Add key mapping possibility
	if (sf::Joystick::isConnected(0))
	{
		x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

		const float joystickMagnitude = Vector2f(x, y).Magnitude();
		if (joystickMagnitude < mJoystickDeadzone)
		{
			x = 0;
			y = 0;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			x -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			x += 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			y -= 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			y += 1;
		}
	}

	const Vector2f direction = Vector2f(x, y).Normalize();
	const Vector2f currentPosition = GetOwnerPosition();
	const Vector2f newPosition = currentPosition + direction * mSpeedPerFrame;

	SetOwnerPosition(newPosition);
	mCallback(currentPosition != newPosition);
}

void SuperBullet::InputMovementComponent::SetOwnerPosition(const Vector2f& position)
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
