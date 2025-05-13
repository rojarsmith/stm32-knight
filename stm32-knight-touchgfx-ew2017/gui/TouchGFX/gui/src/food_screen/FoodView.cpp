#include <gui/food_screen/FoodView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#ifndef SIMULATOR
#include "main.h"
#endif

FoodView::FoodView() :
#ifndef SIMULATOR
    screenwidthreal(getScreenWidthReal()),
    ItemsViewport1(getScreenWidthReal(), getScreenHeight(), BITMAP_FOOD_1_ID, BITMAP_FOOD_2_ID, BITMAP_FOOD_3_ID),
    ItemsViewport2(getScreenWidthReal(), getScreenHeight(), BITMAP_FOOD_4_ID, BITMAP_FOOD_5_ID, BITMAP_FOOD_6_ID),
    ItemsViewport3(getScreenWidthReal(), getScreenHeight(), BITMAP_FOOD_7_ID, BITMAP_FOOD_8_ID, BITMAP_FOOD_9_ID),
#else
    screenwidthreal(HAL::DISPLAY_WIDTH),
    ItemsViewport1(HAL::DISPLAY_WIDTH, getScreenHeight(), BITMAP_FOOD_1_ID, BITMAP_FOOD_2_ID, BITMAP_FOOD_3_ID),
    ItemsViewport2(HAL::DISPLAY_WIDTH, getScreenHeight(), BITMAP_FOOD_4_ID, BITMAP_FOOD_5_ID, BITMAP_FOOD_6_ID),
    ItemsViewport3(HAL::DISPLAY_WIDTH, getScreenHeight(), BITMAP_FOOD_7_ID, BITMAP_FOOD_8_ID, BITMAP_FOOD_9_ID),
#endif
	buttonClickedCallback(this, &FoodView::buttonClicked)
{

}

