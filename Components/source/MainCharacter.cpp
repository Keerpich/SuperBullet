#include "..\include\MainCharacter.h"
#include "..\include\InputMovementComponent.h"

SuperBullet::MainCharacter::MainCharacter(const Vector2f & position) :
	Object(position),
	mSpriteComponent(std::make_shared<AnimatedSpriteComponent>(5.f, false, true, position))
{
}

void SuperBullet::MainCharacter::Initialize()
{
	LoadRifleSpriteSheets();
	
	mSpriteComponent->Play("idle");

	AddMovementComponent();
}

void SuperBullet::MainCharacter::SetPosition(const Vector2f & position)
{
	Object::SetPosition(position);
	mSpriteComponent->SetPosition(position);
}

void SuperBullet::MainCharacter::LoadRifleSpriteSheets()
{
	std::shared_ptr<Texture> idle_ss = std::make_shared<Texture>();
	idle_ss->loadFromFile("Assets/Character/Spritesheets/rifle_idle.png");
	spritesheets.push_back(idle_ss);
	mSpriteComponent->AddAnimation("idle", *idle_ss, SuperBullet::Vector2u(0, 0), 3, 7, 20);

	std::shared_ptr<Texture> melee_ss = std::make_shared<Texture>();
	melee_ss->loadFromFile("Assets/Character/Spritesheets/rifle_melee.png");
	spritesheets.push_back(melee_ss);
	mSpriteComponent->AddAnimation("melee", *melee_ss, SuperBullet::Vector2u(0, 0), 4, 3, 12);

	std::shared_ptr<Texture> move_ss = std::make_shared<Texture>();
	move_ss->loadFromFile("Assets/Character/Spritesheets/rifle_move.png");
	spritesheets.push_back(move_ss);
	mSpriteComponent->AddAnimation("move", *move_ss, SuperBullet::Vector2u(0, 0), 3, 7, 20);

	std::shared_ptr<Texture> reload_ss = std::make_shared<Texture>();
	reload_ss->loadFromFile("Assets/Character/Spritesheets/rifle_reload.png");
	spritesheets.push_back(reload_ss);
	mSpriteComponent->AddAnimation("reload", *reload_ss, SuperBullet::Vector2u(0, 0), 3, 7, 20);

	std::shared_ptr<Texture> shoot_ss = std::make_shared<Texture>();
	shoot_ss->loadFromFile("Assets/Character/Spritesheets/rifle_shoot.png");
	spritesheets.push_back(shoot_ss);
	mSpriteComponent->AddAnimation("shoot", *shoot_ss, SuperBullet::Vector2u(0, 0), 3, 1, 3);

	AttachComponent(mSpriteComponent);
}

void SuperBullet::MainCharacter::AddMovementComponent()
{
	std::shared_ptr<InputMovementComponent> inputMovementComponent =
		std::make_shared<InputMovementComponent>(0.1f);

	AttachComponent(inputMovementComponent);
}
