#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace touchgfx;

class Context : public Container
{
public:
	Context();
	virtual ~Context();
	
	void beginAnimation(int alpha, int duration);
protected:
	
private:
	FadeAnimator<TextAreaWithOneWildcard> line_2_1_;

	FadeAnimator<TextAreaWithOneWildcard> line_1_1_;
	static const uint16_t TICKTXT_SIZE = 9;
	Unicode::UnicodeChar tickTxtBuffer[TICKTXT_SIZE];

	Callback<Context, const FadeAnimator<TextAreaWithOneWildcard>& > item_fade_animation_ended_callback_;
	void itemFadeAnimationEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& source);
};

#endif /* CONTEXT_HPP */
