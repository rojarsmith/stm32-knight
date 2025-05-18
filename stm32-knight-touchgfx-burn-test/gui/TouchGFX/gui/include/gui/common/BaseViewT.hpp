#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#include <mvp/View.hpp>
#include <gui/common/BaseViewInterface.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TouchArea.hpp>
#include <BitmapDatabase.hpp>
#include <gui/widget/McuLoadSlider.hpp>
#include <gui_generated/main_screen/MainViewBase.hpp>

using namespace touchgfx;

template <class T>
class BaseView : public MainViewBase, View<T>, public BaseViewInterface
{
public:
    BaseView() :
        onBackButtonClicked(this, &BaseView::backButtonClickedHandler),
        onMcuLoadClicked(this, &BaseView::mcuLoadClickedHandler)
    {
        //backButton.setBitmaps(Bitmap(BITMAP_DEMO_BACK_BUTTON_ID), Bitmap(BITMAP_DEMO_BACK_BUTTON_PRESSED_ID));
        //backButton.setXY(0, 0);
        //backButton.setAction(onBackButtonClicked);

        mcuLoadArea.setPosition(0, HAL::DISPLAY_HEIGHT - 54, backButton.getWidth(), 54);
        mcuLoadArea.setAction(onMcuLoadClicked);

        mcuLoadSlider.setXY(HAL::DISPLAY_WIDTH - mcuLoadSlider.getWidth(), 5);

        View<T>::add(backButton);
    }

    virtual void afterTransition()
    {
        View<T>::presenter->viewStartupDone();

        // These widget must be on top and are therefore added here
        View<T>::add(mcuLoadArea);
        View<T>::add(mcuLoadSlider);
    }

protected:
    Button backButton;
    TouchArea mcuLoadArea;
    McuLoadSlider mcuLoadSlider;

    Callback<BaseView, const AbstractButton&> onBackButtonClicked;
    Callback<BaseView, const AbstractButton&> onMcuLoadClicked;

    void backButtonClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->backOptionSelected();
    }

    void mcuLoadClickedHandler(const AbstractButton& button)
    {
        View<T>::presenter->mcuLoadSelected();
    }

    // BaseViewInterface impl
    virtual void showProcessorLoad(bool visible)
    {
        // Added to view here to ensure it is in front
        //if (!View<T>::container.contains(mcuLoadSlider))
        {
            //   View<T>::add(mcuLoadSlider);
        }
        (visible) ? mcuLoadSlider.show() : mcuLoadSlider.hide();
    }

    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent)
    {
        mcuLoadSlider.setValue(mcuLoadInProcent);
    }
};

#endif
