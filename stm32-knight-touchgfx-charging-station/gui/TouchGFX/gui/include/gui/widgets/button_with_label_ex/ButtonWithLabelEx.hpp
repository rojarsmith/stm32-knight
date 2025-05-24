#ifndef BUTTONWITHLABELEX_HPP
#define BUTTONWITHLABELEX_HPP

#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/TypedText.hpp>

namespace touchgfx
{
class ButtonWithLabelEx : public ButtonWithLabel
{
public:

    /**
     * @fn ButtonWithLabelEx::ButtonWithLabelEx();
     *
     * @brief Default constructor.
     *
     *        Default constructor.
     */
    ButtonWithLabelEx();

    /**
     * @fn void ButtonWithLabelEx::setLabelText(TypedText t)
     *
     * @brief Sets the text to display on the button.
     *
     *        Sets the text to display on the button. Texts with wildcards are not supported.
     *
     * @param t The text to display.
     */
    void setLabelTextXPrefixOffset(int16_t x)
    {
		x_prefix_offset_ = x;        
        updateTextPosition();
    }

    /**
     * @fn void ButtonWithLabelEx::updateTextPosition()
     *
     * @brief Positions the label text as horizontally centered.
     *
     *        If the text changes due to a language change you may need to reposition the label
     *        text to stay horizontally centered.
     *
     * @note The method does not invalidate the button. This must be done manually.
     */
    void updateTextPosition()
    {
        const Font* f = typedText.getFont();
        const Unicode::UnicodeChar* s = typedText.getText();
        textHeightIncludingSpacing = f->getHeight() * f->getNumberOfLines(s) + f->getSpacingAbove(s);
    }    

    virtual void draw(const Rect& area) const;

protected:
	int16_t x_prefix_offset_;
};
} // namespace touchgfx

#endif // BUTTONWITHLABELEX_HPP
