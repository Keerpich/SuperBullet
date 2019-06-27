#include "../include/Component.h"

namespace SuperBullet
{
	void Component::Draw(RenderTarget& target, RenderStates states) const
	{
		for (const DrawablePtr& drawable : mDrawables)
			target.draw(*drawable, states);
	}

	void Component::AddDrawable(std::shared_ptr<Drawable> drawable)
	{
		mDrawables.push_back(drawable);
	}

	void Component::RemoveDrawable(std::shared_ptr<Drawable> drawable)
	{
		std::list<DrawablePtr>::iterator it =
			std::find(mDrawables.begin(), mDrawables.end(), drawable);

		if (it != mDrawables.end())
			mDrawables.erase(it);
	}
}