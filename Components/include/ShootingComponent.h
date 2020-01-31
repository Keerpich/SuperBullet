#pragma once

#include "Component.h"

#include <functional>

namespace SuperBullet
{
	class ShootingComponent : public Component
	{
	public:
		ShootingComponent(std::function<void()> callback);

		void Shoot(float, float);
		void Update(float deltaSeconds) override;

	private:
		bool mShouldShoot = false;
		std::function<void()> mCallback;
	};
}
