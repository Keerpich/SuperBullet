#include "../ModuleWindow/include/Window.h"

#include "SFML/Graphics.hpp"

int main()
{
	SuperBullet::Window window;

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window.RegisterEventCallback(
		SuperBullet::Event::Closed,
		[&window]()
		{
			window.Close();
		}
	);

	while (window.IsOpen())
	{
		window.PollEvents();
		window.Clear();
		window.Draw(shape);
		window.Display();
	}

	return 0;
}