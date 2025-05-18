#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

// #include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/common/BaseView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/widget/TextureMapperAnimation.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class MainView : public MainViewBase, public BaseViewInterface // BaseView<MainPresenter>
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	virtual void afterTransition();
    virtual void handleTickEvent();

	void buttonClicked(const AbstractButton& source);
	
	void handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds);
	void handleTimeUpdated(int millis);

	void showProcessorLoad(bool visible) override;
    void updateProcessorLoad(uint8_t load) override;

protected:
private:	
	int runLoad;
	Box backgroundColor;
	FadeAnimator<Image> background;
	int backgroundAlpha;
	int backgroundColorValue;
	int backgroundColorValueDirection;
	TextureMapperAnimation ani1;
	int ani1I1;
	TextureMapperAnimation ani2;
	int ani2I1;	
	TextureMapperAnimation ani3;
	int ani3I1;
	static const uint16_t NUMBER_OF_RADIO_BUTTONS = 2;
	RadioButtonGroup<NUMBER_OF_RADIO_BUTTONS> radioButtonGroup;
	RadioButton radioButtons[NUMBER_OF_RADIO_BUTTONS];
	TextArea text100p;
	TextArea text0p;

	int milliSecond;

	Callback<MainView, const TextureMapperAnimation&> animationStoppedCallback;
	void animationStoppedCallbackHandler(const TextureMapperAnimation& source);

	Callback<MainView, const FadeAnimator<Image>& >imageFadeAnimationEndedCallback;
	void imageFadeAnimationEndedHandler(const FadeAnimator<Image>& source);

	Callback<MainView, const AbstractButton&> radioButtonSelectedCallback;
	void radioButtonSelectedHandler(const AbstractButton& radioButton);

	Callback<MainView, const AbstractButton&> radioButtonDeselectedCallback;
	void radioButtonDeselectedHandler(const AbstractButton& radioButton);

    Button backButton;
    TouchArea mcuLoadArea;
    McuLoadSlider mcuLoadSlider;

    Callback<MainView, const AbstractButton&> onBackButtonClicked;
    Callback<MainView, const AbstractButton&> onMcuLoadClicked;

	virtual void backButtonClickedHandler(const AbstractButton& button);
	virtual void mcuLoadClickedHandler(const AbstractButton& button);
    // void backButtonClickedHandler(const AbstractButton& button)
    // {
    //     MainView::presenter->backOptionSelected();
    // }

    // void mcuLoadClickedHandler(const AbstractButton& button)
    // {
    //     MainView::presenter->mcuLoadSelected();
    // }
};

#endif // MAINVIEW_HPP
