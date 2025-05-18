#ifndef BASE_VIEW_INTERFACE_HPP
#define BASE_VIEW_INTERFACE_HPP

#include <touchgfx/hal/Types.hpp>

using namespace touchgfx;

class BaseViewInterface
{
public:
    virtual ~BaseViewInterface() {}
    virtual void showProcessorLoad(bool visible) {}
    virtual void updateProcessorLoad(uint8_t mcuLoadInProcent) {}
};

#endif
