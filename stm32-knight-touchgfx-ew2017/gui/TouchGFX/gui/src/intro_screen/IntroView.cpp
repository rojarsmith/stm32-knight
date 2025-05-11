#include <gui/intro_screen/IntroView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

IntroView::IntroView():
	fadeAnimationEndedCallback(this, &IntroView::embeddedLogoFadedHandler)
{

}

void IntroView::setupScreen()
{
    IntroViewBase::setupScreen();


	backgroundColor.setPosition(0, 0, getScreenWidth(), getScreenHeight());
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

	embeddedLogo.setXY(0, 150);
	embeddedLogo.setBitmap(Bitmap(BITMAP_EMBEDDED_LOGO_ID));
	embeddedLogo.setAlpha(0);

	add(backgroundColor);
	add(embeddedLogo);
}

void IntroView::tearDownScreen()
{
    IntroViewBase::tearDownScreen();
}

void IntroView::afterTransition()
{
	embeddedLogo.clearFadeAnimationEndedAction();
	embeddedLogo.setFadeAnimationEndedAction(fadeAnimationEndedCallback);
	embeddedLogo.startFadeAnimation(255, 180, EasingEquations::linearEaseIn);
	//embeddedLogo.startFadeAnimation(255, 18, EasingEquations::linearEaseIn);
}

void IntroView::embeddedLogoFadedHandler(const FadeAnimator<Image>& source)
{
#ifdef _MSC_VER
	for (uint32_t i = 0; i < 1000000000; i++) {}
	//for (uint32_t i = 0; i < 100000000; i++) { }
#elif __ICCARM__
	TickType_t xDelay = 3000 / portTICK_PERIOD_MS;
	vTaskDelay(xDelay);
#endif

	application().gotoMainScreenFromCurrentScreen();
}
