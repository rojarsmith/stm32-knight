#include <gui/fan_screen/FanView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

FanView::FanView()
	:
#ifndef SIMULATOR
	screenwidthreal(getScreenWidthReal()),
#else
	screenwidthreal(HAL::DISPLAY_WIDTH),
#endif
	buttonClickedCallback(this, &FanView::buttonClicked),
	radioButtonSelectedCallback(this, &FanView::radioButtonSelectedHandler)
{

}

void FanView::setupScreen()
{
	FanViewBase::setupScreen();

	imgBackground.setBitmap(Bitmap(BITMAP_MAINBG_ID));
	imgBackground.setXY(0, 0);
	add(imgBackground);

	imgLogo.setBitmap(Bitmap(BITMAP_LOGO_LARGE_ID));
	//imgLogo.setXY(10, 10); // 480x272
	imgLogo.setXY(16, 16);
	add(imgLogo);

	btnHome.setBitmaps(Bitmap(BITMAP_BTN_HOME_RELEASED_ID), Bitmap(BITMAP_BTN_HOME_PRESSED_ID));

	uint16_t func_btn_width = btnHome.getWidth();
	uint16_t func_btn_height = btnHome.getHeight();

	btnHome.setXY(screenwidthreal - 16 - func_btn_width, HAL::DISPLAY_HEIGHT - func_btn_height); // 800x480
	/*btnHome.setXY(screenwidthreal - 10 - func_btn_width, HAL::DISPLAY_HEIGHT - func_btn_height);*/
	btnHome.setAction(buttonClickedCallback);
	add(btnHome);

	//=========================
	imgScalePanel.setBitmap(Bitmap(BITMAP_SCALEPANEL_ID));

	uint16_t ScalePanelStartx = (screenwidthreal - imgScalePanel.getWidth()) / 2;
	uint16_t ScalePanelStarty = imgLogo.getY() + imgLogo.getHeight();

	imgScalePanel.setXY(ScalePanelStartx, ScalePanelStarty);
	add(imgScalePanel);

	knobpPointer.setXY(imgScalePanel.getX(), imgScalePanel.getY());
	knobpPointer.setHeight(262);
	knobpPointer.setWidth(262);
	//knobpPointer.setHeight(158);
	//knobpPointer.setWidth(158);
	add(knobpPointer);

	imgScaleKnob.setBitmap(Bitmap(BITMAP_SCALEKNOB_ID));
	imgScaleKnob.setXY(imgScalePanel.getX(), imgScalePanel.getY());
	add(imgScaleKnob);

	temperatureValue = 22;
	knobpPointer.setValue(temperatureValue);

	//=========================
	temperatureTxt.setWildcard(temperatureTxtbuf);
	temperatureTxt.setTypedText(TypedText(T_TEMPERATURE));
	temperatureTxt.setColor(Color::getColorFromRGB(0x00, 0x1B, 0x91));
	add(temperatureTxt);
	temperatureTxt.setPosition((screenwidthreal - txtWidth) / 2, ScalePanelStarty + ((imgScalePanel.getHeight() - txtHeight) / 2), txtWidth, txtHeight);
	Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
	temperatureTxt.setVisible(false);
	temperatureTxt.invalidate();

	knobpPointer.setTouchable(false);

	fanoffTxt.setWildcard(fanoffTxtbuf);
	fanoffTxt.setTypedText(TypedText(T_FAN_OFF));
	fanoffTxt.setColor(Color::getColorFromRGB(0xF0, 0x00, 0x00));
	add(fanoffTxt);
	fanoffTxt.setPosition((screenwidthreal - txtWidth) / 2, ScalePanelStarty + ((imgScalePanel.getHeight() - txtHeight) / 2), txtWidth, txtHeight);
	Unicode::snprintf(fanoffTxtbuf, 50, "%d");
	fanoffTxt.setVisible(true);
	fanoffTxt.invalidate();

	//=========================
	btnCool.setBitmaps(Bitmap(BITMAP_BTN_COOL_RELEASED_ID), Bitmap(BITMAP_BTN_COOL_PRESSED_ID), Bitmap(BITMAP_BTN_COOL_PRESSED_ID), Bitmap(BITMAP_BTN_COOL_PRESSED_ID));
	btnHeat.setBitmap(Bitmap(BITMAP_BTN_HEAT_DISABLE_ID));
	btnAuto.setBitmap(Bitmap(BITMAP_BTN_AUTO_DISABLE_ID));
	btnOff.setBitmaps(Bitmap(BITMAP_BTN_OFF_RELEASED_ID), Bitmap(BITMAP_BTN_OFF_PRESSED_ID), Bitmap(BITMAP_BTN_OFF_PRESSED_ID), Bitmap(BITMAP_BTN_OFF_PRESSED_ID));

	uint16_t leftsideBtnWidth = btnHeat.getWidth();
	uint16_t leftsideBtnHeight = btnHeat.getHeight();
	uint16_t leftsidePitchWidth = (imgScalePanel.getX() - leftsideBtnWidth) / 2;
	uint16_t leftsidePitchHeight = (HAL::DISPLAY_HEIGHT - imgLogo.getY() - imgLogo.getHeight() - (leftsideBtnHeight * 4)) / 5;

	uint16_t leftsideStartX = leftsidePitchWidth;
	uint16_t leftsideStartY = imgLogo.getY() + imgLogo.getHeight() + leftsidePitchHeight;

	btnCool.setXY(leftsideStartX, leftsideStartY);
	btnHeat.setXY(leftsideStartX, leftsideStartY + leftsideBtnHeight + leftsidePitchHeight);
	btnAuto.setXY(leftsideStartX, leftsideStartY + (leftsideBtnHeight * 2) + (leftsidePitchHeight * 2));
	btnOff.setXY(leftsideStartX, leftsideStartY + (leftsideBtnHeight * 3) + (leftsidePitchHeight * 3));

	radioButtonGroup.add(btnCool);
	radioButtonGroup.add(btnOff);

	radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);

	radioButtonGroup.setSelected(btnOff);

	add(btnCool);
	add(btnHeat);
	add(btnAuto);
	add(btnOff);
	power_en = false;

	//=========================
	btnHigh.setBitmaps(Bitmap(BITMAP_BTN_HIGH_RELEASED_ID), Bitmap(BITMAP_BTN_HIGH_PRESSED_ID));
	btnMedium.setBitmaps(Bitmap(BITMAP_BTN_MEDIUM_RELEASED_ID), Bitmap(BITMAP_BTN_MEDIUM_PRESSED_ID));
	btnLow.setBitmaps(Bitmap(BITMAP_BTN_LOW_RELEASED_ID), Bitmap(BITMAP_BTN_LOW_PRESSED_ID));

	uint16_t rightsideBtnWidth = btnHigh.getWidth();
	//uint16_t rightsideBtnHeight = btnHigh.getHeight();
	uint16_t rightsidePitchWidth = (screenwidthreal - imgScalePanel.getX() - imgScalePanel.getWidth() - rightsideBtnWidth) / 2;
	//uint16_t rightsidePitchHeight = (btnHome.getY() - imgEDTlogo.getY() - imgEDTlogo.getHeight()  - (rightsideBtnHeight * 3)) / 4;

	uint16_t rightsideStartX = imgScalePanel.getX() + imgScalePanel.getWidth() + rightsidePitchWidth;
	//uint16_t rightsideStartY = imgEDTlogo.getY() + imgEDTlogo.getHeight() + rightsidePitchHeight;

	//btnHigh.setXY(rightsideStartX, rightsideStartY);
	//btnMedium.setXY(rightsideStartX, rightsideStartY + rightsideBtnHeight + rightsidePitchHeight);
	//btnLow.setXY(rightsideStartX, rightsideStartY + (rightsideBtnHeight * 2) + (rightsidePitchHeight * 2));
	btnHigh.setXY(rightsideStartX, btnCool.getY());
	btnMedium.setXY(rightsideStartX, btnHeat.getY());
	btnLow.setXY(rightsideStartX, btnAuto.getY());

	btnHigh.setAction(buttonClickedCallback);
	btnMedium.setAction(buttonClickedCallback);
	btnLow.setAction(buttonClickedCallback);

	add(btnHigh);
	add(btnMedium);
	add(btnLow);

	btnHigh.setAlpha(120);
	btnHigh.invalidate();
	btnMedium.setAlpha(120);
	btnMedium.invalidate();
	btnLow.setAlpha(120);
	btnLow.invalidate();

	btnHigh.setTouchable(false);
	btnMedium.setTouchable(false);
	btnLow.setTouchable(false);
}

