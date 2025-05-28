#include <gui/containers/CustomContainerDirPad.hpp>

CustomContainerDirPad::CustomContainerDirPad()
{
	Application::getInstance()->registerTimerWidget(this);	
}

void CustomContainerDirPad::initialize()
{
    CustomContainerDirPadBase::initialize();
}

void CustomContainerDirPad::handleTickEvent()
{

}

void CustomContainerDirPad::setSelected(bool selected)
{
	isSelected_ = selected;
}

bool CustomContainerDirPad::getSelected()
{
	return isSelected_;
}
