#include "../include/Weapon.h"

namespace SuperBullet
{
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
}