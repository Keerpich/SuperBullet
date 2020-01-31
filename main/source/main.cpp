#include "../../ModuleWindow/include/Window.h"
#include "../../ModuleRendering/include/CircleShape.h"	
#include "../../ModuleRendering/include/Texture.h"
#include "../../Components/include/AnimatedSpriteComponent.h"
#include "../../Components/include/Component.h"
#include "../../Components/include/Object.h"
#include "../../Components/include/MainCharacter.h"
#include "../../ModuleInput/include/InputHandler.h"
#include "../../Utilities/include/Constants.h"

#include <chrono>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <memory>


std::chrono::system_clock::rep time_since_epoch() {
	auto now = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::seconds>(now).count();
}

int main()
{
	using ComponentPtr = std::shared_ptr<SuperBullet::Component>;

	SuperBullet::Window window;

	window.RegisterEventCallback(
		SuperBullet::Event::EventType::Closed,
		[&window]()
		{
			window.Close();
		}
	);

	std::shared_ptr<SuperBullet::InputHandler> inputHandler = 
		std::make_shared<SuperBullet::InputHandler>();

	std::shared_ptr<SuperBullet::MainCharacter> character = 
		std::make_shared<SuperBullet::MainCharacter>(
			SuperBullet::Vector2f(200.f, 200.f),
			inputHandler
		);

	character->Initialize();

	auto lastTime = std::chrono::system_clock::now();
	constexpr float kFrameTime = 1.f / FPS;
	float deltaTime = 0.f;

	while (window.IsOpen())
	{
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<float> timeSpan = currentTime - lastTime;
		lastTime = currentTime;
		deltaTime += timeSpan.count();

		while (deltaTime >= kFrameTime)
		{
			inputHandler->Update();


			character->Update(kFrameTime);
			window.PollEvents();
			window.Clear();
			window.Draw(character);
			window.Display();

			deltaTime -= kFrameTime;
		}

	}

	return 0;
}