void FoodView::setupScreen()
{
	FoodViewBase::setupScreen();

    imgBackground.setBitmap(Bitmap(BITMAP_MAINBG_ID));
    imgBackground.setXY(0, 0);
    add(imgBackground);

    imgLogo.setBitmap(Bitmap(BITMAP_LOGO_SMALL_ID));
    imgLogo.setXY(10, 10);
    add(imgLogo);

    btnCategory1.setBitmaps(Bitmap(BITMAP_BTN_CATEGORY_1_RELEASED_ID), Bitmap(BITMAP_BTN_CATEGORY_1_PRESSED_ID));
    btnCategory2.setBitmaps(Bitmap(BITMAP_BTN_CATEGORY_2_RELEASED_ID), Bitmap(BITMAP_BTN_CATEGORY_2_PRESSED_ID));
    btnCategory3.setBitmaps(Bitmap(BITMAP_BTN_CATEGORY_3_RELEASED_ID), Bitmap(BITMAP_BTN_CATEGORY_3_PRESSED_ID));

    uint16_t btnwidth = btnCategory1.getWidth();
    uint16_t btnheight = btnCategory1.getHeight();
    uint16_t sideArea = (btnwidth * 3) / 4;
    uint16_t pitch = (screenwidthreal - (sideArea * 2) - (btnwidth * 3)) / 2;

    btnCategory1.setXY(sideArea, (HAL::DISPLAY_HEIGHT - btnheight) / 2);
    btnCategory2.setXY(sideArea + btnwidth + pitch, (HAL::DISPLAY_HEIGHT - btnheight) / 2);
    btnCategory3.setXY(sideArea + (btnwidth * 2) + (pitch * 2), (HAL::DISPLAY_HEIGHT - btnheight) / 2);

    btnCategory1.setAction(buttonClickedCallback);
    btnCategory2.setAction(buttonClickedCallback);
    btnCategory3.setAction(buttonClickedCallback);

    add(btnCategory1);
    add(btnCategory2);
    add(btnCategory3);

    ItemsViewport1.setXY(0 - screenwidthreal, 0);
    add(ItemsViewport1);
    ItemsViewport2.setXY(0 - screenwidthreal, 0);
    add(ItemsViewport2);
    ItemsViewport3.setXY(0 - screenwidthreal, 0);
    add(ItemsViewport3);
    ListViewport.setPosition(0, 0 - HAL::DISPLAY_HEIGHT, screenwidthreal, HAL::DISPLAY_HEIGHT);
    add(ListViewport);

    imgShoppinglist.setBitmap(Bitmap(BITMAP_SHOPPINGLIST_ID));
    imgShoppinglist.setXY(((screenwidthreal - imgShoppinglist.getWidth() + shoppingcarIcon) / 2) - shoppingcarIcon, (HAL::DISPLAY_HEIGHT - imgShoppinglist.getHeight()) / 2);
    ListViewport.add(imgShoppinglist);

    btnHome.setBitmaps(Bitmap(BITMAP_BTN_HOME_RELEASED_ID), Bitmap(BITMAP_BTN_HOME_PRESSED_ID));
    btnBackToCategory.setBitmaps(Bitmap(BITMAP_BTN_BACKTOCATEGORY_RELEASED_ID), Bitmap(BITMAP_BTN_BACKTOCATEGORY_PRESSED_ID));
    btnPrint.setBitmaps(Bitmap(BITMAP_BTN_PRINT_RELEASED_ID), Bitmap(BITMAP_BTN_PRINT_PRESSED_ID));
    btnShoppingCar.setBitmaps(Bitmap(BITMAP_BTN_SHOPPINGCAR_RELEASED_ID), Bitmap(BITMAP_BTN_SHOPPINGCAR_PRESSED_ID));

    uint16_t func_btn_width = btnHome.getWidth();
    uint16_t func_btn_height = btnHome.getHeight();

    btnHome.setXY(screenwidthreal - 10 - func_btn_width, HAL::DISPLAY_HEIGHT - func_btn_height);
    btnShoppingCar.setXY(screenwidthreal - 25 - func_btn_width * 2, HAL::DISPLAY_HEIGHT - func_btn_height);
    btnPrint.setXY(screenwidthreal - 25 - func_btn_width * 2, HAL::DISPLAY_HEIGHT - func_btn_height);
    btnBackToCategory.setXY(screenwidthreal - 40 - func_btn_width * 3, HAL::DISPLAY_HEIGHT - func_btn_height);

    btnHome.setAction(buttonClickedCallback);
    btnShoppingCar.setAction(buttonClickedCallback);
    btnPrint.setAction(buttonClickedCallback);
    btnBackToCategory.setAction(buttonClickedCallback);

    add(btnHome);
    add(btnShoppingCar);
    add(btnPrint);
    add(btnBackToCategory);

    btnPrint.setVisible(false);
    btnBackToCategory.setVisible(false);

    menuaction = NO_ANIMATION;
    category_num = NO_CATEGORY;
    btn_alpha = 255;
    visibleCheck = false;
    shoppingcarlist = false;
    printCheck = false;

    for (uint8_t i = 0; i < 9; i++)
    {
        food_value[i] = 0;
    }

    // Setup list food 1 text
    listFood1Txt.setWildcard(listFood1Txtbuf);
    listFood1Txt.setTypedText(TypedText(T_LIST_FOOD_1));
    listFood1Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood1Txt);
    listFood1Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood1Txtbuf, 30, "%d", food_value[0]);
    listFood1Txt.invalidate();

    // Setup list food 2 text
    listFood2Txt.setWildcard(listFood2Txtbuf);
    listFood2Txt.setTypedText(TypedText(T_LIST_FOOD_2));
    listFood2Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood2Txt);
    listFood2Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood2Txtbuf, 30, "%d", food_value[1]);
    listFood2Txt.invalidate();

    // Setup list food 3 text
    listFood3Txt.setWildcard(listFood3Txtbuf);
    listFood3Txt.setTypedText(TypedText(T_LIST_FOOD_3));
    listFood3Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood3Txt);
    listFood3Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood3Txtbuf, 30, "%d", food_value[2]);
    listFood3Txt.invalidate();

    // Setup list food 4 text
    listFood4Txt.setWildcard(listFood4Txtbuf);
    listFood4Txt.setTypedText(TypedText(T_LIST_FOOD_4));
    listFood4Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood4Txt);
    listFood4Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood4Txtbuf, 30, "%d", food_value[3]);
    listFood4Txt.invalidate();

    // Setup list food 5 text
    listFood5Txt.setWildcard(listFood5Txtbuf);
    listFood5Txt.setTypedText(TypedText(T_LIST_FOOD_5));
    listFood5Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood5Txt);
    listFood5Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood5Txtbuf, 30, "%d", food_value[4]);
    listFood5Txt.invalidate();

    // Setup list food 6 text
    listFood6Txt.setWildcard(listFood6Txtbuf);
    listFood6Txt.setTypedText(TypedText(T_LIST_FOOD_6));
    listFood6Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood6Txt);
    listFood6Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood6Txtbuf, 30, "%d", food_value[5]);
    listFood6Txt.invalidate();

    // Setup list food 7 text
    listFood7Txt.setWildcard(listFood7Txtbuf);
    listFood7Txt.setTypedText(TypedText(T_LIST_FOOD_7));
    listFood7Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood7Txt);
    listFood7Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood7Txtbuf, 30, "%d", food_value[6]);
    listFood7Txt.invalidate();

    // Setup list food 8 text
    listFood8Txt.setWildcard(listFood8Txtbuf);
    listFood8Txt.setTypedText(TypedText(T_LIST_FOOD_8));
    listFood8Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood8Txt);
    listFood8Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood8Txtbuf, 30, "%d", food_value[7]);
    listFood8Txt.invalidate();

    // Setup list food 9 text
    listFood9Txt.setWildcard(listFood9Txtbuf);
    listFood9Txt.setTypedText(TypedText(T_LIST_FOOD_9));
    listFood9Txt.setColor(Color::getColorFromRGB(0x0, 0x0, 0x0));
    ListViewport.add(listFood9Txt);
    listFood9Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
    Unicode::snprintf(listFood9Txtbuf, 30, "%d", food_value[8]);
    listFood9Txt.invalidate();
}

