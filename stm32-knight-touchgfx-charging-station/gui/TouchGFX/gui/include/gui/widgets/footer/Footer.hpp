#ifndef FOOTER_HPP
#define FOOTER_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/widgets/footer/FooterItemGroup.hpp>

using namespace touchgfx;

class Footer : public Container
{
public:
	Footer();
	virtual ~Footer();

	//virtual void handleTickEvent();	

	//void bindMachineStatus();
	void initialize(MachineStatus *status);
	virtual void renderGraphic();
	//void setLayout(FooterLayout layout);
	//void setStyle(WeatherStyle style);
	void setAnimationDuration(int duration);
	void setItemXY(int x, int y);
	//void setViewData(MachineStatusProperties * data);
	//void beginAnimation(int y);
	void beginSlideAnimation(AnimationStyle animation);
	void setSlideAnimationEndedCallback(GenericCallback<const uint8_t>& callback);
protected:
	
private:
	const static int APPEARANCE_HEIGHT = 72; // 800x480
	//const static int APPEARANCE_HEIGHT = 116;

	MoveAnimator<FooterItemGroup> footer_;
	//FooterLayout layout_;
	//WeatherStyle style_;
	MachineStatus *ms_;
	   	 
	int animation_duration_;
	//int appearance_height_ = 116;

	void saveElementStatus();

	GenericCallback<const uint8_t >* slide_animation_ended_callback_;

	Callback<Footer, const MoveAnimator<FooterItemGroup>& > itemMoveAnimationEndedCallback;
	void itemMoveAnimationEndedHandler(const MoveAnimator<FooterItemGroup>& source);
};

#endif /* FOOTER_HPP */
