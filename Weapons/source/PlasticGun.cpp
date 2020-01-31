#include "../include/PlasticGun.h"
#include "../include/Projectile.h"

#include <iostream>

namespace SuperBullet
{
	PlasticGun::PlasticGun() :
		Weapon()
	{
	}

	std::shared_ptr<Projectile> PlasticGun::Shoot()
	{
		if (!IsOnCooldown())
		{
			std::cout << "Pew Pew, Plastic Gun\n";

			SetCooldown(kCooldownInSeconds);

			return std::make_shared<Projectile>();
		}

		return nullptr;
	}
}