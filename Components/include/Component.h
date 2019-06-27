#pragma once

#include <list>

#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"
#include "../../ModuleRendering/include/Drawable.h"

namespace SuperBullet
{
	class Component
	{
	public:
		virtual void Update(float deltaSeconds)  = 0;
		virtual void Draw(RenderTarget& target, RenderStates states) const;

		void AddDrawable(std::shared_ptr<Drawable> drawable);
		void RemoveDrawable(std::shared_ptr<Drawable> drawable);

	private:
		 std::list<DrawablePtr> mDrawables;
	};

	using ComponentPtr = std::shared_ptr<Component>;
}