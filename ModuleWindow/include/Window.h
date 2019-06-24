#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <functional>
#include <map>

namespace SuperBullet
{
	enum class Event
	{
		Closed
	};

	class Window
	{
	public:
		Window(
			const unsigned int width = 800,
			const unsigned int height = 600,
			const char* title = "Untitled"
		);

		~Window();

		bool IsOpen() const;
		void Close();

		void Clear();
		///TODO: Replace the parameter with a more abstract one
		///once we implement a GFX module
		void Draw(const sf::Drawable &drawable);
		void Display();

		void PollEvents();

		using EventCallback = std::function<void()>;
		
		void RegisterEventCallback(Event e, EventCallback callback);
		void UnregisterEventCallback(Event e, EventCallback callback);
		
	private:
		sf::RenderWindow mWindow;

		using EventCallbackList = std::list<std::function<void()>>;
		std::map<Event, EventCallbackList> mCallbacks;

	};
}
