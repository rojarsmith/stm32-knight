#include <gui/containers/CustomContainerKnob.hpp>

CustomContainerKnob::CustomContainerKnob()
{
	isSelected_ = false;
}

void CustomContainerKnob::initialize()
{
    CustomContainerKnobBase::initialize();
}

void CustomContainerKnob::setSelected(bool selected)
{
	isSelected_ = selected;
}

bool CustomContainerKnob::getSelected()
{
	return isSelected_;
}