void FoodView::tearDownScreen()
{
	FoodViewBase::tearDownScreen();
}

/**
* Determine which button was pressed, and let
* presenter decide how to react on specific action
*/
void FoodView::buttonClicked(const AbstractButton& source)
{
    if (&source == &btnCategory1)
    {
        category_num = CATEGORY1;
    }
    else if (&source == &btnCategory2)
    {
        category_num = CATEGORY2;
    } 
    else if (&source == &btnCategory3)
    {
        category_num = CATEGORY3;
    }

    if (&source == &btnBackToCategory)
    {
        if (category_num != NO_CATEGORY)
        {
            if (category_num == LIST)
            {
                menuaction = ANIMATE_UP;
            }
            else
            {
                menuaction = ANIMATE_LEFT;
            }
        }
    }

    if (&source == &btnShoppingCar)
    {
        food_value[0] = ItemsViewport1.getQuantity_1();
        food_value[1] = ItemsViewport1.getQuantity_2();
        food_value[2] = ItemsViewport1.getQuantity_3();
        food_value[3] = ItemsViewport2.getQuantity_1();
        food_value[4] = ItemsViewport2.getQuantity_2();
        food_value[5] = ItemsViewport2.getQuantity_3();
        food_value[6] = ItemsViewport3.getQuantity_1();
        food_value[7] = ItemsViewport3.getQuantity_2();
        food_value[8] = ItemsViewport3.getQuantity_3();

        listheight_tmp = FoodTxtStartY;

        if (food_value[0] != 0)
        {
            listFood1Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood1Txtbuf, 30, "%d", food_value[0]);
            listFood1Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood1Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood1Txtbuf, 30, "%d", food_value[0]);
            listFood1Txt.invalidate();
        }

        if (food_value[1] != 0)
        {
            listFood2Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood2Txtbuf, 30, "%d", food_value[1]);
            listFood2Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood2Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood2Txtbuf, 30, "%d", food_value[1]);
            listFood2Txt.invalidate();
        }

        if (food_value[2] != 0)
        {
            listFood3Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood3Txtbuf, 30, "%d", food_value[2]);
            listFood3Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood3Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood3Txtbuf, 30, "%d", food_value[2]);
            listFood3Txt.invalidate();
        }

        if (food_value[3] != 0)
        {
            listFood4Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood4Txtbuf, 30, "%d", food_value[3]);
            listFood4Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood4Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood4Txtbuf, 30, "%d", food_value[3]);
            listFood4Txt.invalidate();
        }

        if (food_value[4] != 0)
        {
            listFood5Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood5Txtbuf, 30, "%d", food_value[4]);
            listFood5Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood5Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood5Txtbuf, 30, "%d", food_value[4]);
            listFood5Txt.invalidate();
        }

        if (food_value[5] != 0)
        {
            listFood6Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood6Txtbuf, 30, "%d", food_value[5]);
            listFood6Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood6Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood6Txtbuf, 30, "%d", food_value[5]);
            listFood6Txt.invalidate();
        }

        if (food_value[6] != 0)
        {
            listFood7Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood7Txtbuf, 30, "%d", food_value[6]);
            listFood7Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood7Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood7Txtbuf, 30, "%d", food_value[6]);
            listFood7Txt.invalidate();
        }

        if (food_value[7] != 0)
        {
            listFood8Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood8Txtbuf, 30, "%d", food_value[7]);
            listFood8Txt.invalidate();
            listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood8Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood8Txtbuf, 30, "%d", food_value[7]);
            listFood8Txt.invalidate();
        }

        if (food_value[8] != 0)
        {
            listFood9Txt.setPosition(FoodTxtStartX, listheight_tmp, FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood9Txtbuf, 30, "%d", food_value[8]);
            listFood9Txt.invalidate();
            //listheight_tmp += FoodTxtPitch;
        }
        else
        {
            listFood9Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
            Unicode::snprintf(listFood9Txtbuf, 30, "%d", food_value[8]);
            listFood9Txt.invalidate();
        }

        if (category_num != NO_CATEGORY)
        {
            menuaction = ANIMATE_LEFT;
        }
        else
        {
            category_num = LIST;
            menuaction = ANIMATE_DOWN;
        }
        shoppingcarlist = true;
    }

    if (&source == &btnPrint)
    {
        qtyCheck = 0;
        for (uint8_t i = 0; i < 9; i++)
        {
            if (food_value[i] > 0)
            {
                qtyCheck++;
            }
        }
    }

    if (&source == &btnHome)
    {
        presenter->gotoMainScreenFromFoodScreen();
    }
}

