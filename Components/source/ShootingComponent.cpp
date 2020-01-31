#include "../include/ShootingComponent.h"
#include "../../Weapons/include/Weapon.h"
#include "../../Weapons/include/Projectile.h"

#include <cmath>

namespace SuperBullet
{
	ShootingComponent::ShootingComponent(
		std::shared_ptr<Weapon> weapon,
		std::function<void()> callback) :
		mpWeapon(weapon),
		mCallback(callback)
	{
	}

	void ShootingComponent::Shoot(float, float)
	{
		auto projectile = mpWeapon->Shoot();

		if (projectile)
			mDidShoot = true;
	}

	void ShootingComponent::Update(float deltaSeconds)
	{
		if (mDidShoot)
		{
			mCallback();
			mDidShoot = false;
		}

		if (mpWeapon)
		{
			mpWeapon->ElapseCooldown(deltaSeconds);
		}
	}
}
