#ifndef CONTENT0206_HPP
#define CONTENT0206_HPP

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

class Content0206 : public AbstractContent
{
public:
	Content0206();
	virtual ~Content0206();

	virtual void handleTickEvent();

	virtual void initialize(MachineStatus *status);

private:
	FadeAnimator<TextArea> title_;
	FadeAnimator<TextArea> body_;
	FadeAnimator<ButtonWithLabel> ok_;
	//Container viewport_;
	FadeAnimator<Image> indicator_1_;
	FadeAnimator<Image> indicator_2_;
	FadeAnimator<Image> indicator_3_;
	FadeAnimator<Image> figure_;

	Callback<Content0206, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<Content0206, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<Content0206, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<Content0206, const AbstractButton&>button_clicked_;
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
};

#endif /* CONTENT0206_HPP */
