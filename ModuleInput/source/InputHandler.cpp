#include "../include/InputHandler.h"
#include "../../Utilities/include/Vector.h"

namespace SuperBullet
{
	void InputHandler::RegisterCallback(InputKey key, 
		std::function<void(float, float)> callback)
    {
        UnregisterCallback(key);
        
        mJoystickCallbacks.insert(std::make_pair(key, callback));
    }

    void InputHandler::UnregisterCallback(InputKey key)
    {
        if (const auto result = mJoystickCallbacks.find(key); 
            result != mJoystickCallbacks.end())
        {
            mJoystickCallbacks.erase(result);
        }
    }

    void InputHandler::Update()
    {
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
    }

	bool InputHandler::IsInUse(InputKey key)
	{
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
	}
}