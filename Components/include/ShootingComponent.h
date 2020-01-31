#pragma once

#include "Component.h"

#include <functional>

namespace SuperBullet
{
	class Projectile
	{
	};

	class Weapon
	{
	public:
		Weapon() = default;
		virtual ~Weapon() = 0;
		Weapon(const Weapon& weapon) = default;
		Weapon& operator=(Weapon& other) = default;
		Weapon(Weapon&& weapon) = default;
		Weapon& operator=(Weapon&& other) = default;

		virtual std::shared_ptr<Projectile> Shoot() = 0;
		void ElapseCooldown(float cooldown);
		void SetCooldown(float cooldown);
		bool IsOnCooldown();

	private:
		float mCurrentCooldown = 0.f;
	};

	class PlasticGun : public Weapon
	{
	public:
		PlasticGun();
		virtual ~PlasticGun() = default;
		std::shared_ptr<Projectile> Shoot() override;

	private:
		const float kCooldownInSeconds = 2.f;
	};

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
