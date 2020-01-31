#include "../include/ShootingComponent.h"

#include <cmath>
#include <iostream>

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

	inline Weapon::~Weapon()
	{

	}

	void Weapon::ElapseCooldown(float cooldown)
	{
		mCurrentCooldown -= cooldown;
		mCurrentCooldown = fmax(0.f, mCurrentCooldown);
	}

	void Weapon::SetCooldown(float cooldown)
	{
		mCurrentCooldown = cooldown;
	}

	bool Weapon::IsOnCooldown()
	{
		return mCurrentCooldown > FLT_EPSILON;
	}

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
