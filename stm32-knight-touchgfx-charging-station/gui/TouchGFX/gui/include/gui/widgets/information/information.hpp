#ifndef INFORMATION_HPP
#define INFORMATION_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class Information : public Container
{
public:
	Information();
	virtual ~Information();

	virtual void initialize(MachineStatus *status);
	virtual void renderGraphic();	
	void setInAnimationDuration(int duration);
	void setOutAnimationDuration(int duration);
	void setDeepTouchable(bool touchable);
	void setInformationXY(int x, int y);
	void setButtonClickedCallback(GenericCallback<const int>& callback);
	void setTransitionInAnimationEndedCallback(GenericCallback<const int>& callback);
	void setTransitionOutAnimationEndedCallback(GenericCallback<const int>& callback);
	void beginTransitionInAnimation();
	void beginTransitionOutAnimation();
protected:
	
private:
	Button info_;
	MachineStatus *ms_;

	int in_animation_duration_;
	int out_animation_duration_;

	void saveContainerStatus();

	GenericCallback<const int>* button_clicked_callback_;
	GenericCallback<const int>* transition_in_animation_ended_callback_;
	GenericCallback<const int>* transition_out_animation_ended_callback_;
		
	Callback<Information, const AbstractButton&> on_button_clicked_;
	void buttonClickedHandler(const AbstractButton& button);
};

#endif /* INFORMATION_HPP */
