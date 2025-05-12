#ifndef ORDERINGITEMS_HPP
#define ORDERINGITEMS_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace touchgfx;

class OrderingItems : public Container
{
public:
    OrderingItems(const int16_t sw, const int16_t sh, const uint16_t food_1_id, const uint16_t food_2_id_id, uint16_t food_3_id_id);
    virtual ~OrderingItems();

    //virtual void handleTickEvent();

    void buttonClicked(const AbstractButton& source);
    uint8_t getQuantity_1();
    uint8_t getQuantity_2();
    uint8_t getQuantity_3();
    void setQuantity_1(uint8_t value);
    void setQuantity_2(uint8_t value);
    void setQuantity_3(uint8_t value);

private:
    Button btnAdd_1, btnMinus_1;
    Button btnAdd_2, btnMinus_2;
    Button btnAdd_3, btnMinus_3;
    Image imgFood_1, imgFood_2, imgFood_3;
    Image imgFoodboard_1, imgFoodboard_2, imgFoodboard_3;

    uint8_t quantity_1, quantity_2, quantity_3;

    TextAreaWithOneWildcard foodnum1Txt, foodnum2Txt, foodnum3Txt;
    Unicode::UnicodeChar foodnum1Txtbuf[5], foodnum2Txtbuf[5], foodnum3Txtbuf[5];

    Callback<OrderingItems, const AbstractButton&> buttonClickedCallback;
};
#endif /* ORDERINGITEMS_HPP */
