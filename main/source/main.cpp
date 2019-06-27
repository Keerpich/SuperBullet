#include "../../ModuleWindow/include/Window.h"
#include "../../ModuleRendering/include/CircleShape.h"	
#include "../../Components/include/Component.h"
#include "../../Components/include/Object.h"


class CircleComponent : public SuperBullet::Component
{
public:
	CircleComponent(float radius, sf::Color color) :
		mCircleShape(std::make_shared<SuperBullet::CircleShape>(radius))
	{
		mCircleShape->setFillColor(color);
		AddDrawable(std::static_pointer_cast<SuperBullet::Drawable>(mCircleShape));
	}

	virtual void Update(float deltaSeconds) override {};

private:
	std::shared_ptr<SuperBullet::CircleShape> mCircleShape = nullptr;
};

int main()
{
	SuperBullet::Window window;

	SuperBullet::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	SuperBullet::Object obj;
	SuperBullet::ComponentPtr circleComponent = std::static_pointer_cast<SuperBullet::Component>(std::make_shared<CircleComponent>(100.f, sf::Color::Green));
	obj.AttachComponent(circleComponent);

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
		window.Draw(obj);
		window.Display();
	}

	return 0;
}