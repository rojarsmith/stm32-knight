#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>

MainView::MainView()
	: 
	checkAccountCallback(this, &MainView::checkAccountCallbackHandler),
	tickCounter_(0),
	hours_(8),
	minutes_(16),
	seconds_(32)
{
	keyboard.setPosition(32, 44, 640, 392);
	keyboard.setCheckAccountAction(checkAccountCallback);
    add(keyboard);

	mask_.setPosition(32, 44, 640, 392);
	add(mask_);

	digitalClock_.setPosition(185, 440, 150, 30);
	digitalClock_.setTypedText(TypedText(T_DIGITALCLOCK));
	digitalClock_.setColor(Color::getColorFromRGB(0x7A, 0x7A, 0x7A));
	digitalClock_.setDisplayMode(DigitalClock::DISPLAY_24_HOUR);
	digitalClock_.displayLeadingZeroForHourIndicator(true);
	add(digitalClock_);

	digitalClock_.setTime24Hour(hours_, minutes_, seconds_);	
	
	buttonLock.setVisible(false);
}

void MainView::setupScreen()
{

}

void MainView::tearDownScreen()
{

}

void MainView::handleTickEvent()
{
	tickCounter_++;

	if (tickCounter_ % 60 == 0)
	{
		if (++seconds_ >= 60)
		{
			seconds_ = 0;
			if (++minutes_ >= 60)
			{
				minutes_ = 0;
				if (++hours_ >= 24)
				{
					hours_ = 0;
				}
			}
		}

		digitalClock_.setTime24Hour(hours_, minutes_, seconds_);		
	}
}

void MainView::clickButtonLock()
{
	buttonLock.setVisible(false);
	imageLock.setVisible(true);
	buttonLock.invalidate();
	imageLock.invalidate();
	mask_.startAgainAnimation();
}

void MainView::checkAccountCallbackHandler(bool valid)
{
	if (valid)
	{
		mask_.startValidAnimation();

		imageLock.setVisible(false);
		buttonLock.setVisible(true);
		imageLock.invalidate();
		buttonLock.invalidate();
	}
	else
	{		
		uint16_t record[18] = { 0x00 };
		keyboard.getBufferUser(record, 12);
		record[12] = 2025;
		record[13] = 1;
		record[14] = 2;
		record[15] = hours_;
		record[16] = minutes_;
		record[17] = seconds_;
		presenter->writeLoginRecord(record, 18);
		mask_.startInvalidAnimation();
	}
}