#include "..\include\MainCharacter.h"
#include "..\include\InputComponent.h"
#include "..\include\MovementComponent.h"
#include "..\include\AnimatedSpriteComponent.h"
#include "..\include\ShootingComponent.h"

#include <iostream>

namespace SuperBullet
{
	MainCharacter::MainCharacter(
		const Vector2f & position,
		std::shared_ptr<InputHandler> &inputHandler) :
		Object(position),
		mInputHandler(inputHandler),
		mInputComponent(std::make_shared<InputComponent>(inputHandler)),
		mSpriteComponent(std::make_shared<AnimatedSpriteComponent>(1.f / 60.f * 3.f,
			false,
			true,
			position
			)),
		mShootingComponent(std::make_shared<ShootingComponent>([]() {std::cout << "Shit works yo\n"; }))
	{
	}

	void MainCharacter::Initialize()
	{
		LoadRifleSpriteSheets();

		mSpriteComponent->Play("idle");
		AddMovementComponent();
		AttachComponent(mShootingComponent);
		mInputComponent->RegisterComponent(InputKey::RightTrigger, mShootingComponent);
	}

	void MainCharacter::SetPosition(const Vector2f & position)
	{
		Object::SetPosition(position);
		mSpriteComponent->SetPosition(position);
	}

	void MainCharacter::LoadRifleSpriteSheets()
	{
		std::shared_ptr<Texture> idle_ss = std::make_shared<Texture>();
		idle_ss->loadFromFile("Assets/Character/Spritesheets/rifle_idle.png");
		spritesheets.push_back(idle_ss);
		mSpriteComponent->AddAnimation("idle", *idle_ss, Vector2u(0, 0), 3, 7, 20);

		std::shared_ptr<Texture> melee_ss = std::make_shared<Texture>();
		melee_ss->loadFromFile("Assets/Character/Spritesheets/rifle_melee.png");
		spritesheets.push_back(melee_ss);
		mSpriteComponent->AddAnimation("melee", *melee_ss, Vector2u(0, 0), 4, 3, 12);

		std::shared_ptr<Texture> move_ss = std::make_shared<Texture>();
		move_ss->loadFromFile("Assets/Character/Spritesheets/rifle_move.png");
		spritesheets.push_back(move_ss);
		mSpriteComponent->AddAnimation("move", *move_ss, Vector2u(0, 0), 3, 7, 20);

		std::shared_ptr<Texture> reload_ss = std::make_shared<Texture>();
		reload_ss->loadFromFile("Assets/Character/Spritesheets/rifle_reload.png");
		spritesheets.push_back(reload_ss);
		mSpriteComponent->AddAnimation("reload", *reload_ss, Vector2u(0, 0), 3, 7, 20);

		std::shared_ptr<Texture> shoot_ss = std::make_shared<Texture>();
		shoot_ss->loadFromFile("Assets/Character/Spritesheets/rifle_shoot.png");
		spritesheets.push_back(shoot_ss);
		mSpriteComponent->AddAnimation("shoot", *shoot_ss, Vector2u(0, 0), 3, 1, 3);

		AttachComponent(mSpriteComponent);
	}

	void MainCharacter::AddMovementComponent()
	{
		std::shared_ptr<MovementComponent> inputMovementComponent =
			std::make_shared<MovementComponent>(
				50.f,
				Vector2f(0, 0),
				std::bind(&MainCharacter::MovementCallback, this, std::placeholders::_1)
				);

		mInputHandler->RegisterCallback(InputKey::JoystickLeftStick,
			std::bind(&MovementComponent::SetMovementDirection,
				inputMovementComponent,
				std::placeholders::_1,
				std::placeholders::_2));

		AttachComponent(inputMovementComponent);
	}

	void MainCharacter::MovementCallback(bool moved)
	{
		if (moved && !mIsMoving)
		{
			mSpriteComponent->Play("move");
		}
		else if (!moved && mIsMoving)
		{
			mSpriteComponent->Play("idle");
		}

		mIsMoving = moved;
	}
}