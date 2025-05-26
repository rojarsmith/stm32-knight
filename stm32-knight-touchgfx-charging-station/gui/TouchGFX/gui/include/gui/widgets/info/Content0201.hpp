#ifndef CONTENT0201_HPP
#define CONTENT0201_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/model/ModelSchema.hpp>
#include <gui/widgets/info/AbstractContent.hpp>

using namespace touchgfx;

class Content0201 : public AbstractContent
{
public:
	Content0201();
	virtual ~Content0201();

	virtual void handleTickEvent();

	virtual void initialize(MachineStatus *status);

private:
	const int HAND_RIGHT_BEGIN_X = 25 + 143;
	const int HAND_RIGHT_END_R_X = 25 + 143 + 21;
	const int HAND_RIGHT_END_L_X = 25 + 143 - 21;
	const int HAND_Y = 137 + 183;
	//const int HAND_RIGHT_BEGIN_X = 40 + 230;
	//const int HAND_RIGHT_END_R_X = 40 + 230 + 35;
	//const int HAND_RIGHT_END_L_X = 40 + 230 - 35;
	//const int HAND_Y = 220 + 294;
	const int HAND_ANIMATION_DURATION = 60;

	FadeAnimator<TextArea> title_;
	FadeAnimator<TextArea> body_;
	FadeAnimator<ButtonWithLabel> ok_;
	//Container viewport_;
	//FadeAnimator<Image> indicator_1_;
	MoveAnimator<FadeAnimator<Image>> hand_;
	//FadeAnimator<Image> indicator_2_;
	//FadeAnimator<Image> indicator_3_;
	FadeAnimator<Image> figure_;

	Callback<Content0201, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<Content0201, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<Content0201, const MoveAnimator<FadeAnimator<Image>>& > image_move_fade_ended_callback_;
	void imageMoveFadeEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image);

	Callback<Content0201, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<Content0201, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	//::[Event]::
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
	virtual void event10();
	virtual void event11();
	virtual void event12();
	virtual void event13();
	virtual void event14();
};

#endif /* CONTENT0201_HPP */
