#ifndef CONTAINER_DESK_HPP
#define CONTAINER_DESK_HPP

#include <vector>
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <gui/widget/ContainerDesk.hpp>
#include <gui/widget/ContainerDeskPageBase.hpp>

using namespace touchgfx;
using namespace std;

class ContainerDesk : public ContainerDeskPageBase
{
public:	
	enum States
	{
		ANIMATE_LEFT,
		ANIMATION_STOP
	} currentState;

	ContainerDesk();
	virtual ~ContainerDesk();

	void addContainer(Container& page);

	void changePage(Container& page, int idx);
	States getCurrentState() { return currentState; }

	void setAnimationEndedAction(GenericCallback<const ContainerDesk& >& callback)
	{
		animationEndedCallback = &callback;
	}

	virtual void handleTickEvent();

protected:
	FrontendApplication& getApplication() {
		return *static_cast<FrontendApplication*>(Application::getInstance());
	}

private:
	const static uint8_t number_of_pages = 10;

	int16_t deltaX;
	int16_t animationCounter;

	Container* currentContainer;
	Container* tempContainer;
	Vector<Container*, number_of_pages> containers;

	void animateLeft();
	void adjustPages();

	GenericCallback<const ContainerDesk& >* animationEndedCallback;
};

#endif /* CONTAINER_DESK_HPP */
