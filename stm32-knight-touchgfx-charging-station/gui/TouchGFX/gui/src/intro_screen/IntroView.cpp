#include <gui/intro_screen/IntroView.hpp>
#include <gui/common/BMPFileLoader.hpp>

#ifdef SIMULATOR
#include <fstream>
#endif
#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

IntroView::IntroView()
	:
	event_trigger_callback_(this, &IntroView::eventTriggerHandler)
{

}

void IntroView::setupScreen()
{
	BaseView::setupScreen();

	//background_.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	background_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	background_.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
	add(background_);

#ifdef SIMULATOR
#ifdef __GNUC__ 
std::string title_path_temp = "assets/intro/Title.bmp";
std::string title_path = "build/bin/Title.bmp";
#else
std::string title_path_temp = "../../assets/intro/Title.bmp";
std::string title_path = "../../build/Debug/bin/Title.bmp";
#endif
	std::ifstream ifs(title_path, std::ios::binary);
	if (!ifs.is_open())
	{
		std::ifstream src(title_path_temp, std::ios::in | std::ios::binary);

		std::ofstream dst(title_path, std::ios::out | std::ios::binary);
		dst << src.rdbuf();
		src.close();
		dst.close();
	}
	ifs.close();

	FILE* f;
	errno_t err;
	err = fopen_s(&f, title_path.c_str(), "rb");
	uint16_t width, height;
	BMPFileLoader::getBMP24Dimensions(f, width, height);
	id_ = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB888);
	//id_ = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);
	BMPFileLoader::readBMP24File(Bitmap(id_), f);
	image_.setBitmap(Bitmap(id_));
	(void)err;
#else       
	//
	//	Upgrade From dynamic address.
	//  uint32_t *f = (uint32_t*)(0x90100000);
	//  uint16_t width=768, height=1024;
	//   
	//  BMPFileLoader::getBMP24Dimensions(f, width, height);
	//	
	//	id_ = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB565);	
	//	BMPFileLoader::readBMP24File(Bitmap(id_), f);	
	//	image_.setBitmap(Bitmap(id_));    
#endif

// #ifdef __ICCARM__ || __GNUC__
#ifndef SIMULATOR
	//For final version. Using touchgfx image converter static address.
	image_.setBitmap(Bitmap(BITMAP_WELCOME_BACKGROUND_ID));
#endif

	image_.setXY(0, (getFixedDisplayHeight() - image_.getHeight()) / 2);
	add(image_);

	BaseView::afterSetupScreen();

	completedCommand();
	setMask(MaskList::FULL_MASK, true);

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addCountDownEvent(
		EventList::EVENT_SEND_COMMAND,
		ms_->ux_delay_0100_to_0200 + 1);
}

void IntroView::tearDownScreen()
{
    IntroViewBase::tearDownScreen();
}

/**
 * Scale the bitmap to full screen while maintaining aspect ratio
 * Show it centered.
 */
void IntroView::showBitmap(BitmapId id)
{
    Bitmap bitmap(id);
    //invalidate bitmap before changing to ensure background is painted
    image2_.invalidate();
    image2_.setBitmap(Bitmap(id));

    const float scale_horiz = 480.0f / bitmap.getWidth();
    const float scale_vert  = 272.0f / bitmap.getHeight();
    const float scale = MIN(scale_horiz, scale_vert);

    image2_.setWidth(static_cast<uint16_t>(bitmap.getWidth() * scale));
    image2_.setHeight(static_cast<uint16_t>(bitmap.getHeight() * scale));

    //center horizontally
    image2_.setXY((480 - image2_.getWidth()) / 2, (272 - image2_.getHeight()) / 2);

    //make visible (image is invisible first time)
    image2_.setVisible(true);
    //invalidate bitmap to ensure new picture is drawn
    image2_.invalidate();
}

void IntroView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case EventList::EVENT_1TICK_LOOP:
		event1TickLoop();
		break;
	case EventList::EVENT_SEND_COMMAND:
		eventSendCommand();
		break;
	case EventList::EVENT_CHANGE_SCREEN:
		eventChangeScreen();
		break;
	case 43:
		event43();
		break;
	case 49:
		event49();
		break;
	}
}

void IntroView::event1TickLoop()
{
}

void IntroView::eventSendCommand()
{
	em_.removeAll();

	sendCommand(ScreenNumber::SCREEN_HOME);

	//em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN, cc_.After1Tick);
	//em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN, cc_.After60Tick);
	em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN, cc_.After120Tick);
}

void IntroView::eventChangeScreen()
{
	em_.removeAll();

	changeScreen(ScreenNumber::SCREEN_HOME);
}
