#ifndef CONTAINER_DESK_PAGE_0_HPP
#define CONTAINER_DESK_PAGE_0_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <gui/container/LineFluxion.hpp>
#include <gui/widget/ContainerDeskPageBase.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


#define CANVAS_BUFFER_SIZE_DESK 40000

using namespace touchgfx;

class ContainerDeskPage0 : public ContainerDeskPageBase
{
public:
	ContainerDeskPage0();
	virtual ~ContainerDeskPage0();

     DeskPageType getPageType() const override { return PAGE0; }
protected:

private:
	Box backgroundColor;
	Image man;
	LineFluxion lineFluxion1;
	LineFluxion lineFluxion2;

#if !defined(_MSC_VER) && !defined(SIMULATOR)
    static uint8_t canvasBuffer[CANVAS_BUFFER_SIZE_DESK];
#endif

    TextArea txtCopyRight;
};

#endif /* CONTAINER_DESK_PAGE_0_HPP */
