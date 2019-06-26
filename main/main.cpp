#include "../ModuleWindow/include/Window.h"
#include "../ModuleRendering/include/CircleShape.h"	

int main()
{
	SuperBullet::Window window;

	SuperBullet::Sprite sprite;

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