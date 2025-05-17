#ifndef LINE_FLUXION_HPP_
#define LINE_FLUXION_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/PixelDataWidget.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
//#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

using namespace touchgfx;

class LineFluxion : public Container
{
public:
	enum Direction
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	} direction;

	enum Status
	{
		PREPARE,
		ANIMAN_RUNNING_VALUE_IN,
		ANIMAN_IN,
		ANIMAN_IN_OV,
		VALUE_IN
	} constatus;

	LineFluxion();
	virtual ~LineFluxion();

	virtual void handleTickEvent();

	void setDirection(Direction d);
	void setValueSample(int value);
	void start(const int inventory, const int frequency, const int times);

protected:
	int tick;
	int tickMax;

	int drwagain;

	uint16_t sizeW;
	uint16_t sizeH;
	uint8_t alpha1;

	Container valueViewport;
	PixelDataWidget pixelDataWidget;
	MoveAnimator<TextAreaWithOneWildcard> value1Text;
	Unicode::UnicodeChar value1Buffer[5];

	int valueSample;
	int inventoryIn1;
	int inventoryIn1Max;
	int inventoryIn1DEach;
	int inventoryIn1Each;	
	int nX;
	int nY;
	int len1;
	void drawPixel();
	void drawLineIn();
	void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	uint8_t* pixelBuffer;	

	void updateValue(int value);
	
	
	Callback<LineFluxion, const MoveAnimator<TextAreaWithOneWildcard>&> textMoveAnimationEndedCallback;
	void textMoveAnimationEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);
};

#endif /* LINE_FLUXION_HPP_ */
