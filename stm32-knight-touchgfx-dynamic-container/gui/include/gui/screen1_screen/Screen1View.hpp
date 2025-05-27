#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>
class Message : public Container
{
public:
	enum Type { A, B, Unknown };

	Message() {
		//Container::Container();
	}
	virtual ~Message() {
		//Container::~Container(); 
	}
	virtual void open()
	{

	}

	virtual Type getType() const { return Unknown; }
protected:

};

class MessageA : public Message
{
public:
	MessageA() { 
		//Message::Message();
	}
	virtual ~MessageA() { 
		//Message::~Message();
	}
	virtual void open()
	{
		box_.setColor(Color::getColorFromRGB(0xaa, 0xa0, 0x00));
		box_.setPosition(10, 10, 200, 100);
		add(box_);
		box_.invalidate();
	}

	Type getType() const override { return A; }
protected:
	Box box_;
};

class MessageB : public Message
{
public:
	MessageB() { 
		//Message::Message();
    }
	virtual ~MessageB() {
		//Message::~Message(); 
	}
	virtual void open()
	{
		box_.setColor(Color::getColorFromRGB(0xaa, 0xa0, 0xa0));
		box_.setPosition(10, 110, 200, 100);
		add(box_);
		box_.invalidate();
	}

	Type getType() const override { return B; }
protected:
	Box box_;
};

class Screen1View : public Screen1ViewBase
{
public:
	Screen1View();
	virtual ~Screen1View() {}
	virtual void handleTickEvent();
	virtual void setupScreen();
	virtual void tearDownScreen();

protected:
	int tick_;
	Box box_;
	Message* msg_;
};

#endif // SCREEN1_VIEW_HPP