void FoodView::handleTickEvent()
{
    if ((category_num != NO_CATEGORY) && (visibleCheck == false))
    {
        if (btn_alpha > 0)
        {
            btn_alpha -= 15;
            btnCategory1.setAlpha(btn_alpha);
            btnCategory1.invalidate();
            btnCategory2.setAlpha(btn_alpha);
            btnCategory2.invalidate();
            btnCategory3.setAlpha(btn_alpha);
            btnCategory3.invalidate();
        }
        else
        {
            btnCategory1.setTouchable(false);
            btnCategory2.setTouchable(false);
            btnCategory3.setTouchable(false);
            visibleCheck = true;
            menuaction = ANIMATE_RIGHT;
        }
    }

    switch (menuaction)
    {
    case ANIMATE_UP:
        if (ListViewport.getY() != (0 - HAL::DISPLAY_HEIGHT))
        {
            ListViewport.moveRelative(0, -DELTA_Y);
            ListViewport.invalidate();
        }
        else
        {
            if (btn_alpha < 255)
            {
                btn_alpha += 15;
                btnCategory1.setAlpha(btn_alpha);
                btnCategory1.invalidate();
                btnCategory2.setAlpha(btn_alpha);
                btnCategory2.invalidate();
                btnCategory3.setAlpha(btn_alpha);
                btnCategory3.invalidate();
            }
            else
            {
                btnCategory1.setTouchable(true);
                btnCategory2.setTouchable(true);
                btnCategory3.setTouchable(true);
                btnBackToCategory.setVisible(false);
                btnBackToCategory.invalidate();
                btnPrint.setVisible(false);
                btnPrint.invalidate();
                btnShoppingCar.setVisible(true);
                btnShoppingCar.invalidate();
                visibleCheck = false;
                shoppingcarlist = false;
                menuaction = NO_ANIMATION;
                category_num = NO_CATEGORY;
            }
        }
        break;

    case ANIMATE_DOWN:
        if (visibleCheck == false)
        {
            if (btn_alpha > 0)
            {
                btn_alpha -= 15;
                btnCategory1.setAlpha(btn_alpha);
                btnCategory1.invalidate();
                btnCategory2.setAlpha(btn_alpha);
                btnCategory2.invalidate();
                btnCategory3.setAlpha(btn_alpha);
                btnCategory3.invalidate();
            }
            else
            {
                btnCategory1.setTouchable(false);
                btnCategory2.setTouchable(false);
                btnCategory3.setTouchable(false);
                visibleCheck = true;
            }
        }

        if (ListViewport.getY() != 0)
        {
            ListViewport.moveRelative(0, DELTA_Y);
            ListViewport.invalidate();
        }
        else
        {
            btnBackToCategory.setVisible(true);
            btnBackToCategory.invalidate();
            btnShoppingCar.setVisible(false);
            btnShoppingCar.invalidate();
            btnPrint.setVisible(false);
            btnPrint.invalidate();
            menuaction = NO_ANIMATION;
        }
        break;

    case ANIMATE_LEFT:
        if (category_num == CATEGORY1)
        {
            if (ItemsViewport1.getX() != -static_cast<int>(screenwidthreal))
            {
                ItemsViewport1.moveRelative(-DELTA_X, 0);
                ItemsViewport1.invalidate();
            }
            else
            {
                if (shoppingcarlist == true)
                {
                    category_num = LIST;
                    menuaction = ANIMATE_DOWN;
                }
                else
                {
                    if (btn_alpha < 255)
                    {
                        btn_alpha += 15;
                        btnCategory1.setAlpha(btn_alpha);
                        btnCategory1.invalidate();
                        btnCategory2.setAlpha(btn_alpha);
                        btnCategory2.invalidate();
                        btnCategory3.setAlpha(btn_alpha);
                        btnCategory3.invalidate();
                    }
                    else
                    {
                        btnCategory1.setTouchable(true);
                        btnCategory2.setTouchable(true);
                        btnCategory3.setTouchable(true);
                        btnBackToCategory.setVisible(false);
                        btnBackToCategory.invalidate();
                        visibleCheck = false;
                        menuaction = NO_ANIMATION;
                        category_num = NO_CATEGORY;
                    }
                }
            }
        }
        if (category_num == CATEGORY2)
        {
            if (ItemsViewport2.getX() != -static_cast<int>(screenwidthreal))
            {
                ItemsViewport2.moveRelative(-DELTA_X, 0);
                ItemsViewport2.invalidate();
            }
            else
            {
                if (shoppingcarlist == true)
                {
                    category_num = LIST;
                    menuaction = ANIMATE_DOWN;
                }
                else
                {
                    if (btn_alpha < 255)
                    {
                        btn_alpha += 15;
                        btnCategory1.setAlpha(btn_alpha);
                        btnCategory1.invalidate();
                        btnCategory2.setAlpha(btn_alpha);
                        btnCategory2.invalidate();
                        btnCategory3.setAlpha(btn_alpha);
                        btnCategory3.invalidate();
                    }
                    else
                    {
                        btnCategory1.setTouchable(true);
                        btnCategory2.setTouchable(true);
                        btnCategory3.setTouchable(true);
                        btnBackToCategory.setVisible(false);
                        btnBackToCategory.invalidate();
                        visibleCheck = false;
                        menuaction = NO_ANIMATION;
                        category_num = NO_CATEGORY;
                    }
                }
            }
        }
        if (category_num == CATEGORY3)
        {
            if (ItemsViewport3.getX() -static_cast<int>(screenwidthreal))
            {
                ItemsViewport3.moveRelative(-DELTA_X, 0);
                ItemsViewport3.invalidate();
            }
            else
            {
                if (shoppingcarlist == true)
                {
                    category_num = LIST;
                    menuaction = ANIMATE_DOWN;
                }
                else
                {
                    if (btn_alpha < 255)
                    {
                        btn_alpha += 15;
                        btnCategory1.setAlpha(btn_alpha);
                        btnCategory1.invalidate();
                        btnCategory2.setAlpha(btn_alpha);
                        btnCategory2.invalidate();
                        btnCategory3.setAlpha(btn_alpha);
                        btnCategory3.invalidate();
                    }
                    else
                    {
                        btnCategory1.setTouchable(true);
                        btnCategory2.setTouchable(true);
                        btnCategory3.setTouchable(true);
                        btnBackToCategory.setVisible(false);
                        btnBackToCategory.invalidate();
                        visibleCheck = false;
                        menuaction = NO_ANIMATION;
                        category_num = NO_CATEGORY;
                    }
                }
            }
        }
        break;

    case ANIMATE_RIGHT:
        if ((category_num == CATEGORY1) && (visibleCheck == true))
        {
            if (ItemsViewport1.getX() != 0)
            {
                ItemsViewport1.moveRelative(DELTA_X, 0);
                ItemsViewport1.invalidate();
            }
            else
            {
                menuaction = NO_ANIMATION;
                btnBackToCategory.setVisible(true);
                btnBackToCategory.invalidate();
            }
        }
        if ((category_num == CATEGORY2) && (visibleCheck == true))
        {
            if (ItemsViewport2.getX() != 0)
            {
                ItemsViewport2.moveRelative(DELTA_X, 0);
                ItemsViewport1.invalidate();
            }
            else
            {
                menuaction = NO_ANIMATION;
                btnBackToCategory.setVisible(true);
                btnBackToCategory.invalidate();
            }
        }
        if ((category_num == CATEGORY3) && (visibleCheck == true))
        {
            if (ItemsViewport3.getX() != 0)
            {
                ItemsViewport3.moveRelative(DELTA_X, 0);
                ItemsViewport1.invalidate();
            }
            else
            {
                menuaction = NO_ANIMATION;
                btnBackToCategory.setVisible(true);
                btnBackToCategory.invalidate();
            }
        }
        break;

    case NO_ANIMATION:
        break;

    default:
        break;
    }

    if (printCheck == true)
    {
        for (uint8_t i = 0; i < 9; i++)
        {
            food_value[i] = 0;
        }

        listFood1Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood1Txtbuf, 30, "%d", food_value[0]);
        listFood1Txt.invalidate();

        listFood2Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood2Txtbuf, 30, "%d", food_value[1]);
        listFood2Txt.invalidate();

        listFood3Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood3Txtbuf, 30, "%d", food_value[2]);
        listFood3Txt.invalidate();

        listFood4Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood4Txtbuf, 30, "%d", food_value[3]);
        listFood4Txt.invalidate();

        listFood5Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood5Txtbuf, 30, "%d", food_value[4]);
        listFood5Txt.invalidate();

        listFood6Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood6Txtbuf, 30, "%d", food_value[5]);
        listFood6Txt.invalidate();

        listFood7Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood7Txtbuf, 30, "%d", food_value[6]);
        listFood7Txt.invalidate();

        listFood8Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood8Txtbuf, 30, "%d", food_value[7]);
        listFood8Txt.invalidate();

        listFood9Txt.setPosition(FoodTxtStartX, (0 - HAL::DISPLAY_HEIGHT), FoodTxtWidth, FoodTxtHeight);
        Unicode::snprintf(listFood9Txtbuf, 30, "%d", food_value[8]);
        listFood9Txt.invalidate();

        ItemsViewport1.setQuantity_1(food_value[0]);
        ItemsViewport1.setQuantity_2(food_value[1]);
        ItemsViewport1.setQuantity_3(food_value[2]);
        ItemsViewport2.setQuantity_1(food_value[3]);
        ItemsViewport2.setQuantity_2(food_value[4]);
        ItemsViewport2.setQuantity_3(food_value[5]);
        ItemsViewport3.setQuantity_1(food_value[6]);
        ItemsViewport3.setQuantity_2(food_value[7]);
        ItemsViewport3.setQuantity_3(food_value[8]);

        printCheck = false;
        // Back to category
        menuaction = ANIMATE_UP;

        btnHome.setTouchable(true);
        btnShoppingCar.setTouchable(true);
        btnBackToCategory.setTouchable(true);
        btnPrint.setTouchable(false);
        //=====================================================================
    }
    else {

    }
}

