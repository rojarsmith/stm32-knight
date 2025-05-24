#ifndef CAR_HPP
#define CAR_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <gui/widgets/car/CarItemGroup.hpp>

using namespace touchgfx;

class Car : public Container
{
public:
	Car();
	virtual ~Car();

	virtual void handleTickEvent();	

	void initialize(MachineStatus *status, bool mirrored);

	/**	 
	*
	* @brief Set duration of move animation.
	*
	* @param duration    One way.	 
	*/
	void setAnimationDuration(int duration);
	void beginSlideAnimation(AnimationStyle animation);
	void beginSlideAnimation(AnimationStyle animation, ChargeSocketSelected selected);
	void setSlideAnimationEndedCallback(GenericCallback<const uint8_t>& callback);
protected:
	
private:
	MoveAnimator<CarItemGroup> item_;
	
	bool is_mirrored_;
	int animation_duration_;
	int appearance_width_ = 384;
	int appearance_height_ = 520;
	WeatherStyle style_;
	MachineStatus *ms_;

	GenericCallback<const uint8_t >* setSlideAnimationEndedCallBack;

	Callback<Car, const MoveAnimator<CarItemGroup>& > itemMoveAnimationEndedCallback;
	void itemMoveAnimationEndedHandler(const MoveAnimator<CarItemGroup>& source);
};

#endif /* CAR_HPP */
