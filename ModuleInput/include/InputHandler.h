#pragma once

#include <functional>
#include <map>

#include "InputKeys.h"

namespace SuperBullet
{
    class InputHandler
    {
    public:
        /// Callbacks for normal buttons will have both parameters
        /// set 0, callbacks for buttons with scale values (e.g. triggers)
        /// will have the first parameter set to the value and callbacks
        /// for sticks will have both parameters set for x and y.
        /// WARNING: Make sure to unregister when you destroy the callback owner
		void RegisterCallback(InputKey key,
			std::function<void(float, float)> callback);
		/*{
			UnregisterCallback(key);

			mJoystickCallbacks.insert(std::make_pair(key, callback));
		}*/

		void UnregisterCallback(InputKey key);
		/*{
			if (const auto result = mJoystickCallbacks.find(key);
				result != mJoystickCallbacks.end())
			{
				mJoystickCallbacks.erase(result);
			}
		}*/

		void Update();
		/*{
			if (IsInUse(InputKey::JoystickLeftStick))
			{
				if (const auto result = mJoystickCallbacks.find(InputKey::JoystickLeftStick);
					result != mJoystickCallbacks.end())
				{
					float x = Joystick::getAxisPosition(0, Joystick::Axis::X);
					float y = Joystick::getAxisPosition(0, Joystick::Axis::Y);

					mJoystickCallbacks[InputKey::JoystickLeftStick](x, y);
				}
			}
		}*/

    private:
		bool IsInUse(InputKey key);
		/*{
			switch (key)
			{
			case SuperBullet::InputKey::JoystickLeftStick:
			{
				float x = Joystick::getAxisPosition(0, Joystick::Axis::X);
				float y = Joystick::getAxisPosition(0, Joystick::Axis::Y);

				const Vector2f stickVector(x, y);
				const float stickMagnitude = stickVector.Magnitude();

				if (stickMagnitude > 20.f)
					return true;
				else
					return false;
			}
			break;
			default:
			{
				return false;
			}
			break;
			}
		}*/

		//static constexpr float skJoystickLeftStickDeadzone = 20.f;

        std::map<InputKey, std::function<void(float, float)>> mJoystickCallbacks;
    };
}