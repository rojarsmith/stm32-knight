#include <BitmapDatabase.hpp>
#include <gui/widget/ContainerDeskPage2.hpp>
#include <touchgfx/Color.hpp>

ContainerDeskPage2::ContainerDeskPage2()
	:
	newValueCallback(this, &ContainerDeskPage2::newValueCallbackHandler),
	radioButtonSelectedCallback(this, &ContainerDeskPage2::radioButtonSelectedHandler),
	radioButtonDeselectedCallback(this, &ContainerDeskPage2::radioButtonDeselectedHandler),
	buttonClickedCallback(this, &ContainerDeskPage2::buttonClickedHandler)
	//buttonClickedThroughCallback2(this, &ContainerDeskPage2::buttonClickedThroughHandler2)
{
	backgroundColor.setPosition(0, 0, scrollable_area_width, 480);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 74, 127));
	//int x = getWidth();
	//int y = getHeight();
	add(backgroundColor);

	page.setPosition(0, 0, scrollable_area_width, scrollable_area_height);

	scrollablePage.enableHorizontalScroll(false);
	scrollablePage.enableVerticalScroll(true);
	scrollablePage.setScrollbarsVisible(true);
	scrollablePage.setScrollThreshold(30);
	scrollablePage.setScrollbarsColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	scrollablePage.setScrollbarWidth(3);
	scrollablePage.setScrollbarsAlpha(100);
	scrollablePage.setScrollbarPadding(10);
	scrollablePage.setPosition(0, 0, scrollable_area_width, 480);

	//Setting area.
	setting_area_x = scrollable_area_begin_x;
	setting_area_y = scrollable_area_begin_y;
	
	motor1.setXY(setting_area_x + group_revert_indent_1_x, setting_area_y);
	motor1.setColor(Color::getColorFromRGB(255, 178, 127));
	motor1.setTypedText(TypedText(T_TITLE_MOTOR_1));
	page.add(motor1);

	setting_area_y += configtitle1_height + scrollable_area_spacing_y;

	speed1.setXY(setting_area_x, setting_area_y);
	speed1.setColor(Color::getColorFromRGB(255, 255, 255));
	speed1.setTypedText(TypedText(T_CONFIG_SPEED));
	page.add(speed1);

	setting_area_y += configtitle1_height + scrollable_area_spacing_y;
	
	speed_slider1.setBitmaps(Bitmap(BITMAP_CONFIGBAR_S2_400X6_ID), Bitmap(BITMAP_CONFIGBAR_S1_400X6_ID), Bitmap(BITMAP_CONFIGBAR_CW_ID));
	speed_slider1.setXY(setting_area_x, setting_area_y);
	//speed_slider1.setNewValueCallback(newValueCallback);
	speed_slider1.setupHorizontalSlider(32, 29, 0, 0, 400);
	speed_slider1.setValueRange(0, 100);
	speed_slider1.setTouchable(true);
	speed_slider1.setXY(setting_area_x, setting_area_y);
	speed_slider1.setVisible(true);
	speed_slider1.setTouchable(true);
	page.add(speed_slider1);
	
	setting_area_y += speed_slider1.getHeight() + scrollable_area_spacing_y;

	offset1.setXY(setting_area_x, setting_area_y);
	offset1.setColor(Color::getColorFromRGB(255, 255, 255));
	offset1.setTypedText(TypedText(T_CONFIG_OFFSET));
	page.add(offset1);

	setting_area_y += iconlebel1_height + scrollable_area_spacing_y;

	offset_slider1.setBitmaps(Bitmap(BITMAP_CONFIGBAR_S2_400X6_ID), Bitmap(BITMAP_CONFIGBAR_S1_400X6_ID), Bitmap(BITMAP_CONFIGBAR_CW_ID));
	offset_slider1.setXY(setting_area_x, setting_area_y);
	offset_slider1.setNewValueCallback(newValueCallback);
	offset_slider1.setupHorizontalSlider(32, 29, 0, 0, 400);
	offset_slider1.setValueRange(0, 100);
	offset_slider1.setTouchable(true);
	offset_slider1.setXY(setting_area_x, setting_area_y);
	offset_slider1.setVisible(true);
	offset_slider1.setTouchable(true);
	page.add(offset_slider1);

	//Motor2
	setting_area_y += offset_slider1.getHeight() + scrollable_area_spacing_y;

	motor2.setXY(setting_area_x + group_revert_indent_1_x, setting_area_y);
	motor2.setColor(Color::getColorFromRGB(255, 178, 127));
	motor2.setTypedText(TypedText(T_TITLE_MOTOR_2));
	page.add(motor2);

	setting_area_y += configtitle1_height + scrollable_area_spacing_y;

	speed2.setXY(setting_area_x, setting_area_y);
	speed2.setColor(Color::getColorFromRGB(255, 255, 255));
	speed2.setTypedText(TypedText(T_CONFIG_SPEED));
	page.add(speed2);

	setting_area_y += iconlebel1_height + scrollable_area_spacing_y;

	speed_slider2.setBitmaps(Bitmap(BITMAP_CONFIGBAR_S2_400X6_ID), Bitmap(BITMAP_CONFIGBAR_S1_400X6_ID), Bitmap(BITMAP_CONFIGBAR_CW_ID));
	speed_slider2.setXY(setting_area_x, setting_area_y);
	speed_slider2.setNewValueCallback(newValueCallback);
	speed_slider2.setupHorizontalSlider(32, 29, 0, 0, 400);
	speed_slider2.setValueRange(0, 100);
	speed_slider2.setTouchable(true);
	speed_slider2.setXY(setting_area_x, setting_area_y);
	speed_slider2.setVisible(true);
	speed_slider2.setTouchable(true);
	page.add(speed_slider2);

	setting_area_y += speed_slider2.getHeight() + scrollable_area_spacing_y;

	offset2.setXY(setting_area_x, setting_area_y);
	offset2.setColor(Color::getColorFromRGB(255, 255, 255));
	offset2.setTypedText(TypedText(T_CONFIG_OFFSET));
	page.add(offset2);

	setting_area_y += iconlebel1_height + scrollable_area_spacing_y;

	offset_slider2.setBitmaps(Bitmap(BITMAP_CONFIGBAR_S2_400X6_ID), Bitmap(BITMAP_CONFIGBAR_S1_400X6_ID), Bitmap(BITMAP_CONFIGBAR_CW_ID));
	offset_slider2.setXY(setting_area_x, setting_area_y);
	offset_slider2.setNewValueCallback(newValueCallback);
	offset_slider2.setupHorizontalSlider(32, 29, 0, 0, 400);
	offset_slider2.setValueRange(0, 100);
	offset_slider2.setTouchable(true);
	offset_slider2.setXY(setting_area_x, setting_area_y);
	offset_slider2.setVisible(true);
	offset_slider2.setTouchable(true);
	page.add(offset_slider2);

	//Brightness
	setting_area_y += offset_slider2.getHeight() + scrollable_area_spacing_y * 3;

	brightness.setXY(setting_area_x, setting_area_y);
	brightness.setColor(Color::getColorFromRGB(255, 255, 255));
	brightness.setTypedText(TypedText(T_CONFIG_BRIGHTNESS));
	page.add(brightness);

	brightnessValueText.setPosition(setting_area_x + 380, setting_area_y - 5, 110, 34);
	brightnessValueText.setWildcard(brightnessValueBuffer);
	brightnessValueText.setTypedText(TypedText(T_CONFIG_BRIGHTNESS_VALUE));
	brightnessValueText.setColor(Color::getColorFromRGB(0, 176, 80));
	brightnessValueTextShadow.setPosition(setting_area_x + 380 + 2, setting_area_y - 5 + 2, 110, 34);
	brightnessValueTextShadow.setWildcard(brightnessValueBuffer);
	brightnessValueTextShadow.setTypedText(TypedText(T_CONFIG_BRIGHTNESS_VALUE));
	brightnessValueTextShadow.setColor(Color::getColorFromRGB(0, 0, 0));
	page.add(brightnessValueTextShadow);
	page.add(brightnessValueText);

	setting_area_y += iconlebel1_height + scrollable_area_spacing_y;

	brightness_slider.setBitmaps(Bitmap(BITMAP_CONFIGBAR_S2_400X6_ID), Bitmap(BITMAP_CONFIGBAR_S1_400X6_ID), Bitmap(BITMAP_CONFIGBAR_CW_ID));
	brightness_slider.setXY(setting_area_x, setting_area_y);
	brightness_slider.setNewValueCallback(newValueCallback);
	brightness_slider.setupHorizontalSlider(32, 29, 0, 0, 400);
	brightness_slider.setValueRange(0, 100);
	brightness_slider.setTouchable(true);
	brightness_slider.setXY(setting_area_x, setting_area_y);
	brightness_slider.setVisible(true);
	brightness_slider.setTouchable(true);
	page.add(brightness_slider);

	//Jap
	setting_area_y += brightness_slider.getHeight() + scrollable_area_spacing_y * 3;

	langEng.setXY(setting_area_x + 55, setting_area_y);
	langEng.setTypedText(TypedText(T_CONFIG_ENGLISH));
	langEng.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	page.add(langEng);

	langJpn.setXY(setting_area_x + 270, setting_area_y);
	langJpn.setTypedText(TypedText(T_CONFIG_JAPAN));
	langJpn.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	page.add(langJpn);

	for (int i = 0; i < NUMBER_OF_RADIO_BUTTONS; i++)
	{
		radioButtonGroup.add(radioButtons[i]);
		radioButtons[i].setBitmaps(Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_PRESSED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_PRESSED_ID));
		radioButtons[i].setXY(setting_area_x + 220 * i, setting_area_y);
		page.add(radioButtons[i]);
	}
	radioButtonGroup.setSelected(radioButtons[0]);
	radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);
	radioButtonGroup.setRadioButtonDeselectedHandler(radioButtonDeselectedCallback);

	setting_area_y += brightness_slider.getHeight() + scrollable_area_spacing_y * 3;

	buttonReset.setBitmaps(Bitmap(BITMAP_RESETFACTORY_ID), Bitmap(BITMAP_RESETFACTORY_M_ID));
	buttonReset.setXY(setting_area_x, setting_area_y);
	buttonReset.setAction(buttonClickedCallback);
	buttonReset.setVisible(true);
	buttonReset.setLabelText(TypedText(T_CONFIG_RESET_TO_FACTORY));
	buttonReset.setLabelColor(Color::getColorFromRGB(192, 192, 192));
	buttonReset.setLabelColorPressed(Color::getColorFromRGB(255, 255, 255));
	page.add(buttonReset);
	

	setting_area_y += buttonReset.getHeight() + scrollable_area_spacing_y * 3;

	version.setXY(setting_area_x, setting_area_y);
	version.setColor(Color::getColorFromRGB(255, 255, 255));
	version.setTypedText(TypedText(T_INFO_VERSION));
	page.add(version);

	scrollablePage.add(page);
	add(scrollablePage);

	rightBlockShadow.setBitmap(Bitmap(BITMAP_SHADOW_21_10X480_ID));
	rightBlockShadow.setXY(670 - Bitmap(BITMAP_SHADOW_21_10X480_ID).getWidth(), 0);
	rightBlockShadow.setAlpha(150);
	add(rightBlockShadow);
}

