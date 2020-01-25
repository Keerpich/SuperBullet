#pragma once

#include "Object.h"
#include "AnimatedSpriteComponent.h"

namespace SuperBullet
{
	class MainCharacter : public Object
	{
	public:
		MainCharacter(const Vector2f & position);
		void Initialize();

		virtual void SetPosition(const Vector2f& position) override;

	private:
		void LoadRifleSpriteSheets();
		void AddMovementComponent();
		void MovementCallback(bool moved);

		std::list<std::shared_ptr<Texture>> spritesheets;
		std::shared_ptr<AnimatedSpriteComponent> mSpriteComponent;

		bool mIsMoving = false;
	};
}