#include <gui/main_screen/MainView.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

MainView::MainView() :
#ifndef SIMULATOR
    screenwidthreal(getScreenWidthReal()),
#else
    screenwidthreal(HAL::DISPLAY_WIDTH),	
#endif
	xAngle3D(0.0f),
	yAngle3D(0.0f),
	zAngle3D(0.0f),
	deltaXangle3D(0.032f),
	deltaYangle3D(0.029f),
	deltaZangle3D(0.027f),
	buttonClickedCallback(this, &MainView::buttonClicked)
{

}

void MainView::setupScreen()
{
	MainViewBase::setupScreen();

	imgBackground.setBitmap(Bitmap(BITMAP_MAINBG_ID));
	imgBackground.setXY(0, 0);
	add(imgBackground);

	imgDemotitle.setBitmap(Bitmap(BITMAP_DEMOTITLE_ID));
	imgDemotitle.setXY((screenwidthreal - imgDemotitle.getWidth()) / 2, ((HAL::DISPLAY_HEIGHT - imgDemotitle.getHeight()) / 2));
	add(imgDemotitle);

	btnWatch.setBitmap(Bitmap(BITMAP_BTN_WATCH_DISABLE_ID));
	btnBacklight.setBitmaps(Bitmap(BITMAP_BTN_BACKLIGHT_RELEASED_64X64_ID), Bitmap(BITMAP_BTN_BACKLIGHT_PRESSED_64X64_ID));
	btnMusic.setBitmaps(Bitmap(BITMAP_BTN_MUSIC_RELEASED_ID), Bitmap(BITMAP_BTN_MUSIC_PRESSED_ID));
	btnLighting.setBitmaps(Bitmap(BITMAP_BTN_LIGHTING_RELEASED_ID), Bitmap(BITMAP_BTN_LIGHTING_PRESSED_ID));
	btnFood.setBitmaps(Bitmap(BITMAP_BTN_FOOD_RELEASED_ID), Bitmap(BITMAP_BTN_FOOD_PRESSED_ID));
	btnFan.setBitmaps(Bitmap(BITMAP_BTN_FAN_RELEASED_ID), Bitmap(BITMAP_BTN_FAN_PRESSED_ID));
	btnWeather.setBitmap(Bitmap(BITMAP_BTN_WEATHER_DISABLE_ID));

	uint16_t icon_width = btnBacklight.getWidth();
	uint16_t icon_height = btnBacklight.getHeight();

	uint16_t icon_pitch_width_3 = (imgDemotitle.getWidth() - (icon_width * 2)) / 2;
	uint16_t icon_pitch1_height = btnBacklight.getHeight() / 4;

	btnWatch.setXY(imgDemotitle.getX() - icon_width - icon_pitch_width_3, (HAL::DISPLAY_HEIGHT - icon_height) / 2);
	btnWeather.setXY(imgDemotitle.getX(), btnWatch.getY() + icon_height + icon_pitch1_height);
	btnLighting.setXY(imgDemotitle.getX() + imgDemotitle.getWidth() + icon_pitch_width_3 * 2, (HAL::DISPLAY_HEIGHT - icon_height) / 2);

	uint16_t icon_pitch_width_2 = (btnLighting.getX() - btnWatch.getX() - (icon_width * 3)) / 3;

	btnFood.setXY(btnLighting.getX() - icon_width - icon_pitch_width_2 * 6, btnWatch.getY() + icon_height + icon_pitch1_height);
	btnMusic.setXY(btnLighting.getX() - icon_width - icon_pitch_width_2 * 6, btnWatch.getY() - icon_height);
	btnBacklight.setXY(btnWatch.getX() + icon_width + icon_pitch_width_2 * 4, btnWatch.getY() - icon_height);
	btnFan.setXY(btnWatch.getX() + icon_width + icon_pitch_width_2 * 4, btnWatch.getY() + icon_height + icon_pitch1_height);

	btnBacklight.setAction(buttonClickedCallback);
	btnMusic.setAction(buttonClickedCallback);
	btnLighting.setAction(buttonClickedCallback);
	btnFood.setAction(buttonClickedCallback);
	btnFan.setAction(buttonClickedCallback);

	add(btnBacklight);
	//add(btnWatch);
	add(btnMusic);
	add(btnLighting);
	add(btnFood);
	add(btnFan);
	//add(btnWeather);

	// Setup the texture mapper image that does 3D rotation
	textureMapperImage3D.setBitmap(Bitmap(BITMAP_EMBEDDED_ICON_ID));

	// Extra space for the image to rotate in
	int borderWidth = 15;
	int borderHeight = (HAL::DISPLAY_HEIGHT - Bitmap(BITMAP_EMBEDDED_ICON_ID).getHeight()) / 2 - 40;

	int imageWidth = textureMapperImage3D.getBitmap().getWidth();
	int imageHeight = textureMapperImage3D.getBitmap().getHeight();

	// Position the texture mapper image on the screen
	textureMapperImage3D.setXY(60, 40);

	// Set the width and height of the texture mapper image widget, including
	// space for the image to rotate (border)
	textureMapperImage3D.setWidth(imageWidth + borderWidth * 2);
	textureMapperImage3D.setHeight(imageHeight + borderHeight * 2);

	// Place the actual bitmap inside the texture mapper image.
	textureMapperImage3D.setBitmapPosition(borderWidth, borderHeight);

	// Set the camera distance which is the distance to the image in the z direction.
	// This has an effect of the perspective ratio of the image when it rotates
	textureMapperImage3D.setCameraDistance(300.0f);

	// Set the center of rotation of the texture mapper image (here it is the center of the image)
	textureMapperImage3D.setOrigo(textureMapperImage3D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage3D.getBitmapPositionY() + (imageHeight / 2), textureMapperImage3D.getCameraDistance());

	// Place the camera/eye of the viewer relative the image (here it is the center of the image)
	textureMapperImage3D.setCamera(textureMapperImage3D.getBitmapPositionX() + (imageWidth / 2), textureMapperImage3D.getBitmapPositionY() + (imageHeight / 2));

	// Set the rendering algorithm. Here the fast lower image quality NEAREST_NEIGHBOR algorithm is chosen.
	// Another option is the slower but high image quality Bilinear Interpolation algorithm.
	textureMapperImage3D.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);

	add(textureMapperImage3D);

	txtCopyRight.setTypedText(TypedText(T_COPYRIGHT));
	txtCopyRight.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	txtCopyRight.setHeight(100);
	txtCopyRight.setWidth(250);
	txtCopyRight.setXY(20, 10 + txtCopyRight.getTypedText().getFont()->getBaseline());
	add(txtCopyRight);
}

