#include <gui/food_screen/OrderingItems.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

OrderingItems::OrderingItems(const int16_t sw, const int16_t sh, const uint16_t food_1_id, const uint16_t food_2_id, uint16_t food_3_id) :
    buttonClickedCallback(this, &OrderingItems::buttonClicked)
{
    quantity_1 = quantity_2 = quantity_3 = 0;

    setWidth(sw);
    setHeight(sh);

    imgFoodboard_1.setBitmap(Bitmap(BITMAP_FOODBOARD_ID));
    imgFoodboard_2.setBitmap(Bitmap(BITMAP_FOODBOARD_ID));
    imgFoodboard_3.setBitmap(Bitmap(BITMAP_FOODBOARD_ID));

    imgFood_1.setBitmap(Bitmap(food_1_id));
    imgFood_2.setBitmap(Bitmap(food_2_id));
    imgFood_3.setBitmap(Bitmap(food_3_id));

    btnMinus_1.setBitmaps(Bitmap(BITMAP_BTN_MINUS_RELEASED_ID), Bitmap(BITMAP_BTN_MINUS_PRESSED_ID));
    btnAdd_1.setBitmaps(Bitmap(BITMAP_BTN_ADD_RELEASED_ID), Bitmap(BITMAP_BTN_ADD_PRESSED_ID));
    btnMinus_2.setBitmaps(Bitmap(BITMAP_BTN_MINUS_RELEASED_ID), Bitmap(BITMAP_BTN_MINUS_PRESSED_ID));
    btnAdd_2.setBitmaps(Bitmap(BITMAP_BTN_ADD_RELEASED_ID), Bitmap(BITMAP_BTN_ADD_PRESSED_ID));
    btnMinus_3.setBitmaps(Bitmap(BITMAP_BTN_MINUS_RELEASED_ID), Bitmap(BITMAP_BTN_MINUS_PRESSED_ID));
    btnAdd_3.setBitmaps(Bitmap(BITMAP_BTN_ADD_RELEASED_ID), Bitmap(BITMAP_BTN_ADD_PRESSED_ID));

    uint16_t sideArea = imgFoodboard_1.getWidth() / 2;
    uint16_t pitch = (getWidth() - (sideArea * 2) - (imgFoodboard_1.getWidth() * 3)) / 2;
    uint16_t dist = (imgFoodboard_1.getWidth() - imgFood_1.getWidth()) / 2;

    imgFoodboard_1.setXY(sideArea, (getHeight() - imgFoodboard_1.getHeight()) / 2);
    imgFoodboard_2.setXY(sideArea + imgFoodboard_1.getWidth() + pitch, (getHeight() - imgFoodboard_1.getHeight()) / 2);
    imgFoodboard_3.setXY(sideArea + (imgFoodboard_1.getWidth() * 2) + (pitch * 2), (getHeight() - imgFoodboard_1.getHeight()) / 2);

    imgFood_1.setXY(imgFoodboard_1.getX() + dist, imgFoodboard_1.getY() + dist);
    imgFood_2.setXY(imgFoodboard_2.getX() + dist, imgFoodboard_2.getY() + dist);
    imgFood_3.setXY(imgFoodboard_3.getX() + dist, imgFoodboard_3.getY() + dist);

    btnMinus_1.setXY(imgFoodboard_1.getX() + dist, imgFoodboard_1.getY() + imgFoodboard_1.getHeight() - dist - btnMinus_1.getHeight());
    btnAdd_1.setXY(imgFoodboard_1.getX() + imgFoodboard_1.getWidth() - dist - btnAdd_1.getWidth(), imgFoodboard_1.getY() + imgFoodboard_1.getHeight() - dist - btnAdd_1.getHeight());
    btnMinus_2.setXY(imgFood_2.getX(), imgFoodboard_2.getY() + imgFoodboard_2.getHeight() - dist - btnMinus_2.getHeight());
    btnAdd_2.setXY(imgFood_2.getX() + imgFood_2.getWidth() - btnMinus_2.getWidth(), imgFoodboard_2.getY() + imgFoodboard_2.getHeight() - dist - btnAdd_2.getHeight());
    btnMinus_3.setXY(imgFood_3.getX(), imgFoodboard_3.getY() + imgFoodboard_3.getHeight() - dist - btnMinus_3.getHeight());
    btnAdd_3.setXY(imgFood_3.getX() + imgFood_3.getWidth() - btnMinus_3.getWidth(), imgFoodboard_3.getY() + imgFoodboard_3.getHeight() - dist - btnAdd_3.getHeight());

    btnMinus_1.setAction(buttonClickedCallback);
    btnAdd_1.setAction(buttonClickedCallback);
    btnMinus_2.setAction(buttonClickedCallback);
    btnAdd_2.setAction(buttonClickedCallback);
    btnMinus_3.setAction(buttonClickedCallback);
    btnAdd_3.setAction(buttonClickedCallback);

    add(imgFoodboard_1);
    add(imgFoodboard_2);
    add(imgFoodboard_3);
    add(imgFood_1);
    add(imgFood_2);
    add(imgFood_3);
    add(btnMinus_1);
    add(btnAdd_1);
    add(btnMinus_2);
    add(btnAdd_2);
    add(btnMinus_3);
    add(btnAdd_3);

    quantity_1 = 0;
    quantity_2 = 0;
    quantity_3 = 0;

    // Setup food 1 value text
    foodnum1Txt.setWildcard(foodnum1Txtbuf);
    foodnum1Txt.setTypedText(TypedText(T_FOOD_1_NUM));
    foodnum1Txt.setColor(Color::getColorFromRGB(0xFF, 0x00, 0x00));
    foodnum1Txt.setPosition(imgFood_1.getX(), imgFood_1.getY() + imgFood_1.getHeight(), imgFood_1.getWidth(), 20);
    add(foodnum1Txt);
    Unicode::snprintf(foodnum1Txtbuf, 5, "%d", quantity_1);
    foodnum1Txt.invalidate();

    // Setup food 2 value text
    foodnum2Txt.setWildcard(foodnum2Txtbuf);
    foodnum2Txt.setTypedText(TypedText(T_FOOD_2_NUM));
    foodnum2Txt.setColor(Color::getColorFromRGB(0xFF, 0x00, 0x00));
    foodnum2Txt.setPosition(imgFood_2.getX(), imgFood_2.getY() + imgFood_2.getHeight(), imgFood_2.getWidth(), 20);
    add(foodnum2Txt);
    Unicode::snprintf(foodnum2Txtbuf, 5, "%d", quantity_2);
    foodnum2Txt.invalidate();

    // Setup food 3 value text
    foodnum3Txt.setWildcard(foodnum3Txtbuf);
    foodnum3Txt.setTypedText(TypedText(T_FOOD_2_NUM));
    foodnum3Txt.setColor(Color::getColorFromRGB(0xFF, 0x00, 0x00));
    foodnum3Txt.setPosition(imgFood_3.getX(), imgFood_3.getY() + imgFood_3.getHeight(), imgFood_3.getWidth(), 20);
    add(foodnum3Txt);
    Unicode::snprintf(foodnum3Txtbuf, 5, "%d", quantity_3);
    foodnum3Txt.invalidate();
}