void FanView::tearDownScreen()
{
	FanViewBase::tearDownScreen();
}

void FanView::handleTickEvent()
{
	if (power_en == true)
	{
		temperatureValue = knobpPointer.getValue();
		Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
		temperatureTxt.invalidate();
		presenter->setFan(temperatureValue);
	}
}

void FanView::buttonClicked(const AbstractButton& source)
{
	if (&source == &btnHigh)
	{
		temperatureValue = 17;
		knobpPointer.setValue(temperatureValue);
		Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
		temperatureTxt.invalidate();
		presenter->setFan(temperatureValue);
	}

	if (&source == &btnMedium)
	{
		temperatureValue = 22;
		knobpPointer.setValue(temperatureValue);
		Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
		temperatureTxt.invalidate();
		presenter->setFan(temperatureValue);
	}

	if (&source == &btnLow)
	{
		temperatureValue = 27;
		knobpPointer.setValue(temperatureValue);
		Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
		temperatureTxt.invalidate();
		presenter->setFan(temperatureValue);
	}

	if (&source == &btnHome)
	{
		presenter->setFan(0);
		presenter->gotoMainScreenFromFanScreen();
	}
}

void FanView::radioButtonSelectedHandler(const AbstractButton& radioButton)
{
	if (&btnCool == &radioButton)
	{
		power_en = true;
		fanoffTxt.setVisible(false);
		fanoffTxt.invalidate();
		temperatureValue = knobpPointer.getValue();
		Unicode::snprintf(temperatureTxtbuf, 50, "%d", temperatureValue);
		temperatureTxt.setVisible(true);
		temperatureTxt.invalidate();
		knobpPointer.setTouchable(true);
		btnHigh.setAlpha(255);
		btnHigh.invalidate();
		btnMedium.setAlpha(255);
		btnMedium.invalidate();
		btnLow.setAlpha(255);
		btnLow.invalidate();
		btnHigh.setTouchable(true);
		btnMedium.setTouchable(true);
		btnLow.setTouchable(true);
		presenter->setFan(temperatureValue);
	}

	if (&btnOff == &radioButton)
	{
		power_en = false;
		temperatureTxt.setVisible(false);
		temperatureTxt.invalidate();
		fanoffTxt.setVisible(true);
		fanoffTxt.invalidate();
		knobpPointer.setTouchable(false);
		btnHigh.setAlpha(120);
		btnHigh.invalidate();
		btnMedium.setAlpha(120);
		btnMedium.invalidate();
		btnLow.setAlpha(120);
		btnLow.invalidate();
		btnHigh.setTouchable(false);
		btnMedium.setTouchable(false);
		btnLow.setTouchable(false);
		presenter->setFan(0);
	}
}
