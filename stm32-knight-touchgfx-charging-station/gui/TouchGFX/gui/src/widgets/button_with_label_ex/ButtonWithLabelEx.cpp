#include <gui/widgets/button_with_label_ex/ButtonWithLabelEx.hpp>
#include <touchgfx/FontManager.hpp>
#include <touchgfx/hal/HAL.hpp>

namespace touchgfx
{
ButtonWithLabelEx::ButtonWithLabelEx()
    : ButtonWithLabel(), x_prefix_offset_(0)
{
}

void ButtonWithLabelEx::draw(const Rect& area) const
{
    Button::draw(area);

    const Font* fontToDraw = typedText.getFont();
    if ((fontToDraw != 0) && typedText.hasValidId())
    {
        int16_t height = textHeightIncludingSpacing;
        int16_t offset;
        Rect labelRect;
        switch (rotation)
        {
        default:
        case TEXT_ROTATE_0:
        case TEXT_ROTATE_180:
            offset = (this->getHeight() - height) / 2;
            labelRect = Rect(x_prefix_offset_ , offset, this->getWidth(), height);
            break;
        case TEXT_ROTATE_90:
        case TEXT_ROTATE_270:
            offset = (this->getWidth() - height) / 2;
            labelRect = Rect(offset, 0, height, this->getHeight());
            break;
        }
        Rect dirty = labelRect & area;

        if (!dirty.isEmpty())
        {
            dirty.x -= labelRect.x;
            dirty.y -= labelRect.y;
            translateRectToAbsolute(labelRect);
            LCD::StringVisuals visuals(fontToDraw, pressed ? colorPressed : color, alpha, typedText.getAlignment(), 0, rotation, typedText.getTextDirection(), 0, WIDE_TEXT_NONE);
            HAL::lcd().drawString(labelRect, dirty, visuals, typedText.getText());
        }
    }
}
} // namespace touchgfx