OrderingItems::~OrderingItems()
{
}

void OrderingItems::buttonClicked(const AbstractButton& source)
{
    if (&source == &btnMinus_1)
    {
        if (quantity_1 > 0)
        {
            quantity_1--;
            Unicode::snprintf(foodnum1Txtbuf, 5, "%d", quantity_1);
            foodnum1Txt.invalidate();
        }
    }

    if (&source == &btnAdd_1)
    {
        if (quantity_1 < 255)
        {
            quantity_1++;
            Unicode::snprintf(foodnum1Txtbuf, 5, "%d", quantity_1);
            foodnum1Txt.invalidate();
        }
    }

    if (&source == &btnMinus_2)
    {
        if (quantity_2 > 0)
        {
            quantity_2--;
            Unicode::snprintf(foodnum2Txtbuf, 5, "%d", quantity_2);
            foodnum2Txt.invalidate();
        }
    }

    if (&source == &btnAdd_2)
    {
        if (quantity_2 < 255)
        {
            quantity_2++;
            Unicode::snprintf(foodnum2Txtbuf, 5, "%d", quantity_2);
            foodnum2Txt.invalidate();
        }
    }

    if (&source == &btnMinus_3)
    {
        if (quantity_3 > 0)
        {
            quantity_3--;
            Unicode::snprintf(foodnum3Txtbuf, 5, "%d", quantity_3);
            foodnum3Txt.invalidate();
        }
    }

    if (&source == &btnAdd_3)
    {
        if (quantity_3 < 255)
        {
            quantity_3++;
            Unicode::snprintf(foodnum3Txtbuf, 5, "%d", quantity_3);
            foodnum3Txt.invalidate();
        }
    }
}

uint8_t OrderingItems::getQuantity_1()
{
    return quantity_1;
}

uint8_t OrderingItems::getQuantity_2()
{
    return quantity_2;
}

uint8_t OrderingItems::getQuantity_3()
{
    return quantity_3;
}

void OrderingItems::setQuantity_1(uint8_t value)
{
    quantity_1 = value;
    Unicode::snprintf(foodnum1Txtbuf, 5, "%d", quantity_1);
    foodnum1Txt.invalidate();
}

void OrderingItems::setQuantity_2(uint8_t value)
{
    quantity_2 = value;
    Unicode::snprintf(foodnum2Txtbuf, 5, "%d", quantity_2);
    foodnum2Txt.invalidate();
}

void OrderingItems::setQuantity_3(uint8_t value)
{
    quantity_3 = value;
    Unicode::snprintf(foodnum3Txtbuf, 5, "%d", quantity_3);
    foodnum3Txt.invalidate();
}
