#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
	:
	tick_(0)
{
	msg_ = new MessageA();
	msg_->setPosition(10, 10, 400, 400);
	add(*msg_);

	box_.setColor(Color::getColorFromRGB(0xaa, 0x00, 0x00));
	box_.setPosition(210, 10, 200, 100);
	add(box_);
}

void Screen1View::setupScreen()
{
	msg_->open();
}

void Screen1View::tearDownScreen()
{
	remove(*msg_);
}

void Screen1View::handleTickEvent()
{
	tick_++;

	if (tick_ % 60 == 0 && msg_->getType() == Message::A)
	{
		remove(*msg_);
		delete msg_;

		msg_ = new MessageB();
		msg_->setPosition(10, 10, 400, 400);
		add(*msg_);
		msg_->open();
		
	}
	else if(tick_ % 60 == 0 && msg_->getType() == Message::B)
	{
		remove(*msg_);
		delete msg_;

		msg_ = new MessageA();
		msg_->setPosition(10, 10, 400, 400);
		add(*msg_);
		msg_->open();
	}
}