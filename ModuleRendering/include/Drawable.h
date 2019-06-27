#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace SuperBullet
{
	using Drawable = sf::Drawable;
	using DrawablePtr = std::shared_ptr<Drawable>;
}