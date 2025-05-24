#ifndef CAR_ITEM_GROUP_HPP
#define CAR_ITEM_GROUP_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextureMapper.hpp>
#include <gui/model/ModelSchema.hpp>

using namespace touchgfx;

class CarItemGroup : public Container
{
public:
	enum 
	{

	};

	CarItemGroup();
	virtual ~CarItemGroup();

	virtual void handleTickEvent();	

	void initialize(MachineStatus *status);
	//void initialize(MachineStatus *status, bool mirrored);
	void setWeather(WeatherStyle style);	
	void setAnimationStyle(AnimationStyle animation);
	void setOperationPlug(ChargeSocketSelected selected);
protected:
	
private:
	const static int APPEARANCE_WIDTH_ = 384;
	//bool mirr
	MachineStatus *ms_;
	WeatherStyle style_;	
	Image car_;
	TextureMapper wheel_;

	AnimationStyle ani_style_;
	ChargeSocketSelected operation_plug_;
	int animation_duration_;
	float zAngle_;
	float deltaZangle_;

	//GenericCallback<const uint8_t >* setSlideAnimationEndedCallBack;

	//Callback<CarItemGroup, const MoveAnimator<CarItemGroup>& > itemAnimationEndedCallback_;
	//void itemAnimationEndedHandler(const MoveAnimator<CarItemGroup>& source);

	const uint16_t getCarBitmap();
	const uint16_t getWheelBitmap();
	const uint16_t getWheelX();
};

#endif /* CAR_ITEM_GROUP_HPP */
