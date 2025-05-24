#ifndef TITLE_HPP
#define TITLE_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/common/EventManager.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/model/ModelSchema.hpp>
#include <gui/common/Resolution.hpp>

using namespace touchgfx;

class Title : public Container, public Resolution
{
public:
	Title();
	virtual ~Title();

	virtual void initialize(MachineStatus *status);
	virtual void renderGraphic();	
	void setInAnimationDuration(int duration);
	void setOutAnimationDuration(int duration);
	void setSubAnimationDuration(uint16_t duration);
	void setTitleXY(int x, int y);
	void setSubTitleXY(int x, int y);
	void setTransitionInAnimationEndedCallback(GenericCallback<const int>& callback);
	void setTransitionOutAnimationEndedCallback(GenericCallback<const int>& callback);
	void beginTransitionInAnimation();
	void beginTransitionOutAnimation();
	void beginTransitionNextInAnimation(ScreenNumber next);
	void beginTransitionNextOutAnimation(ScreenNumber next);
	void beginSubScreenTransitionAnimation(ScreenNumber next);
	void beginTransitionInAnimationFast();
	void beginTransitionOutAnimationFast();
protected:
	CommonConstant& cc_ = CommonConstant::getInstance();
private:
	FadeAnimator<TextArea> title_;
	FadeAnimator<TextArea> subtitle_;
	FadeAnimator<TextArea> title_prev_;
	FadeAnimator<TextArea> subtitle_prev_;
	MachineStatus *ms_;

	bool isInit_;
	bool isTwoLine_;
	bool isTwoLine_prev_;
	int animation_duration_in_;
	int animation_duration_out_;
	uint16_t animation_duration_sub_;

	void configElement(ScreenNumber id);
	void saveContainerStatus();

	GenericCallback<const int>* transition_in_animation_ended_callback_;
	GenericCallback<const int>* transition_out_animation_ended_callback_;

	Callback<Title, const FadeAnimator<TextArea>& > textarea_fade_animation_ended_callback_;
	void textareaFadeAnimationEndedHandler(const FadeAnimator<TextArea>& source);
};

#endif /* TITLE_HPP */
