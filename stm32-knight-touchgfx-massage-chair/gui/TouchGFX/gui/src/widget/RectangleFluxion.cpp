#include <typeinfo>
#include <gui/widget/RectangleFluxion.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

RectangleFluxion::RectangleFluxion()
{
	add(animationU);
	add(animationR);
	add(animationD);
	add(animationL);
}

RectangleFluxion::~RectangleFluxion()
{
}

void RectangleFluxion::start(const int inventory, const int frequency, const int times)
{
	this->inventory = (int)(inventory * 0.8);
	this->inventoryMax = (int)(inventory * 0.8);
	this->inventory2 = (inventory - this->inventory);
	this->inventoryMax2 = (inventory - this->inventoryMax);
	this->frequency = frequency;
	this->times = times;

	//application().getInstance()->registerTimerWidget(this);
	//touchgfx::Application::getInstance()->registerTimerWidget(this);
	Application::getInstance()->registerTimerWidget(this);
}

void RectangleFluxion::handleTickEvent()
{
	int w = 10;

	if (0 == inventory % frequency)
	{
		int ug = 148 - (148 - 0) / inventoryMax * inventory;
		int ub = 255 - (255 - 0) / inventoryMax * inventory;
		int ua = 255 - (255 - 0) / inventoryMax * inventory;
		int16_t uxs = (int16_t)(1.0 * (getWidth() - w * 3) / inventoryMax * (inventoryMax - inventory));
		int16_t uxe = (int16_t)(w * 3 + 1.0 * (getWidth() - w * 3) / inventoryMax * (inventoryMax - inventory));
		colorPainter.setColor(Color::getColorFromRGB(0, ug, ub));
		animationU.setPosition(0, 0, getWidth(), w);
		animationU.setLineWidth(w);
		animationU.setAlpha(ua);
		animationU.setPainter(colorPainter);
		animationU.updateStart(uxs, (int16_t)0);
		animationU.updateEnd(uxe, (int16_t)0);

		int16_t dxs = (int16_t)(getWidth() - 1.0 * (getWidth() - w * 3) / inventoryMax * (inventoryMax - inventory));
		int16_t dxe = (int16_t)(getWidth() - w * 3 - (1.0 * getWidth() - w * 3) / inventoryMax * (inventoryMax - inventory));
		animationD.setPosition(0, getHeight() - w, getWidth(), w);
		animationD.setLineWidth(w);
		animationD.setAlpha(ua);
		animationD.setPainter(colorPainter);
		animationD.updateStart(dxs, (int16_t)0);
		animationD.updateEnd(dxe, (int16_t)0);

		int16_t lxs = (int16_t)(getHeight() - 1.0 * (getHeight() - w * 3) / inventoryMax * (inventoryMax - inventory));
		int16_t lxe = (int16_t)(getHeight() - w * 3 - (1.0 * getHeight() - w * 3) / inventoryMax * (inventoryMax - inventory));
		animationL.setPosition(0, 0, w, getHeight());
		animationL.setLineWidth(w);
		animationL.setAlpha(ua);
		animationL.setPainter(colorPainter);
		animationL.updateStart((int16_t)0, lxs);
		animationL.updateEnd((int16_t)0, lxe);

		int16_t rxs = (int16_t)(1.0 * (getHeight() - w * 3) / inventoryMax * (inventoryMax - inventory));
		int16_t rxe = (int16_t)(w * 3 + 1.0 * (getHeight() - w * 3) / inventoryMax * (inventoryMax - inventory));
		animationR.setPosition(getWidth() - w, 0, w, getHeight());
		animationR.setLineWidth(w);
		animationR.setAlpha(ua);
		animationR.setPainter(colorPainter);
		animationR.updateStart((int16_t)0, rxs);
		animationR.updateEnd((int16_t)0, rxe);
	}

	inventory--;

	if (0 == inventory2)
	{
		Application::getInstance()->unregisterTimerWidget(this);
	}

	if (0 >= inventory && times > 0)
	{
		animationU.setAlpha(0);
		animationU.invalidate();
		inventory = inventoryMax;
		times--;
	}
	else if (0 >= inventory && times <= 0)
	{
		int ua2 = 255 - 255 / inventoryMax2 * (inventoryMax2 - inventory2);
		animationU.setAlpha(ua2);
		animationU.invalidate();
		animationD.setAlpha(ua2);
		animationD.invalidate();
		animationL.setAlpha(ua2);
		animationL.invalidate();
		animationR.setAlpha(ua2);
		animationR.invalidate();
		inventory2--;
	}
}