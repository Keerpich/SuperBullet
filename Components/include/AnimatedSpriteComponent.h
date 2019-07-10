#pragma once

#include <string>
#include <map>

#include "Component.h"
#include "../../ModuleRendering/include/AnimatedSprite.h"
#include "../../ModuleRendering/include/Texture.h"
#include "../../Utilities/include/Vector.h"

namespace SuperBullet
{
	class AnimatedSpriteComponent : public Component
	{
	public:
		AnimatedSpriteComponent(float frameTimeInSeconds, bool paused, bool looped, const Vector2f &position);
		virtual ~AnimatedSpriteComponent();

		virtual void Update(float deltaSeconds) override;
		virtual void Draw(RenderTarget& target, RenderStates states) const override;
		
		void AddAnimation(
			const std::string &animationSetName, 
			Texture &spriteSheet, 
			const Vector2u &start, 
			const int32_t columns, 
			const int32_t lines, 
			uint32_t framesCount
		);

		void Play(const std::string &animationName);

		void SetPosition(const Vector2f &position) override;

	private:
		std::unique_ptr<AnimatedSprite> mAnimatedSprite;
		std::map<std::string, Animation> mAnimations;
	};
}