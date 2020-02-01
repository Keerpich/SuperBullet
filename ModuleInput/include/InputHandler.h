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

		void UnregisterCallback(InputKey key);

		void Update();

    private:
		bool IsInUse(InputKey key);

		static constexpr float skJoystickLeftStickDeadzone = 20.f;
		static constexpr float skJoystickRightStickDeadzone = 20.f;
		static constexpr float skJoystickRightTriggerDeadzone = 10.f;

        std::map<InputKey, std::function<void(float, float)>> mJoystickCallbacks;
    };
}