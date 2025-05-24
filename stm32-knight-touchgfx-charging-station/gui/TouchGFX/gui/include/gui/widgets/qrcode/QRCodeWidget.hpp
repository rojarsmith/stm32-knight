#ifndef QR_CODE_WIDGET_HPP
#define QR_CODE_WIDGET_HPP

#include <touchgfx/widgets/Widget.hpp>
#include <gui/widgets/qrcode/QRCode.hpp>
#include <touchgfx/hal/Types.hpp>

/**
* @class QRCodeWidget
* 
* @brief A widget for displaying a QRCode
* 
*        The widget will be drawn in black and white.
*        The values of the supplied QRCode will determine the appearance
*        The widget can be scaled in order to display the qr code in an appropriate size
*
*        @sa touchgfx::Widget
*/
class QRCodeWidget : public touchgfx::Widget
{
public:
    /**
     * @fn QRCodeWidget::QRCodeWidget();
     *
     * @brief Default constructor
     */
    QRCodeWidget();

	~QRCodeWidget();

    /**
     * @fn virtual void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const;
     *
     * @brief Draw the part of the qr code that is inside the invalidated area
     *        
     * @param invalidatedArea The region of this drawable that needs to be redrawn
     *
     * @sa touchgfx::Drawable
     */
    virtual void draw(const touchgfx::Rect& invalidatedArea) const;

    /**
     * @fn virtual touchgfx::Rect QRCodeWidget::getSolidRect() const;
     *
     * @brief Report this widget as being completely solid
     *
     * @return The solid rect.
     */
    virtual touchgfx::Rect getSolidRect() const;

    /**
     * @fn void QRCodeWidget::setQRCode(QRCode *code);
     *
     * @brief Set the qr code to display
     */
    void setQRCode(QRCode *code);

    /**
     * @fn void QRCodeWidget::setScale(uint8_t s);
     *
     * @brief Set the scaling factor of the widget
     */
    void setScale(uint8_t s);

	void setAlpha(uint8_t alpha);

	void setColor(uint8_t red, uint8_t green, uint8_t blue);
	void setBackgroundColor(uint8_t red, uint8_t green, uint8_t blue);
	
	uint8_t getAlpha() const
	{
		return alpha_;
	}
private:
    void updateSize();

    QRCode *code;
    uint8_t scale;
	uint8_t alpha_;
	uint16_t color_;
	uint16_t background_color_;	

	uint16_t convertRGB888toRGB565(uint8_t red, uint8_t green, uint8_t blue);
};

#endif