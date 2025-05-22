#ifndef CONTENTE6_HPP
#define CONTENTE6_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/info/AbstractContent.hpp>

using namespace touchgfx;

class ContentE6 : public AbstractContent
{
public:
	ContentE6();
	virtual ~ContentE6();

	virtual void handleTickEvent();	
	
	virtual void initialize(MachineStatus *status);

private:		
	static const uint16_t TEXT_SIZE_21 = 21;

	FadeAnimator<TextArea> title_;
	FadeAnimator<TextAreaWithTwoWildcards> body_;
	Unicode::UnicodeChar body_buffer1_[TEXT_SIZE_21];
	Unicode::UnicodeChar body_buffer2_[TEXT_SIZE_21];
	FadeAnimator<ButtonWithLabel> ok_;

	Callback<ContentE6, const MoveAnimator<FadeAnimator<TextArea>>& > textarea_move_ended_callback_;
	void textareaMoveEndedHandler(const MoveAnimator<FadeAnimator<TextArea>>& textarea);
	Callback<ContentE6, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<ContentE6, const FadeAnimator<TextAreaWithTwoWildcards>& > textareawithtwowildcards_fade_ended_callback_;
	void textareawithtwowildcardsFadeEndedHandler(const FadeAnimator<TextAreaWithTwoWildcards>& textarea);

	Callback<ContentE6, const MoveAnimator<FadeAnimator<ButtonWithLabel>>& > buttonwithlabel_move_ended_callback_;
	void buttonwithlabelMoveEndedHandler(const MoveAnimator<FadeAnimator<ButtonWithLabel>>& buttonwithlabel);
	Callback<ContentE6, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<ContentE6, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	//::[Event]::
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
};

#endif /* CONTENTE6_HPP */