void MainView::tearDownScreen()
{
	MainViewBase::tearDownScreen();
}

void MainView::buttonClicked(const AbstractButton& source)
{
	if (&source == &btnMusic)
	{
		presenter->gotoMusicScreenFromMainScreen();
	}
	else if (&source == &btnLighting)
	{
		presenter->gotoLightingScreenFromMainScreen();
	}
	else if (&source == &btnFood)
	{
		presenter->gotoFoodScreenFromMainScreen();
	}
	else if (&source == &btnFan)
	{
		presenter->gotoFanScreenFromMainScreen();
	}
	//else if (&source == &btnBacklight)
	//{
	//	presenter->gotoBacklightScreenFromMainScreen();
	//}
}

void MainView::handleTickEvent()
{
	// Update angle values
	xAngle3D += deltaXangle3D;
	yAngle3D += deltaYangle3D;
	//zAngle3D += deltaZangle3D;


	// Update the images with the new angles
	// The image is automatically invalidated (the optimal minimal area).
	// If any of the set..() methods (e.g. setOrigo, setCamera, setRenderingAlgorithm...) are used
	// remember to manually invalidate the image afterwards (textureMapperImage2D.invalidate()).
	textureMapperImage3D.updateAngles(xAngle3D, yAngle3D, zAngle3D);
}
