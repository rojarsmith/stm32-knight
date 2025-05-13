#ifndef FOODVIEW_HPP
#define FOODVIEW_HPP

#include <gui_generated/food_screen/FoodViewBase.hpp>
#include <gui/food_screen/FoodPresenter.hpp>
#include <gui/food_screen/OrderingItems.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/Container.hpp>
#include <BitmapDatabase.hpp>

class FoodView : public FoodViewBase
{
public:
    FoodView();
    virtual ~FoodView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
    void buttonClicked(const AbstractButton& source);
    uint8_t foodvaluecheck[9];
    bool printCheck;
protected:
    enum Animation
    {
        ANIMATE_UP,
        ANIMATE_DOWN,
        ANIMATE_LEFT,
        ANIMATE_RIGHT,
        NO_ANIMATION
    };

    Animation menuaction;

    enum CategoryNumber
    {
        CATEGORY1,
        CATEGORY2,
        CATEGORY3,
        LIST,
        NO_CATEGORY
    };
    CategoryNumber category_num;

private:
    Image imgBackground, imgShoppinglist, imgLogo;
    Button btnCategory1, btnCategory2, btnCategory3;
    Button btnHome, btnShoppingCar, btnBackToCategory, btnPrint;

    uint32_t screenwidthreal = 0;

    OrderingItems ItemsViewport1;
    OrderingItems ItemsViewport2;
    OrderingItems ItemsViewport3;

    Container ListViewport;
    static const uint8_t DELTA_X = 40; //480*272:24, 800*480:40
    static const uint8_t DELTA_Y = 30; //480*272:17, 800*480:30
    static const uint16_t FoodTxtWidth = 498; //480*272:300, 800*480:498
    static const uint8_t FoodTxtHeight = 20;
    static const uint8_t FoodTxtPitch = 14;
    static const uint8_t FoodTxtStartX = 192; // 116
    static const uint8_t FoodTxtStartY = 142; // 74
    static const uint8_t shoppingcarIcon = 27;
    uint8_t listheight_tmp;

    uint8_t btn_alpha;
    uint8_t qtyCheck;
    bool visibleCheck;
    bool shoppingcarlist;

    TextAreaWithOneWildcard listFood1Txt, listFood2Txt, listFood3Txt;
    TextAreaWithOneWildcard listFood4Txt, listFood5Txt, listFood6Txt;
    TextAreaWithOneWildcard listFood7Txt, listFood8Txt, listFood9Txt;
    Unicode::UnicodeChar listFood1Txtbuf[30], listFood2Txtbuf[30], listFood3Txtbuf[30];
    Unicode::UnicodeChar listFood4Txtbuf[30], listFood5Txtbuf[30], listFood6Txtbuf[30];
    Unicode::UnicodeChar listFood7Txtbuf[30], listFood8Txtbuf[30], listFood9Txtbuf[30];

    uint8_t food_value[9];

    Callback<FoodView, const AbstractButton&> buttonClickedCallback;
};

#endif // FOODVIEW_HPP
