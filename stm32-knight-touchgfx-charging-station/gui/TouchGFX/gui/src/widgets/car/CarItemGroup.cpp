#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/car/CarItemGroup.hpp>

CarItemGroup::CarItemGroup()
	:	
	ani_style_(AnimationStyle::SLIDE_IN),
	operation_plug_(ChargeSocketSelected::CHARGE_SOCKET_RIGHT),
	animation_duration_(60),
	zAngle_(0.0f),
	deltaZangle_(0.029f)
{
}

CarItemGroup::~CarItemGroup()
{
	Container::~Container();
}

void CarItemGroup::handleTickEvent()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
	{
		if (AnimationStyle::SLIDE_IN == ani_style_)
		{
			zAngle_ -= deltaZangle_;
			wheel_.updateAngles(0.0F, 0.0F, zAngle_);
		}
		else if (AnimationStyle::SLIDE_OUT == ani_style_)
		{
			zAngle_ += deltaZangle_;
			wheel_.updateAngles(0.0F, 0.0F, zAngle_);
		}
	}
	else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
	{
		if (AnimationStyle::SLIDE_IN == ani_style_)
		{
			zAngle_ += deltaZangle_;
			wheel_.updateAngles(0.0F, 0.0F, zAngle_);
		}
		else if (AnimationStyle::SLIDE_OUT == ani_style_)
		{
			zAngle_ -= deltaZangle_;
			wheel_.updateAngles(0.0F, 0.0F, zAngle_);
		}
	}
}

void CarItemGroup::initialize(MachineStatus *status)
{
	ms_ = status;	

	car_.setBitmap(Bitmap(getCarBitmap()));
	car_.setPosition(0, 0, Bitmap(getCarBitmap()).getWidth(), Bitmap(getCarBitmap()).getHeight());
	add(car_);

	wheel_.setBitmap(Bitmap(getWheelBitmap()));
	int borderWidth = 0;
	int borderHeight = 0;
	int imageWidth = wheel_.getBitmap().getWidth();
	int imageHeight = wheel_.getBitmap().getHeight();
	wheel_.setXY(getWheelX(), 280);
	
	wheel_.setWidth(imageWidth + borderWidth * 2);
	wheel_.setHeight(imageHeight + borderHeight * 2);
	wheel_.setBitmapPosition(borderWidth, borderHeight);
	wheel_.setCameraDistance(300.0f);
	wheel_.setOrigo(wheel_.getBitmapPositionX() + (imageWidth / 2), wheel_.getBitmapPositionY() + (imageHeight / 2), wheel_.getCameraDistance());
	wheel_.setCamera(wheel_.getBitmapPositionX() + (imageWidth / 2), wheel_.getBitmapPositionY() + (imageHeight / 2));
	wheel_.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);
	//wheel_.setBitmap(Bitmap(BITMAP_WHEEL_DAY_ID));
	//wheel_.setPosition(18, 280, Bitmap(BITMAP_WHEEL_DAY_ID).getWidth(), Bitmap(BITMAP_WHEEL_DAY_ID).getHeight());
	add(wheel_);
}

void CarItemGroup::setWeather(WeatherStyle style)
{
	style_ = style;
}

void CarItemGroup::setAnimationStyle(AnimationStyle animation)
{
	ani_style_ = animation;
}

void CarItemGroup::setOperationPlug(ChargeSocketSelected selected)
{
	operation_plug_ = selected;	
}

const uint16_t CarItemGroup::getCarBitmap()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
	{
		if (ms_->ux_weather == WeatherStyle::DAY)
		{
			return BITMAP_CAR_DAY_LEFT_ID;
		}
		else
		{
			return BITMAP_CAR_NIGHT_LEFT_ID;
		}
	}
	else if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
	{
		if (ms_->ux_weather == WeatherStyle::NIGHT)
		{
			return BITMAP_CAR_NIGHT_ID;
		}
	}
	return BITMAP_CAR_DAY_ID;
}

const uint16_t CarItemGroup::getWheelBitmap()
{
	if (ms_->ux_weather == WeatherStyle::NIGHT)
	{
		return BITMAP_WHEEL_NIGHT_ID;
	}
	return BITMAP_WHEEL_DAY_ID;
}

const uint16_t CarItemGroup::getWheelX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
	{		
		return APPEARANCE_WIDTH_ - 240 - 18;
	}	
	return 18;
}