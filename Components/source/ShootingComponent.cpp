#include "../include/ShootingComponent.h"

namespace SuperBullet
{
	ShootingComponent::ShootingComponent(std::function<void()> callback) :
		mCallback(callback)
	{
	}

	void ShootingComponent::Shoot(float, float)
	{
		mShouldShoot = true;
	}

	void ShootingComponent::Update(float deltaSeconds)
	{
		if (mShouldShoot)
		{
			mCallback();
			mShouldShoot = false;
		}
	}
}
