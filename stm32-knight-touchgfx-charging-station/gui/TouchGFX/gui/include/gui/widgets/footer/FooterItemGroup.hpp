#ifndef FOOTER_ITEM_GROUP_HPP
#define FOOTER_ITEM_GROUP_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class FooterItemGroup : public Container
{
public:
	FooterItemGroup();
	virtual ~FooterItemGroup();

	virtual void handleTickEvent();		
	void initialize(MachineStatus* status);		
	void renderGraphic();
	void renderElementLowSpeed();
protected:
	
private:
	static const uint16_t TEXT_SIZE_4 = 4;
	static const uint16_t TEXT_SIZE_5 = 5;
	static const uint16_t TEXT_SIZE_6 = 6;
	static const uint16_t TEXT_SIZE_21 = 21;
	static const uint16_t left_items_origin_x_ = 25;
	static const uint16_t left_item_top_margin_ = 27;
	static const uint16_t left_item_right_margin_1_ = 64;
	static const uint16_t left_item_right_margin_2_ = 76;
	static const uint16_t left_item_right_margin_3_ = 88;

	MachineStatus *ms_;
	WeatherStyle* weather_;
	WeatherStyle* weather_prev_;

	Box background_;
	Image split_line_;
	Image icon_phone_;
	Image icon_clock_;

	TextAreaWithOneWildcard text_head_1_;	
	TextAreaWithOneWildcard text_value_1_;
	Unicode::UnicodeChar text_value_1_buffer_[TEXT_SIZE_6];
	TextAreaWithOneWildcard text_tail_1_;	
	TextAreaWithOneWildcard text_head_2_;
	Unicode::UnicodeChar text_head_2_buffer_[TEXT_SIZE_5];
	TextAreaWithOneWildcard text_value2_;
	Unicode::UnicodeChar text_value_2_buffer_[TEXT_SIZE_6];
	TextAreaWithOneWildcard text_tail_2_;	
	Unicode::UnicodeChar text_tail_2_buffer_[TEXT_SIZE_4];		
	TextAreaWithOneWildcard phone_;
	Unicode::UnicodeChar phone_buffer_[TEXT_SIZE_21];
	TextAreaWithOneWildcard clock_;	
	Unicode::UnicodeChar clock_buffer_[TEXT_SIZE_21];
};

#endif /* FOOTER_ITEM_GROUP_HPP */