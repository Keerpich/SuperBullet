#include "..\include\InputMovementComponent.h"
#include "..\..\Utilities\include\Vector.h"

SuperBullet::InputMovementComponent::InputMovementComponent(float speedPerFrame) :
	Component(),
	mSpeedPerFrame(speedPerFrame)
{
}

SuperBullet::InputMovementComponent::InputMovementComponent(float speedPerFrame, const Vector2f & position) :
	Component(position),
	mSpeedPerFrame(speedPerFrame)
{
}

void SuperBullet::InputMovementComponent::Update(float deltaSeconds)
{
	float x = 0, y = 0;

	if (sf::Joystick::isConnected(0))
	{
		x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
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

	Vector2f direction = Vector2f(x, y).Normalize();
	Vector2f currentPosition = GetOwnerPosition();
	Vector2f newPosition = currentPosition + direction * mSpeedPerFrame;
	SetOwnerPosition(newPosition);
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