ContainerDeskPage2::~ContainerDeskPage2()
{
}

void ContainerDeskPage2::restAll()
{
	speed_slider1.setValue(100);
	offset_slider1.setValue(100);
	speed_slider2.setValue(100);
	offset_slider2.setValue(100);
	brightness_slider.setValue(100);
}

void ContainerDeskPage2::buttonClickedHandler(const AbstractButton& source)
{
	if (buttonClickedThroughCallback && buttonClickedThroughCallback->isValid())
	{
		buttonClickedThroughCallback->execute(0);
	}
}

void ContainerDeskPage2::newValueCallbackHandler(const SliderMod& slider, int value)
{
	if (&slider == &brightness_slider)
	{
		brightnessValue = value;

		if (brightnessValue == brightnessValueCatch) {
			return;
		}

		brightnessValueCatch = value;
		updateBrightnessValue(value);
	}
}

void ContainerDeskPage2::updateBrightnessValue(int brightness)
{
	Unicode::snprintf(brightnessValueBuffer, 5, "%d", brightness);
	brightnessValueText.invalidate();
	brightnessValueTextShadow.invalidate();
}

void ContainerDeskPage2::radioButtonSelectedHandler(const AbstractButton& radioButton)
{
	if (&radioButtons[0] == &radioButton)
	{
		setLanguage(GB);
	}else if (&radioButtons[1] == &radioButton)
	{
		setLanguage(JPN);
	}
}

void ContainerDeskPage2::radioButtonDeselectedHandler(const AbstractButton& radioButton)
{
	if (&radioButtons[0] == &radioButton)
	{
	}
	else if (&radioButtons[1] == &radioButton)
	{
	}
}

void ContainerDeskPage2::setLanguage(LANGUAGES language)
{
	Texts::setLanguage(language);

	brightness.invalidate();
	buttonReset.invalidate();

	motor1.setWidth(200);
	motor1.invalidate();
	motor2.setWidth(200);
	motor2.invalidate();

	application().drawCachedAreas();
}
