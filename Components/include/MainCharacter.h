#pragma once

#include "Object.h"
#include "AnimatedSpriteComponent.h"

namespace SuperBullet
{
	class MainCharacter : public Object
	{
	public:
		MainCharacter(const Vector2f & position);

	private:
		void LoadRifleSpriteSheets();

		std::list<std::shared_ptr<Texture>> spritesheets;
		std::shared_ptr<AnimatedSpriteComponent> mSpriteComponent;
	};
}