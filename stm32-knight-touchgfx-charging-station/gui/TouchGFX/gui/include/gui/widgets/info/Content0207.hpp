#ifndef CONTENT0207_HPP
#define CONTENT0207_HPP

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

class Content0207 : public AbstractContent
{
public:
	Content0207();
	virtual ~Content0207();

	virtual void handleTickEvent();

	virtual void initialize(MachineStatus *status);

private:
	static const uint16_t TEXT_SIZE_3 = 3;
	static const uint16_t TEXT_SIZE_4 = 4;
	static const uint16_t TEXT_SIZE_7 = 7;

	FadeAnimator<TextArea> title_;	
	FadeAnimator<ButtonWithLabel> ok_;
	FadeAnimator<TextArea> tfa_1_;
	FadeAnimator<TextArea> tfa_2_;
	FadeAnimator<TextArea> tfa_3_;
	FadeAnimator<TextAreaWithOneWildcard> tfb_11_;
	Unicode::UnicodeChar tfb_11_buffer_[TEXT_SIZE_3];
	FadeAnimator<TextAreaWithOneWildcard> tfb_12_;
	Unicode::UnicodeChar tfb_12_buffer_[TEXT_SIZE_3];
	FadeAnimator<TextAreaWithOneWildcard> tfb_2_;
	Unicode::UnicodeChar tfb_2_buffer_[TEXT_SIZE_7];
	FadeAnimator<TextAreaWithOneWildcard> tfb_3_;
	Unicode::UnicodeChar tfb_3_buffer_[TEXT_SIZE_7];
	FadeAnimator<TextAreaWithOneWildcard> bc_;
	Unicode::UnicodeChar bc_buffer_[TEXT_SIZE_4];

	Callback<Content0207, const FadeAnimator<TextArea>& > textarea_fade_ended_callback_;
	void textareaFadeEndedHandler(const FadeAnimator<TextArea>& textarea);

	Callback<Content0207, const FadeAnimator<TextAreaWithOneWildcard>& > textareawithonewildcard_fade_ended_callback_;
	void textareawithonewildcardFadeEndedHandler(const FadeAnimator<TextAreaWithOneWildcard>& textarea);

	Callback<Content0207, const FadeAnimator<ButtonWithLabel>& > buttonwithlabel_fade_ended_callback_;
	void buttonwithlabelFadeEndedHandler(const FadeAnimator<ButtonWithLabel>& buttonwithlabel);

	Callback<Content0207, const FadeAnimator<Image>& > image_fade_ended_callback_;
	void imageFadeEndedHandler(const FadeAnimator<Image>& image);

	Callback<Content0207, const AbstractButton&>button_clicked_;
	void buttonClickedHandler(const AbstractButton& source);

	//::[Event]::
	virtual void eventTriggerHandler(const int source);
	virtual void event2();
	virtual void event3();
	virtual void event4();
	virtual void event5();
	virtual void event6();
	virtual void event17();
	virtual void event18();
	//virtual void event10();
	//virtual void event11();
	//virtual void event12();
};

#endif /* CONTENT0207_HPP */
