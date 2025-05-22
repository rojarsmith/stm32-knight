#ifndef CONTENT0205_HPP
#define CONTENT0205_HPP

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

class Content0205 : public AbstractContent
{
public:
	Content0205();
	virtual ~Content0205();

	virtual void handleTickEvent();

	virtual void initialize(MachineStatus *status);

private:
	FadeAnimator<TextArea> title_;
	FadeAnimator<TextArea> body_;
	FadeAnimator<ButtonWithLabel> ok_;

	Callback<Content0205, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<Content0205, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<Content0205, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<Content0205, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	//::[Event]::
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
};

#endif /* CONTENT0205_HPP */
