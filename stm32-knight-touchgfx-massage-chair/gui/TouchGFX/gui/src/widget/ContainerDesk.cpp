#include <typeinfo>
#include <gui/widget/ContainerDesk.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <gui/widget/ContainerDeskPage0.hpp>
#include <gui/widget/ContainerDeskPage1.hpp>
#include <gui/widget/ContainerDeskPage2.hpp>

ContainerDesk::ContainerDesk()
	:
	currentState(ANIMATION_STOP),
	deltaX(0),
	animationCounter(0)
{
}

ContainerDesk::~ContainerDesk()
{
}

void ContainerDesk::addContainer(Container& container)
{
	containers.add(&container);

	int s = containers.size();
	
	if (s > number_of_pages)
	{
		return;
	}

	if (1 == s)
	{
		currentContainer = &container;
		tempContainer = &container;
		currentContainer->moveTo(0, 0);
		add(*currentContainer);
	}else if (2 == s)
	{
		tempContainer = &container;
		tempContainer->moveTo(getWidth(), 0);
	}
}

void ContainerDesk::changePage(Container& page, int idx)
{
	if (currentState != ANIMATION_STOP)
	{
		return;
	}
	else if (currentContainer == &page)
	{
		return;
	}

	if (idx == PAGE1)
	{
	// if (typeid(page) == typeid(ContainerDeskPage1)){
		((ContainerDeskPage1*)&page)->end();
	}

	currentContainer->setTouchable(false);
	(&page)->setTouchable(false);	
	setTouchable(false);
	
	tempContainer = &page;

	if (!contains(*currentContainer)) {
		add(*currentContainer);
	}

	insert(currentContainer, *tempContainer);

	tempContainer->setXY(getWidth(), 0);	

	currentState = ANIMATE_LEFT;	

	Application::getInstance()->registerTimerWidget(this);
}


void ContainerDesk::handleTickEvent()
{
	if (ANIMATE_LEFT == currentState)
	{
		animateLeft();
	}
}

void ContainerDesk::animateLeft()
{
	uint8_t duration = 10;

	if (animationCounter <= duration)
	{
		deltaX = EasingEquations::cubicEaseOut(animationCounter, getWidth(), -getWidth(), duration);

		adjustPages();
	}
	else
	{	
		animationCounter = 0;
		deltaX = 0;

		adjustPages();		

		currentContainer = tempContainer;
		remove(*tempContainer);
		tempContainer = 0;

		if (!contains(*currentContainer)) {
			add(*currentContainer);
		}

		Application::getInstance()->unregisterTimerWidget(this);
		setTouchable(true);

		currentState = ANIMATION_STOP;

		if (animationEndedCallback && animationEndedCallback->isValid())
		{
			animationEndedCallback->execute(*this);
		}
	}
	animationCounter++;
}

void ContainerDesk::adjustPages()
{
	tempContainer->moveTo(deltaX, getY());
}
