#ifndef CONTENTE3_HPP
#define CONTENTE3_HPP

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

class ContentE3 : public AbstractContent
{
public:
	ContentE3();
	virtual ~ContentE3();

	virtual void handleTickEvent();	
	
	virtual void initialize(MachineStatus *status);

private:		
	FadeAnimator<TextArea> title_;
	FadeAnimator<TextArea> body_;
	FadeAnimator<ButtonWithLabel> ok_;

	Callback<ContentE3, const MoveAnimator<FadeAnimator<TextArea>>& > textarea_move_ended_callback_;
	void textareaMoveEndedHandler(const MoveAnimator<FadeAnimator<TextArea>>& textarea);
	Callback<ContentE3, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<ContentE3, const MoveAnimator<FadeAnimator<ButtonWithLabel>>& > buttonwithlabel_move_ended_callback_;
	void buttonwithlabelMoveEndedHandler(const MoveAnimator<FadeAnimator<ButtonWithLabel>>& buttonwithlabel);
	Callback<ContentE3, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<ContentE3, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	//::[Event]::
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
};

#endif /* CONTENTE3_HPP */
