#ifndef CONTAINER_DESK_PAGE_2_HPP
#define CONTAINER_DESK_PAGE_2_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <gui/widget/SliderMod.hpp>
//#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/container/ModalDialog.hpp>
#include <gui/widget/ContainerDeskPageBase.hpp>

using namespace touchgfx;

class ContainerDeskPage2 : public ContainerDeskPageBase
{
public:
	ContainerDeskPage2();
	virtual ~ContainerDeskPage2();

	void setPopup(ModalDialog & dialog){ alartDialog = &dialog; }

	void setPopupAction(GenericCallback<const uint8_t>& callback)
	{
		buttonClickedThroughCallback = &callback;
	}

	void updateBrightnessValue(int brightness);

	void restAll();
protected:
	FrontendApplication& application() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}
private:
	static const int scrollable_area_width = 670;
	static const int scrollable_area_height = 1160;
	static const int scrollable_area_begin_x = 80;
	static const int scrollable_area_begin_y = 40;
	static const int scrollable_area_spacing_y = 20;
	static const int iconlebel1_height = 20;
	static const int configtitle1_height = 24;
	static const int group_revert_indent_1_x = -50;

	int setting_area_x;
	int setting_area_y;

	ModalDialog * alartDialog;

	Image rightBlockShadow;
	Container page;
	ScrollableContainer scrollablePage;
	Box backgroundColor;
	SliderMod t2;
	SliderMod as1;
	//Button buttonRelex;

	TextArea motor1;
	TextArea speed1;
	SliderMod speed_slider1;
	TextArea offset1;
	SliderMod offset_slider1;
	TextArea motor2;
	TextArea speed2;
	SliderMod speed_slider2;
	TextArea offset2;
	SliderMod offset_slider2;
	TextArea brightness;
	SliderMod brightness_slider;
	TextAreaWithOneWildcard brightnessValueText;
	TextAreaWithOneWildcard brightnessValueTextShadow;
	Unicode::UnicodeChar brightnessValueBuffer[5];
	int brightnessValue, brightnessValueCatch;

	static const uint16_t NUMBER_OF_RADIO_BUTTONS = 2;
	RadioButtonGroup<NUMBER_OF_RADIO_BUTTONS> radioButtonGroup;
	RadioButton radioButtons[NUMBER_OF_RADIO_BUTTONS];
	TextArea langEng;
	TextArea langJpn;

	Callback<ContainerDeskPage2, const SliderMod&, int> newValueCallback;
	void newValueCallbackHandler(const SliderMod& slider, int value);

	Callback<ContainerDeskPage2, const AbstractButton&> radioButtonSelectedCallback;
	void radioButtonSelectedHandler(const AbstractButton& radioButton);

	Callback<ContainerDeskPage2, const AbstractButton&> radioButtonDeselectedCallback;
	void radioButtonDeselectedHandler(const AbstractButton& radioButton);

	Callback<ContainerDeskPage2, const AbstractButton&> buttonClickedCallback;
	void buttonClickedHandler(const AbstractButton& source);
	GenericCallback<const uint8_t >* buttonClickedThroughCallback;
	
	ButtonWithLabel buttonReset;
	TextArea reset;
	TextArea version;

	//Spared
	TextArea motor3;
	TextArea speed3;
	TextArea offset3;
	TextArea volume;

	void setLanguage(LANGUAGES language);

	Callback<ContainerDeskPage2, const uint8_t>buttonClickedThroughCallback2;
	void buttonClickedThroughHandler2(const uint8_t source);
};

#endif /* CONTAINER_DESK_PAGE_2_HPP */
