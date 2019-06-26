#include "../include/Component.h"

namespace SuperBullet
{
	IComponent::IComponent() : 
		Drawable()
	{
	}

	void IComponent::Draw(RenderTarget& target, RenderStates states)
	{
		draw(target, states);
	}
}