#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/footer/FooterItemGroup.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/hal/HAL.hpp>

FooterItemGroup::FooterItemGroup()
{			
}

FooterItemGroup::~FooterItemGroup()
{
}

void FooterItemGroup::handleTickEvent()
{
}

void FooterItemGroup::initialize(MachineStatus* status)
{
	ms_ = status;
	weather_ = &ms_->ux_weather;
	weather_prev_ = &ms_->ux_weather_prev;

	add(background_);
	add(split_line_);

	add(icon_phone_);
	add(phone_);

	add(icon_clock_);
	add(clock_);	

	add(text_head_1_);
	add(text_value_1_);
	add(text_tail_1_);
	add(text_head_2_);
	add(text_value2_);
	add(text_tail_2_);

	renderGraphic();
}

void FooterItemGroup::renderGraphic()
{
	if (*weather_ != *weather_prev_)
	{
		renderElementLowSpeed();
	}
	
	text_value_1_.setPosition(40, left_item_top_margin_, 40, 17);
	//text_value_1_.setPosition(80 + 5, 44, 62, 28); // 1024x768
	text_value_1_.setAlpha(255);
	text_value_1_.setColor(touchgfx::Color::getColorFromRGB(76, 199, 238));
	text_value_1_.setLinespacing(0);
	text_value_1_.setTypedText(TypedText(T_FOOTER_MONEY));
	int pklen = sizeof(ms_->ux_per_kwh);
	text_value_1_buffer_[pklen - 1] = 0;
	Unicode::strncpy(text_value_1_buffer_, ms_->ux_per_kwh, pklen);
	text_value_1_.setWildcard(text_value_1_buffer_);
	text_value_1_.invalidate();

	text_value2_.setPosition(206, left_item_top_margin_, 40, 17);
	//text_value2_.setPosition(345 - 6, 44, 62, 28); // 1024x768
	text_value2_.setAlpha(255);
	text_value2_.setColor(touchgfx::Color::getColorFromRGB(76, 199, 238));
	text_value2_.setLinespacing(0);
	text_value2_.setTypedText(TypedText(T_FOOTER_MONEY));
	int mklen = sizeof(ms_->ux_max_kw);
	text_value_2_buffer_[mklen - 1] = 0;
	Unicode::strncpy(text_value_2_buffer_, ms_->ux_max_kw, mklen);
	text_value2_.setWildcard(text_value_2_buffer_);
	text_value2_.invalidate();

	uint8_t cr = 0;
	uint8_t cg = 0;
	uint8_t cb = 0;
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		cr = 255;
		cg = 255;
		cb = 255;
	}

	phone_.setPosition(354, 18, 112, 15);
	//phone_.setPosition(567, 30, 180, 24); // 1024x768
	phone_.setAlpha(255);
	phone_.setLinespacing(0);
	phone_.setTypedText(TypedText(T_FOOTER_PHONE));
	int phlen = sizeof(ms_->ux_phone);
	phone_buffer_[phlen - 1] = 0;
	Unicode::strncpy(phone_buffer_, ms_->ux_phone, phlen);
	phone_.setWildcard(phone_buffer_);
	phone_.setColor(touchgfx::Color::getColorFromRGB(cr, cg, cb));
	phone_.invalidate();

	clock_.setPosition(354, 40, 112, 15);
	//clock_.setPosition(567, 65, 180, 24);
	clock_.setAlpha(255);
	clock_.setLinespacing(0);
	clock_.setTypedText(TypedText(T_FOOTER_CLOCK));
	int cllen = sizeof(ms_->ux_datetime);
	clock_buffer_[cllen - 1] = 0;
	Unicode::strncpy(clock_buffer_, ms_->ux_datetime, cllen);
	clock_.setWildcard(clock_buffer_);
	clock_.setColor(Color::getColorFromRGB(cr, cg, cb));
	clock_.invalidate();
}

