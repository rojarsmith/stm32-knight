#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

MainView::MainView()
	:	
	runLoad(100),
	backgroundAlpha(0),
	backgroundColorValue(0),
	backgroundColorValueDirection(1),
	ani1I1(15),
	ani2I1(15),
	ani3I1(15),
	milliSecond(0),
	animationStoppedCallback(this, &MainView::animationStoppedCallbackHandler),
	imageFadeAnimationEndedCallback(this, &MainView::imageFadeAnimationEndedHandler),
	radioButtonSelectedCallback(this, &MainView::radioButtonSelectedHandler),
	radioButtonDeselectedCallback(this, &MainView::radioButtonDeselectedHandler),
	onBackButtonClicked(this, &MainView::backButtonClickedHandler),
    onMcuLoadClicked(this, &MainView::mcuLoadClickedHandler)
{

}

void MainView::setupScreen()
{
    // MainViewBase::setupScreen();

    backgroundColor.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, backgroundColorValue, 0));
	add(backgroundColor);

	background.setBitmap(Bitmap(BITMAP_MATERIAL_WALLPAPER_GYP1_480X272_ID));
	background.setAlpha(backgroundAlpha);
	background.setFadeAnimationEndedAction(imageFadeAnimationEndedCallback);
	add(background);	

	ani1.setBitmaps(BITMAP_ANI1_01_ID, BITMAP_ANI1_15_ID);
	ani1.setXY(0, 0);
	ani1.setWidth(HAL::DISPLAY_WIDTH);
	ani1.setHeight(HAL::DISPLAY_HEIGHT);

	int ani1PX = HAL::DISPLAY_WIDTH / 2 - Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2;
	int ani1PY = HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2;
	ani1.setBitmapPosition(ani1PX, ani1PY);
	ani1.setCameraDistance(300.0f);

	float ani1OX = ani1.getBitmapPositionX() + ani1.getBitmap().getWidth() / 2;
	float ani1OY = ani1.getBitmapPositionY() + ani1.getBitmap().getHeight() / 2;
	float ani1OZ = ani1.getCameraDistance();
	ani1.setOrigo(ani1OX, ani1OY, ani1OZ);
	ani1.setCamera(ani1OX, ani1OY);
	ani1.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
	ani1.setAnimationStoppedCallback(animationStoppedCallback);
	ani1.setScale(2.0f);
	ani1.setAlpha(255);
	add(ani1);

	if (runLoad == 100)
	{
		ani1.startAnimation(ani1I1, 1, 255, 2.0);
	}

	ani2.setBitmaps(BITMAP_ANI1_01_ID, BITMAP_ANI1_15_ID);
	ani2.setXY(0, 0);
	ani2.setWidth(HAL::DISPLAY_WIDTH);
	ani2.setHeight(HAL::DISPLAY_HEIGHT);

	int ani2PX = HAL::DISPLAY_WIDTH / 2 - Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2 - 100;
	int ani2PY = HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2;
	ani2.setBitmapPosition(ani2PX, ani2PY);
	ani2.setCameraDistance(300.0f);

	float ani2OX = ani2.getBitmapPositionX() + ani2.getBitmap().getWidth() / 2;
	float ani2OY = ani2.getBitmapPositionY() + ani2.getBitmap().getHeight() / 2;
	float ani2OZ = ani2.getCameraDistance();
	ani2.setOrigo(ani2OX, ani2OY, ani2OZ);
	ani2.setCamera(ani2OX, ani2OY);
	ani2.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
	ani2.setAnimationStoppedCallback(animationStoppedCallback);
	ani2.setScale(2.0f);
	ani2.setAlpha(255);
	add(ani2);

	if (runLoad == 100)
	{
		ani2.startAnimation(ani2I1, 1, 255, 2.0);
	}

	ani3.setBitmaps(BITMAP_ANI1_01_ID, BITMAP_ANI1_15_ID);
	ani3.setXY(0, 0);
	ani3.setWidth(HAL::DISPLAY_WIDTH);
	ani3.setHeight(HAL::DISPLAY_HEIGHT);

	int ani3PX = HAL::DISPLAY_WIDTH / 2 - Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2 + 100;
	int ani3PY = HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2;
	ani3.setBitmapPosition(ani3PX, ani3PY);
	ani3.setCameraDistance(300.0f);

	float ani3OX = ani3.getBitmapPositionX() + ani3.getBitmap().getWidth() / 2;
	float ani3OY = ani3.getBitmapPositionY() + ani3.getBitmap().getHeight() / 2;
	float ani3OZ = ani3.getCameraDistance();
	ani3.setOrigo(ani3OX, ani3OY, ani3OZ);
	ani3.setCamera(ani3OX, ani3OY);
	ani3.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
	ani3.setAnimationStoppedCallback(animationStoppedCallback);
	ani3.setScale(2.0f);
	ani3.setAlpha(255);
	add(ani3);	

	//Setting area.
	int setting_area_x = 380;
	int setting_area_y = 160;

	text100p.setXY(setting_area_x, setting_area_y);
	text100p.setTypedText(TypedText(T_CONFIG_HIGH));
	text100p.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	add(text100p);

	text0p.setXY(setting_area_x, setting_area_y + 50);
	text0p.setTypedText(TypedText(T_CONFIG_LOW));
	text0p.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	add(text0p);

	for (int i = 0; i < NUMBER_OF_RADIO_BUTTONS; i++)
	{
		radioButtonGroup.add(radioButtons[i]);
		radioButtons[i].setBitmaps(Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_UNSELECTED_PRESSED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_ID), Bitmap(BITMAP_RADIO_BUTTON_SELECTED_PRESSED_ID));
		radioButtons[i].setXY(setting_area_x - 50,setting_area_y + 50 * i);
		add(radioButtons[i]);
	}
	radioButtonGroup.setSelected(radioButtons[0]);
	radioButtonGroup.setRadioButtonSelectedHandler(radioButtonSelectedCallback);
	radioButtonGroup.setRadioButtonDeselectedHandler(radioButtonDeselectedCallback);

	if (runLoad == 100)
	{
		ani3.startAnimation(ani3I1, 1, 255, 2.0);
		background.startFadeAnimation(255, 120, EasingEquations::linearEaseIn);
	}

    //backButton.setBitmaps(Bitmap(BITMAP_DEMO_BACK_BUTTON_ID), Bitmap(BITMAP_DEMO_BACK_BUTTON_PRESSED_ID));
    //backButton.setXY(0, 0);
    //backButton.setAction(onBackButtonClicked);
    mcuLoadArea.setPosition(0, HAL::DISPLAY_HEIGHT - 54, backButton.getWidth(), 54);
    mcuLoadArea.setAction(onMcuLoadClicked);
	// int a = HAL::DISPLAY_WIDTH;
	// int b = mcuLoadSlider.getWidth();
