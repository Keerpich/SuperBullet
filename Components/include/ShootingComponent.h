#pragma once

#include "Component.h"

#include <functional>

namespace SuperBullet
{
	class Weapon;

	class ShootingComponent : public Component
	{
	public:
		ShootingComponent(std::shared_ptr<Weapon> weapon, 
			std::function<void()> callback);

		void Shoot(float, float);
		void Update(float deltaSeconds) override;

	private:
		bool mDidShoot = false;
		std::shared_ptr<Weapon> mpWeapon;
		std::function<void()> mCallback;
	};
}
