#include "..\include\AnimatedSpriteComponent.h"

SuperBullet::AnimatedSpriteComponent::AnimatedSpriteComponent(
	float frameTimeInSeconds, 
	bool paused, 
	bool looped, 
	const Vector2f & position) :
	mAnimatedSprite(std::make_unique<AnimatedSprite>(sf::seconds(frameTimeInSeconds), paused, looped)),
	Component(position)
{
	mAnimatedSprite->setPosition(position);
}

SuperBullet::AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
}

void SuperBullet::AnimatedSpriteComponent::Update(float deltaSeconds)
{
	Component::Update(deltaSeconds);
	mAnimatedSprite->update(sf::seconds(deltaSeconds));
}

void SuperBullet::AnimatedSpriteComponent::Draw(RenderTarget & target, RenderStates states) const
{
	Component::Draw(target, states);
	mAnimatedSprite->draw(target, states);
}

void SuperBullet::AnimatedSpriteComponent::AddAnimation(
	const std::string &animationSetName,
	Texture & spriteSheet,
	const Vector2u & start,
	const int32_t columns,
	const int32_t lines,
	uint32_t framesCount)
{
	Animation animation;
	animation.setSpriteSheet(spriteSheet);

	const int32_t frame_width = spriteSheet.getSize().x / columns;
	const int32_t frame_height = spriteSheet.getSize().y / lines;

	int32_t frames = 0;

	for (int32_t i = 0; i < lines; ++i)
	{
		const int32_t y_offset = i * frame_height;

		for (int32_t j = 0; j < columns; ++j)
		{
			const int32_t x_offset = j * frame_width;

			const Vector2i currentPosition(start.x + x_offset, start.y + y_offset);

			animation.addFrame(sf::IntRect(currentPosition.x, currentPosition.y, frame_width, frame_height));
			++frames;

			if (frames >= framesCount)
				break;
		}

		if (frames >= framesCount)
			break;
	}

	mAnimations.insert(std::make_pair(animationSetName, animation));
}

void SuperBullet::AnimatedSpriteComponent::Play(const std::string & animationName)
{
	mAnimatedSprite->play(mAnimations[animationName]);
}
