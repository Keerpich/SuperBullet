#pragma once

#include <SFML/Window/Joystick.hpp>

namespace SuperBullet
{
	using Joystick = sf::Joystick;

	enum class InputKey : unsigned int
	{
		JoystickLeftStick,
		RightTrigger
	};
}