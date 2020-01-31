#pragma once

#include <memory>

#include "Object.h"
#include "../../ModuleInput/include/InputHandler.h"
#include "../../ModuleRendering/include/Texture.h"

namespace SuperBullet
{
	class AnimatedSpriteComponent;
	class InputComponent;
	class ShootingComponent;;

	class MainCharacter : public Object
	{
	public:
		MainCharacter(const Vector2f & position, 
			std::shared_ptr<InputHandler> &inputHandler);
		void Initialize();

		virtual void SetPosition(const Vector2f& position) override;

	private:
		void LoadRifleSpriteSheets();
		void AddMovementComponent();
		void MovementCallback(bool moved);

		std::shared_ptr<InputHandler> mInputHandler;

		std::list<std::shared_ptr<Texture>> spritesheets;
		std::shared_ptr<InputComponent> mInputComponent;
		std::shared_ptr<AnimatedSpriteComponent> mSpriteComponent;
		std::shared_ptr<ShootingComponent> mShootingComponent;

		bool mIsMoving = false;
	};
}