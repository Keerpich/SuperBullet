#pragma once

#include "../../ModuleRendering/include/RenderStates.h"
#include "../../ModuleRendering/include/RenderTarget.h"
#include "../../ModuleRendering/include/Drawable.h"

namespace SuperBullet
{
	class IComponent : Drawable	
	{
	public:	
		IComponent();
		virtual ~IComponent() = 0;
		virtual void Update(float deltaSeconds) = 0;
		virtual void Draw(RenderTarget& target, RenderStates states);
	};
}