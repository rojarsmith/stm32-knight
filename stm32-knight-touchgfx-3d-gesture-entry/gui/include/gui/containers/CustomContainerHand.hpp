#ifndef CUSTOMCONTAINERHAND_HPP
#define CUSTOMCONTAINERHAND_HPP

#include <gui_generated/containers/CustomContainerHandBase.hpp>

class CustomContainerHand : public CustomContainerHandBase
{
public:
    CustomContainerHand();
    virtual ~CustomContainerHand() {}

    virtual void initialize();
protected:
};

#endif // CUSTOMCONTAINERHAND_HPP
