#include <gui/widgets/context/ContextNameValue.hpp>
#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

ContextNameValue::ContextNameValue()
{
	name_.setPosition(0, 0, 200, 20);
	name_.setAlpha(200);
	name_.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	name_.setLinespacing(0);
	name_.setTypedText(TypedText(T_DBG_NVS_ROLI18LL));
	add(name_);
	
	value_.setPosition(200, 0, 100, 20);
	value_.setAlpha(200);
	value_.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
	value_.setLinespacing(0);
	value_.setTypedText(TypedText(T_DBG_NVS_ROLI18RL));
	add(value_);
}

ContextNameValue::~ContextNameValue()
{	
}

void ContextNameValue::initialize(char * name, float value)
{
	Unicode::strncpy(name_txt_buffer_, name, 20);
	name_.setWildcard(name_txt_buffer_);
	name_.invalidate();

	Unicode::snprintfFloat(value_txt_buffer_, 10, "%f", value);
	value_.setWildcard(value_txt_buffer_);
	value_.invalidate();
}

void ContextNameValue::updateValue(float value)
{
	Unicode::snprintfFloat(value_txt_buffer_, 10, "%f", value);
	value_.setWildcard(value_txt_buffer_);
	value_.invalidate();
}

void ContextNameValue::updateValue(int value)
{
	Unicode::snprintf(value_txt_buffer_, 10, "%i", value);
	value_.setWildcard(value_txt_buffer_);
	value_.invalidate();
}