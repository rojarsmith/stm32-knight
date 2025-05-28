#ifndef CUSTOMCONTAINERKNOB_HPP
#define CUSTOMCONTAINERKNOB_HPP

#include <gui_generated/containers/CustomContainerKnobBase.hpp>

class CustomContainerKnob : public CustomContainerKnobBase
{
public:
    CustomContainerKnob();
    virtual ~CustomContainerKnob() {}

    virtual void initialize();

	void setSelected(bool selected);
	bool getSelected();
protected:
	bool isSelected_;
};

#endif // CUSTOMCONTAINERKNOB_HPP