#if !defined(_MSC_VER) && !defined(SIMULATOR)
	mcuLoadSlider.setXY(HAL::DISPLAY_WIDTH - mcuLoadSlider.getWidth() - 34, 5);
#else
	mcuLoadSlider.setXY(HAL::DISPLAY_WIDTH - mcuLoadSlider.getWidth(), 5);
#endif
	mcuLoadSlider.show();
	// add(backButton);
}

void MainView::tearDownScreen()
{
    // MainViewBase::tearDownScreen();
}

void MainView::handleTimeUpdated(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
}

void MainView::handleTimeUpdated(int millis)
{
	milliSecond = millis;
}

void MainView::afterTransition()
{
    presenter->viewStartupDone();

    // These widget must be on top and are therefore added here
    add(mcuLoadArea);
    add(mcuLoadSlider);
}

void MainView::handleTickEvent()
{
	if (runLoad == 100) 
	{
		backgroundColorValue += backgroundColorValueDirection;
		backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, backgroundColorValue, 0));
		backgroundColor.invalidate();
		if (backgroundColorValue > 200)
		{
			backgroundColorValueDirection = -1;
		}
		else if (backgroundColorValue < 20)
		{
			backgroundColorValueDirection = 1;
		}
	}

//#ifndef SIMULATOR
//	uint16_t load = presenter->readLoad();
//	if (load > 95 || load < 5)
//	{
//		radioButtons[0].setTouchable(true);
//		radioButtons[1].setTouchable(true);
//		radioButtons[0].setAlpha(255);
//		radioButtons[1].setAlpha(255);
//		radioButtons[0].invalidate();
//		radioButtons[1].invalidate();
//	}
//	else
//	{
//		radioButtons[0].setTouchable(false);
//		radioButtons[1].setTouchable(false);
//		radioButtons[0].setAlpha(20);
//		radioButtons[0].invalidate();
//		radioButtons[1].setAlpha(20);
//		radioButtons[1].invalidate();
//	}
//#endif
}

void MainView::animationStoppedCallbackHandler(const TextureMapperAnimation& source)
{
	if (runLoad == 100)
	{
		if (&source == &ani1)
		{
			ani1.startAnimation(ani1I1, 1, 255, 2.0);
		}
		else if (&source == &ani2)
		{
			ani2.startAnimation(ani2I1, 1, 255, 2.0);
		}
		else if (&source == &ani3)
		{
			ani3.startAnimation(ani3I1, 1, 255, 2.0);
		}
	}	
}

void MainView::imageFadeAnimationEndedHandler(const FadeAnimator<Image>& source)
{
	if (runLoad == 100)
	{
		if (0 == background.getAlpha())
		{
			background.startFadeAnimation(255, 120, EasingEquations::linearEaseIn);
		}
		else if (255 == background.getAlpha())
		{
			background.startFadeAnimation(0, 120, EasingEquations::linearEaseIn);
		}
	}
}

void MainView::radioButtonSelectedHandler(const AbstractButton& radioButton)
{
	if (&radioButtons[0] == &radioButton)
	{
		runLoad = 100;
		ani1.startAnimation(ani1I1, 1, 255, 2.0);
		ani2.startAnimation(ani2I1, 1, 255, 2.0);
		ani3.startAnimation(ani3I1, 1, 255, 2.0);
		background.startFadeAnimation(255, 120, EasingEquations::linearEaseIn);

		presenter->setLoad(100);
	}
	else if (&radioButtons[1] == &radioButton)
	{
		runLoad = 0;

		presenter->setLoad(0);
	}
}

void MainView::radioButtonDeselectedHandler(const AbstractButton& radioButton)
{

}

void MainView::backButtonClickedHandler(const AbstractButton& button)
{
    presenter->backOptionSelected();
}

void MainView::mcuLoadClickedHandler(const AbstractButton& button)
{
    presenter->mcuLoadSelected();
}

// BaseViewInterface impl
void MainView::showProcessorLoad(bool visible)
{
    // Added to view here to ensure it is in front
    //if (!View<T>::container.contains(mcuLoadSlider))
    {
        //   View<T>::add(mcuLoadSlider);
    }
    (visible) ? mcuLoadSlider.show() : mcuLoadSlider.hide();
}

void MainView::updateProcessorLoad(uint8_t mcuLoadInProcent)
{
    mcuLoadSlider.setValue(mcuLoadInProcent);
}
