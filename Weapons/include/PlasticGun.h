#pragma once

#include "Weapon.h"

namespace SuperBullet
{
    class Projectile;

    class PlasticGun : public Weapon
	{
	public:
		PlasticGun();
		virtual ~PlasticGun() = default;
		std::shared_ptr<Projectile> Shoot() override;

	private:
		const float kCooldownInSeconds = 2.f;
	};

}