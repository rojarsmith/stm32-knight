#include <typeinfo>
#include <gui/widget/TextureMapperAnimation.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Application.hpp>

TextureMapperAnimation::TextureMapperAnimation()
	:
	frameTick(0)	
{
}

TextureMapperAnimation::~TextureMapperAnimation()
{
}

void TextureMapperAnimation::handleTickEvent()
{
	renderAnimation(frameTick);

	frameTick++;
}

void TextureMapperAnimation::setBitmaps(BitmapId start, BitmapId end)
{
	startId = start;
	endId = end;
	this->setBitmap(Bitmap(start));
}

void TextureMapperAnimation::setAnimationStoppedCallback(GenericCallback<const TextureMapperAnimation&>& callback)
{
	animationStoppedCallback = &callback;
}

void TextureMapperAnimation::startAnimation(const int inventory, const int frequency, const int alpha, const float scale)
{
	this->inventory = inventory;
	this->inventoryCach = inventory;
	this->frequency = frequency;
	this->currentAlpha = this->getAlpha();
	this->targetAlpha = alpha;
	this->currentScale = this->getScale();
	this->targetScale = scale;

	Application::getInstance()->registerTimerWidget(this);
}

void TextureMapperAnimation::renderAnimation(const int tick)
{
	if (0 != tick % frequency) return;

	if (0 == inventory) 
	{ 
		return;
	}
	else if (0 < inventory)
	{
		int idx = this->getBitmap().getId() + 1;
		if (idx > endId)
		{
			idx = startId;
		}
		this->setBitmap(Bitmap(idx));
		this->setWidth(HAL::DISPLAY_WIDTH);
		this->setHeight(HAL::DISPLAY_HEIGHT);
		this->setAlpha(targetAlpha - (targetAlpha - currentAlpha) / inventoryCach * inventory);
		this->setScale(targetScale - (targetScale - currentScale) / inventoryCach * inventory);
		this->invalidate();
		inventory--;

		if (0 == inventory)
		{
			Application::getInstance()->unregisterTimerWidget(this);
			if (animationStoppedCallback && animationStoppedCallback->isValid())
			{
				animationStoppedCallback->execute(*this);
			}
		}
	}
	else if (0 > inventory)
	{
		int idx = this->getBitmap().getId() - 1;
		if (idx < startId)
		{
			idx = endId;
		}
		this->setBitmap(Bitmap(idx));
		this->setWidth(HAL::DISPLAY_WIDTH);
		this->setHeight(HAL::DISPLAY_HEIGHT);
		this->setAlpha(targetAlpha - (targetAlpha - currentAlpha) / inventoryCach * inventory);
		this->setScale(targetScale - (targetScale - currentScale) / inventoryCach * inventory);
		this->invalidate();
		inventory++;

		if (0 == inventory)
		{
			Application::getInstance()->unregisterTimerWidget(this);
			if (animationStoppedCallback && animationStoppedCallback->isValid())
			{
				animationStoppedCallback->execute(*this);
			}
		}
	}
}
