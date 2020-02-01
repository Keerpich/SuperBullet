#pragma once

#include <memory>

namespace SuperBullet
{
	class Projectile;

    class Weapon
    {
    public:
        Weapon() = default;
        virtual ~Weapon() = default;
        Weapon(const Weapon& weapon) = default;
        Weapon& operator=(const Weapon& other) = default;
        Weapon(Weapon&& weapon) = default;
        Weapon& operator=(Weapon&& other) = default;

        virtual std::shared_ptr<Projectile> Shoot() = 0;
        void ElapseCooldown(float cooldown);
        void SetCooldown(float cooldown);
        bool IsOnCooldown();

    private:
        float mCurrentCooldown = 0.f;
    };
}