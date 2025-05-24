#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/context/Context.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Context::Context()
	:	
	item_fade_animation_ended_callback_(this, &Context::itemFadeAnimationEndedHandler)
{
	line_1_1_.setPosition(0, 0, 350, 60);
	line_1_1_.setAlpha(0);
	line_1_1_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	line_1_1_.setLinespacing(0);
	line_1_1_.setTypedText(TypedText(T_HOME_TITLE));
	tickTxtBuffer[8] = 0;
	Unicode::strncpy(tickTxtBuffer, "TouchEDT", 8);
	line_1_1_.setWildcard(tickTxtBuffer);
	line_1_1_.setFadeAnimationEndedAction(item_fade_animation_ended_callback_);
	add(line_1_1_);
	
	line_2_1_.setPosition(0, 52, 350, 56);
	line_2_1_.setAlpha(0);
	line_2_1_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	line_2_1_.setLinespacing(0);
	line_2_1_.setTypedText(TypedText(T_HOME_SUBTITLE_1));
	line_2_1_.setFadeAnimationEndedAction(item_fade_animation_ended_callback_);
	add(line_2_1_);
}

Context::~Context()
{	
}

void Context::beginAnimation(int alpha, int duration)
{
	line_1_1_.startFadeAnimation(alpha, duration);
	line_2_1_.startFadeAnimation(alpha, duration);
}

void Context::itemFadeAnimationEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& source)
{
}