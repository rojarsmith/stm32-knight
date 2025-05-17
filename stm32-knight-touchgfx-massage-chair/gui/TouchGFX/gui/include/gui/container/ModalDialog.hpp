#ifndef MODAL_DIALOG_HPP_
#define MODAL_DIALOG_HPP_

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/PixelDataWidget.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <gui/common/FrontendApplication.hpp>

using namespace touchgfx;

class ModalDialog : public Container
{
public:
	//enum Direction
	//{
	//	TOP_LEFT,
	//	TOP_RIGHT,
	//	BOTTOM_LEFT,
	//	BOTTOM_RIGHT
	//} direction;

	//enum Status
	//{
	//	PREPARE,
	//	ANIMAN_RUNNING_VALUE_IN,
	//	ANIMAN_IN,
	//	ANIMAN_IN_OV,
	//	VALUE_IN
	//} constatus;

	ModalDialog();
	virtual ~ModalDialog();

	virtual void handleTickEvent();
	virtual void invalidate() const;	

	void setResizeText();

	//void setDirection(Direction d);
	//void setValueSample(int value);
	//void start(const int inventory, const int frequency, const int times);
	void setClickedAction(GenericCallback<const uint8_t>& callback)
	{
		buttonClickedThroughCallback = &callback;
	}

protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}

	Box backgroundColor;

	TextArea dialogMessage;

	Button buttonOK;
	Button buttonCancel;
	//int tick;
	//int tickMax;

	//int drwagain;

	//uint16_t sizeW;
	//uint16_t sizeH;
	//uint8_t alpha1;

	//Container valueViewport;
	//PixelDataWidget pixelDataWidget;
	//MoveAnimator<TextAreaWithOneWildcard> value1Text;
	//Unicode::UnicodeChar value1Buffer[5];

	//int valueSample;
	//int inventoryIn1;
	//int inventoryIn1Max;
	//int inventoryIn1DEach;
	//int inventoryIn1Each;
	//int nX;
	//int nY;
	//int len1;
	//void drawPixel();
	//void drawLineIn();
	//void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	//uint8_t* pixelBuffer;

	//void updateValue(int value);


	//Callback<ModalDialog, const MoveAnimator<TextAreaWithOneWildcard>&> textMoveAnimationEndedCallback;
	//void textMoveAnimationEndedHandler(const MoveAnimator<TextAreaWithOneWildcard>& source);
private:
	Callback<ModalDialog, const AbstractButton&> buttonClickedCallback;
	void buttonClickedHandler(const AbstractButton& source);
	GenericCallback<const uint8_t >* buttonClickedThroughCallback;
};

#endif /* MODAL_DIALOG_HPP_ */
