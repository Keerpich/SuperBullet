#pragma once

#include <memory>

#include "Object.h"
#include "../../ModuleInput/include/InputHandler.h"
#include "../../ModuleRendering/include/Texture.h"

namespace SuperBullet
{
	class AnimatedSpriteComponent;
	class InputComponent;
	class ShootingComponent;
	class MovementComponent;
	class Weapon;

	class MainCharacter : public Object
	{
	public:
		MainCharacter(const Vector2f & position, 
			std::shared_ptr<InputHandler> &inputHandler);

		//Need to initialize through this becase we use 'weak_from_this()'
		//which returns nullptr if used in constructor causing everything to crash
		void Initialize();

		virtual void SetPosition(const Vector2f& position) override;
		virtual void SetRotation(const float degrees) override;

	private:
		void InitializeSpriteComponent();
		void InitializeMovementComponent();
		void InitializeShootingComponent();
		void InitializeInputComponent();

		void MovementCallback(bool moved);

		std::shared_ptr<InputHandler> mInputHandler;

		std::list<std::shared_ptr<Texture>> spritesheets;
		std::shared_ptr<InputComponent> mInputComponent;
		std::shared_ptr<AnimatedSpriteComponent> mSpriteComponent;
		std::shared_ptr<ShootingComponent> mShootingComponent;
		std::shared_ptr<MovementComponent> mMovementComponent;
		std::shared_ptr<Weapon> mCurrentGun;

		bool mIsMoving = false;
	};
}