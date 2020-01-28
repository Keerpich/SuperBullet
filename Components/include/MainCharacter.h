#pragma once

#include <memory>

#include "Object.h"
#include "AnimatedSpriteComponent.h"
#include "../../ModuleInput/include/InputHandler.h"

namespace SuperBullet
{
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
		std::shared_ptr<AnimatedSpriteComponent> mSpriteComponent;

		bool mIsMoving = false;
	};
}