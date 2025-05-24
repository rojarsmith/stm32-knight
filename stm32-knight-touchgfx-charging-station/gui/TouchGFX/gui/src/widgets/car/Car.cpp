#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/car/Car.hpp>

Car::Car()
	:	
	ms_(0),
	is_mirrored_(false),
	animation_duration_(60),
	itemMoveAnimationEndedCallback(this, &Car::itemMoveAnimationEndedHandler)
{
}

Car::~Car()
{
	Container::~Container();
}

void Car::handleTickEvent()
{	
}

void Car::initialize(MachineStatus *status, bool mirrored)
{
	ms_ = status;
	is_mirrored_ = mirrored;

	item_.initialize(status);
	item_.setOperationPlug((ChargeSocketSelected)ms_->operation_charge_socket_selected);

	item_.setPosition(
		appearance_width_, 0,
		appearance_width_, appearance_height_);
	item_.setMoveAnimationEndedAction(itemMoveAnimationEndedCallback);	
	add(item_);
}

void Car::setAnimationDuration(int duration)
{
	animation_duration_ = duration;
}

void Car::beginSlideAnimation(AnimationStyle animation)
{
	item_.setAnimationStyle(animation);
	item_.setOperationPlug((ChargeSocketSelected)ms_->operation_charge_socket_selected);

	switch (animation)
	{
	case SLIDE_IN:
		if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
		{
			item_.setXY(appearance_width_, 0);
			item_.startMoveAnimation(0, 0, animation_duration_, EasingEquations::linearEaseIn);
		}
		else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
		{
			item_.setXY(-appearance_width_, 0);
			item_.startMoveAnimation(0, 0, animation_duration_, EasingEquations::linearEaseIn);
		}
		break;
	case SLIDE_OUT:
		if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
		{
			item_.setXY(0, 0);
			item_.startMoveAnimation(appearance_width_, 0, animation_duration_, EasingEquations::linearEaseIn);
			break;
		}
		else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == (ChargeSocketSelected)ms_->operation_charge_socket_selected)
		{
			item_.setXY(0, 0);
			item_.startMoveAnimation(-appearance_width_, 0, animation_duration_, EasingEquations::linearEaseIn);
			break;
		}
	default:
		break;
	}
}

void Car::beginSlideAnimation(AnimationStyle animation, ChargeSocketSelected selected)
{
	item_.setAnimationStyle(animation);
	item_.setOperationPlug(selected);

	switch (animation)
	{
	case SLIDE_IN:
		item_.setXY(appearance_width_, 0);		
		item_.invalidate();
		item_.startMoveAnimation(0, 0, animation_duration_, EasingEquations::linearEaseIn);
		break;
	case SLIDE_OUT:
		item_.setXY(0, 0);
		item_.invalidate();
		item_.startMoveAnimation(appearance_width_, 0, animation_duration_, EasingEquations::linearEaseIn);
		break;
	default:
		break;
	}
}

void Car::setSlideAnimationEndedCallback(GenericCallback<const uint8_t>& callback)
{
	setSlideAnimationEndedCallBack = &callback;
}

void Car::itemMoveAnimationEndedHandler(const MoveAnimator<CarItemGroup>& source)
{
	uint8_t id = 0;
	setSlideAnimationEndedCallBack->execute(id);
}