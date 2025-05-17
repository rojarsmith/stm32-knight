#include <BitmapDatabase.hpp>
#include <gui/widget/ContainerDeskPage0.hpp>
#include <touchgfx/Color.hpp>

// uint8_t ContainerDeskPage0::canvasBuffer[CANVAS_BUFFER_SIZE_DESK];
__attribute__((section(".RAM_D1"))) __attribute__((aligned(4)))
uint8_t ContainerDeskPage0::canvasBuffer[CANVAS_BUFFER_SIZE_DESK];

ContainerDeskPage0::ContainerDeskPage0()
{
	// Not work
	// CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE_DESK);
	// SCB_CleanDCache_by_Addr((uint32_t*)pixelBuffer, 200 * 50 * 4);
	// Manual set buffer for LineFluxion. MUST!!!!
    HAL::getInstance()->setAnimationStorage((void*)canvasBuffer); 

	backgroundColor.setPosition(0, 0, 700, 480);
	backgroundColor.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

	add(backgroundColor);

	man.setBitmap(Bitmap(BITMAP_ANI1_01_ID));
	int xt = (HAL::DISPLAY_WIDTH - 130) / 2 - Bitmap(BITMAP_ANI1_01_ID).getWidth() / 2;
	int yt = HAL::DISPLAY_HEIGHT / 2 - Bitmap(BITMAP_ANI1_01_ID).getHeight() / 2;
	man.setXY(xt, yt);

	add(man);

	lineFluxion1.setWidth(200);
	lineFluxion1.setHeight(100);
	lineFluxion1.setXY(50, 100);
	add(lineFluxion1);

	lineFluxion1.setValueSample(1000);
	lineFluxion1.setXY(80, 200);
	lineFluxion1.setDirection(LineFluxion::Direction::TOP_LEFT);
	lineFluxion1.start(0, 0, 0);


	lineFluxion2.setWidth(200);
	lineFluxion2.setHeight(100);
	lineFluxion2.setXY(150, 50);
	add(lineFluxion2);

	lineFluxion2.setValueSample(100);
	lineFluxion2.setXY(200, 30);
	lineFluxion2.setDirection(LineFluxion::Direction::TOP_LEFT);
	lineFluxion2.start(0, 0, 0);

    txtCopyRight.setTypedText(TypedText(T_COPYRIGHT));
	txtCopyRight.setColor(Color::getColorFromRGB(0xFF, 0xFF, 0xFF));
	txtCopyRight.setXY(20 + 360, 5 + 400 + txtCopyRight.getTypedText().getFont()->getBaseline());
	add(txtCopyRight);
}

ContainerDeskPage0::~ContainerDeskPage0()
{
	touchgfx::CanvasWidgetRenderer::resetBuffer();
}