void FooterItemGroup::renderElementLowSpeed()
{
	uint8_t cr = 0xDF;
	uint8_t cg = 0xE4;
	uint8_t cb = 0xE6;
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		cr = 0x1A;
		cg = 0x19;
		cb = 0x18;
	}

	background_.setPosition(0, 0, HAL::DISPLAY_WIDTH, 72); // 800x480
	//background_.setPosition(0, 0, HAL::DISPLAY_WIDTH, 116);
	background_.setColor(Color::getColorFromRGB(cr, cg, cb));

	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		split_line_.setBitmap(Bitmap(BITMAP_FOOTER_LINE_ID));
		split_line_.setPosition(298, 22, Bitmap(BITMAP_FOOTER_LINE_ID).getWidth(), Bitmap(BITMAP_FOOTER_LINE_ID).getHeight());
		//split_line_.setPosition(477, 36, Bitmap(BITMAP_FOOTER_LINE_ID).getWidth(), Bitmap(BITMAP_FOOTER_LINE_ID).getHeight());

		icon_phone_.setBitmap(Bitmap(BITMAP_FOOTER_PHONE_ID));
		icon_phone_.setPosition(330, 18, Bitmap(BITMAP_FOOTER_PHONE_ID).getWidth(), Bitmap(BITMAP_FOOTER_PHONE_ID).getHeight());
		//icon_phone_.setPosition(528, 29, Bitmap(BITMAP_FOOTER_PHONE_ID).getWidth(), Bitmap(BITMAP_FOOTER_PHONE_ID).getHeight());

		icon_clock_.setBitmap(Bitmap(BITMAP_FOOTER_CLOCK_ID));
		icon_clock_.setPosition(330, 39, Bitmap(BITMAP_FOOTER_CLOCK_ID).getWidth(), Bitmap(BITMAP_FOOTER_CLOCK_ID).getHeight());
		//icon_clock_.setPosition(528, 63, Bitmap(BITMAP_FOOTER_CLOCK_ID).getWidth(), Bitmap(BITMAP_FOOTER_CLOCK_ID).getHeight());

		int16_t flowitem_x = left_items_origin_x_;
		text_head_1_.setPosition(flowitem_x, left_item_top_margin_, 38, 17);
		//text_head_1_.setPosition(80 - 10, 44, 62, 28);
		text_head_1_.setAlpha(255);
		text_head_1_.setColor(touchgfx::Color::getColorFromRGB(76, 199, 238));
		text_head_1_.setLinespacing(0);
		text_head_1_.setTypedText(TypedText(T_FOOTER_CURRENCY));

		flowitem_x += left_item_right_margin_1_;
		text_tail_1_.setPosition(flowitem_x, left_item_top_margin_, 57, 17);
		//text_tail_1_.setPosition(149, 44, 88, 28);
		text_tail_1_.setAlpha(255);
		text_tail_1_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		text_tail_1_.setLinespacing(0);
		text_tail_1_.setTypedText(TypedText(T_FOOTER_PER_KWH));

		flowitem_x += left_item_right_margin_2_;
		text_head_2_.setPosition(flowitem_x, left_item_top_margin_, 55, 17);
		//text_head_2_.setPosition(280, 44, 88, 28);
		text_head_2_.setAlpha(255);
		text_head_2_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		text_head_2_.setLinespacing(0);
		text_head_2_.setTypedText(TypedText(T_FOOTER_MAX_DOT));

		flowitem_x += left_item_right_margin_3_;
		text_tail_2_.setPosition(flowitem_x, left_item_top_margin_, 55, 17);
		//text_tail_2_.setPosition(401, 44, 88, 28);
		text_tail_2_.setAlpha(255);
		text_tail_2_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		text_tail_2_.setLinespacing(0);
		text_tail_2_.setTypedText(TypedText(T_FOOTER_KW));
	}
	else
	{
		split_line_.setBitmap(Bitmap(BITMAP_FOOTER_LINE_ID));
		split_line_.setPosition(298, 22, Bitmap(BITMAP_FOOTER_LINE_ID).getWidth(), Bitmap(BITMAP_FOOTER_LINE_ID).getHeight());
		//split_line_.setPosition(477, 36, Bitmap(BITMAP_FOOTER_LINE_ID).getWidth(), Bitmap(BITMAP_FOOTER_LINE_ID).getHeight());

		icon_phone_.setBitmap(Bitmap(BITMAP_FOOTER_PHONE_ID));
		icon_phone_.setPosition(330, 18, Bitmap(BITMAP_FOOTER_PHONE_ID).getWidth(), Bitmap(BITMAP_FOOTER_PHONE_ID).getHeight());
		//icon_phone_.setPosition(528, 29, Bitmap(BITMAP_FOOTER_PHONE_ID).getWidth(), Bitmap(BITMAP_FOOTER_PHONE_ID).getHeight());

		icon_clock_.setBitmap(Bitmap(BITMAP_FOOTER_CLOCK_ID));
		icon_clock_.setPosition(330, 39, Bitmap(BITMAP_FOOTER_CLOCK_ID).getWidth(), Bitmap(BITMAP_FOOTER_CLOCK_ID).getHeight());
		//icon_clock_.setPosition(528, 63, Bitmap(BITMAP_FOOTER_CLOCK_ID).getWidth(), Bitmap(BITMAP_FOOTER_CLOCK_ID).getHeight());

		text_head_1_.setPosition(25, 27, 38, 17);
		//text_head_1_.setPosition(80 - 10, 44, 62, 28);
		text_head_1_.setAlpha(255);
		text_head_1_.setColor(touchgfx::Color::getColorFromRGB(76, 199, 238));
		text_head_1_.setLinespacing(0);
		text_head_1_.setTypedText(TypedText(T_FOOTER_CURRENCY));

		text_tail_1_.setPosition(93, 27, 55, 17);
		//text_tail_1_.setPosition(149, 44, 88, 28);
		text_tail_1_.setAlpha(255);
		text_tail_1_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		text_tail_1_.setLinespacing(0);
		text_tail_1_.setTypedText(TypedText(T_FOOTER_PER_KWH));

		text_head_2_.setPosition(175, 27, 55, 17);
		//text_head_2_.setPosition(280, 44, 88, 28);
		text_head_2_.setAlpha(255);
		text_head_2_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		text_head_2_.setLinespacing(0);
		text_head_2_.setTypedText(TypedText(T_FOOTER_MAX_DOT));

		text_tail_2_.setPosition(250, 27, 55, 17);
		//text_tail_2_.setPosition(401, 44, 88, 28);
		text_tail_2_.setAlpha(255);
		text_tail_2_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		text_tail_2_.setLinespacing(0);
		text_tail_2_.setTypedText(TypedText(T_FOOTER_KW));
	}

	this->invalidate();
}
