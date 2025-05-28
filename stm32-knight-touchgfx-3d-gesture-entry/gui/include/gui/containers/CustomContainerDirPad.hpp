#ifndef CUSTOMCONTAINERDIRPAD_HPP
#define CUSTOMCONTAINERDIRPAD_HPP

#include <gui_generated/containers/CustomContainerDirPadBase.hpp>

class CustomContainerDirPad : public CustomContainerDirPadBase
{
public:
    CustomContainerDirPad();
    virtual ~CustomContainerDirPad() {}

    virtual void initialize();
	virtual void handleTickEvent();

	void setSelected(bool selected);
	bool getSelected();
protected:
	bool isSelected_;
};

#endif // CUSTOMCONTAINERDIRPAD_HPP
