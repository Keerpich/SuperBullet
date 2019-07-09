#include "..\include\Window.h"

SuperBullet::Window::Window(const unsigned int width, const unsigned int height, const char * title) :
	mWindow(sf::VideoMode(width, height), title)
{
}

SuperBullet::Window::~Window()
{
	mWindow.close();
}

bool SuperBullet::Window::IsOpen() const
{
	return mWindow.isOpen();
}

void SuperBullet::Window::Close()
{
	mWindow.close();
}

void SuperBullet::Window::Clear()
{
	mWindow.clear();
}

void SuperBullet::Window::Draw(const std::shared_ptr<SuperBullet::Object> object)
{
	object->Draw(mWindow);
}

void SuperBullet::Window::Display()
{
	mWindow.display();
}

void SuperBullet::Window::PollEvents()
{
	sf::Event event;

	while(mWindow.pollEvent(event))
	{
		auto it = mCallbacks.find(static_cast<Event>(event.type));
		if (it != mCallbacks.end())
		{
			for (auto &callback : it->second)
			{
				callback();
			}
		}
	}
}

void SuperBullet::Window::RegisterEventCallback(Event e, EventCallback callback)
{
	auto eventPosition = mCallbacks.find(e);
	if (eventPosition != mCallbacks.end())
	{
		eventPosition->second.push_back(callback);
	}
	else
	{
		mCallbacks.insert(std::make_pair(e, EventCallbackList{ callback }));
	}
}

void SuperBullet::Window::UnregisterEventCallback(Event e, EventCallback callback)
{
	auto eventPosition = mCallbacks.find(e);
	if (eventPosition != mCallbacks.end())
	{
		mCallbacks.erase(eventPosition);
	}
}
