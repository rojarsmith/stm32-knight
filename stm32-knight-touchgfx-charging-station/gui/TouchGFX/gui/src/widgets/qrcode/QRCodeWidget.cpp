#include <gui/widgets/qrcode/QRCodeWidget.hpp>
#include <touchgfx/hal/HAL.hpp>

QRCodeWidget::QRCodeWidget() : 
    code(0),
    scale(1),
	alpha_(255),
	color_(0),
	background_color_(0xFFFF)
{
}

QRCodeWidget::~QRCodeWidget()
{
	if (0 != code)
	{
		code->gc();
	}
}

void QRCodeWidget::setQRCode(QRCode *qrCode)
{
    code = qrCode;
    updateSize();
}

void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
    if(0 == code)
    {
        return;
    }

    touchgfx::Rect absolute = getAbsoluteRect();

    uint16_t *framebuffer = touchgfx::HAL::getInstance()->lockFrameBuffer();

	uint16_t r90x = touchgfx::HAL::DISPLAY_WIDTH - absolute.x - invalidatedArea.right();

	for (int y = invalidatedArea.y; y < invalidatedArea.bottom(); y++)
    {
		for (int x = invalidatedArea.x; x < invalidatedArea.right(); x++)
        {
			framebuffer[absolute.y + y + (r90x + x) * touchgfx::HAL::DISPLAY_HEIGHT] = code->at(y / scale, (invalidatedArea.right() - x) / scale) ? color_ : background_color_;
        }
    }

    touchgfx::HAL::getInstance()->unlockFrameBuffer();
}

touchgfx::Rect QRCodeWidget::getSolidRect() const
{
	return touchgfx::Rect(0, 0, getWidth(), getHeight());
}

void QRCodeWidget::setScale(uint8_t s)
{
	if (0 == code)
	{
		return;
	}

    scale = s;
    updateSize();
}

void QRCodeWidget::updateSize()
{
    if(0 != code)
    {
        setWidth(code->getWidth() * scale);
        setHeight(code->getHeight() * scale);
    }    
}

void QRCodeWidget::setAlpha(uint8_t alpha)
{
	this->alpha_ = alpha;
}

void QRCodeWidget::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
	color_ = convertRGB888toRGB565(red, green, blue);
}

void QRCodeWidget::setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue)
{
	background_color_ = convertRGB888toRGB565(red, green, blue);	
}

uint16_t QRCodeWidget::convertRGB888toRGB565(uint8_t red, uint8_t green, uint8_t blue)
{
	uint16_t b = (blue >> 3) & 0x1f;
	uint16_t g = ((green >> 2) & 0x3f) << 5;
	uint16_t r = ((red >> 3) & 0x1f) << 11;

	return (uint16_t)(r | g | b);
}