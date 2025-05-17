#ifndef CONTAINER_DESK_PAGE_BASE_HPP
#define CONTAINER_DESK_PAGE_BASE_HPP

#include <touchgfx/containers/Container.hpp>

enum DeskPageType
{
    PAGE0,
    PAGE1,
    PAGE2,
    PAGE_UNKNOWN
};

using namespace touchgfx;

class ContainerDeskPageBase : public Container
{
public:
    virtual DeskPageType getPageType() const { return PAGE_UNKNOWN; }
};

#endif /* CONTAINER_DESK_PAGE_BASE_HPP */