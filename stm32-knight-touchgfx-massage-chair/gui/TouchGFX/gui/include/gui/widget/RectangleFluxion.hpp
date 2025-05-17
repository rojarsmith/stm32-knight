#ifndef RECTANGLE_FLUXION_HPP
#define RECTANGLE_FLUXION_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
//#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;

class RectangleFluxion : public Container
{
public:
	RectangleFluxion();
	virtual ~RectangleFluxion();

	virtual void handleTickEvent();

	void start(const int inventory, const int frequency, const int times);

protected:
	int inventory;
	int inventoryMax;
	int inventory2;
	int inventoryMax2;
	int frequency;
	int times;

	Line animationU;
	Line animationR;
	Line animationD;
	Line animationL;
	//PainterRGB565 colorPainter;
	PainterRGB888 colorPainter;

	//FrontendApplication& application() {
	//	return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
	//}
};

#endif /* RECTANGLE_FLUXION_HPP */
