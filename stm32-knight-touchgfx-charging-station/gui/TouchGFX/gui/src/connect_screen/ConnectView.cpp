#include <gui/connect_screen/ConnectView.hpp>
#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

ConnectView::ConnectView() :
	socket_right_(false, ms_),
	socket_left_(true, ms_),
	plugin_right_(false, ms_),
	plugin_left_(true, ms_),
	plug_status_(0),
	plug_status_prv_(0),
	event_trigger_callback_(this, &ConnectView::eventTriggerHandler),
	checking_open_end_callback_(this, &ConnectView::checkingOpenEndHandler),
	checking_hide_end_callback_(this, &ConnectView::checkinghideEndHandler),
	checking_close_end_callback_(this, &ConnectView::checkingCloseEndHandler),
	backto_button_clicked_callback_(this, &ConnectView::backtoButtonClickedHandler),
	button_clicked_callback_(this, &ConnectView::buttonClickedHandler),
	carMoveAnimationEndedCallback(this, &ConnectView::carMoveAnimationEndedHandler),
	message_open_end_callback_(this, &ConnectView::messageOpenEndHandler),
	message_close_end_callback_(this, &ConnectView::messageCloseEndHandler),
	footerMoveAnimationEndedCallback(this, &ConnectView::footerMoveAnimationEndedHandler)
{
    plug_status_prv_ = ms_->ux0400_plug_right_status;
}

void ConnectView::setupScreen()
{
	BaseView::setupScreen();

	scenario_prev_ = ms_->ux_screen_id_current;

	//Element
	wallpaper_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	wallpaper_.initialize(ms_->ux_weather, ms_->ux_weather_prev);
	add(wallpaper_);

	//Element
	pole_.setBitmaps(Bitmap(getPoleBitmapSmall()), Bitmap(getPoleBitmapLarge()));
	pole_.setPosition(
		ms_->pole_previous_x,
		getScaledY(ms_->pole_previous_y),
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);
	add(pole_);

	//Element
	socket_right_.initialize(ms_, false);
	socket_right_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	add(socket_right_);

	//Element
	socket_left_.initialize(ms_, true);
	socket_left_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	add(socket_left_);

	//Element
	car_.setPosition(getCarX(), 388, 384, 520);
	car_.initialize(ms_, getCarIsMirrored());
	car_.setSlideAnimationEndedCallback(carMoveAnimationEndedCallback);
	add(car_);

	//Element
	plugin_right_.initialize(ms_, false);
	plugin_right_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	add(plugin_right_);

	//Element
	plugin_left_.initialize(ms_, true);
	plugin_left_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
	add(plugin_left_);

	//Element
	plugin_out_.setAlpha(0);
	plugin_out_.setVisible(false);
	add(plugin_out_);

	//Element
	title_.setPosition(cc_.TitleX, getScaledY(cc_.TitleY), cc_.TitleWidth, cc_.TitleHeight);
	title_.initialize(ms_);
	title_.setInAnimationDuration(ANIMATION_TRANSITION_IN_DURATION);
	title_.setOutAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	add(title_);

	//Element
	footer_.initialize(ms_);
	uint16_t foot_reduce_y = 72; // 800x480
	//footer_.setPosition(0, HAL::DISPLAY_HEIGHT - foot_reduce_y, HAL::DISPLAY_WIDTH, foot_reduce_y);
	footer_.setPosition(0, getFixedDisplayHeight() - foot_reduce_y - ratio_height_, HAL::DISPLAY_WIDTH, foot_reduce_y); // 
	//footer_.setPosition(0, getFixedDisplayHeight() - 72, HAL::DISPLAY_WIDTH, 72);
	//footer_.setPosition(0, getFixedDisplayHeight() - 116, HAL::DISPLAY_WIDTH, 116);
	//footer_.setItemXY(0, 0);
	add(footer_);

	//Element
	information_.setPosition(30, 30, 70, 70);
	information_.initialize(ms_);
	information_.setButtonClickedCallback(button_clicked_callback_);
	add(information_);

	//Element
	language_.initialize(ms_);
	language_.setAnimationDuration(60);
	language_.setPosition(120, 33, 386, 64);
	language_.lock();
	add(language_);

	//Element
	backto_.setPosition(668, 30, 70, 70);
	backto_.initialize(ms_);
	backto_.setButtonClickedCallback(backto_button_clicked_callback_);
	add(backto_);

	//Element
	checking_.initialize(ms_);
	checking_.setPosition(-101, -101, 102, 102);
	checking_.setOpenCompletedCallback(checking_open_end_callback_);
	checking_.setHideCompletedCallback(checking_hide_end_callback_);
	checking_.setCloseCompletedCallback(checking_close_end_callback_);
	checking_.setVisible(false);
	add(checking_);

	setMessageAction(&message_open_end_callback_, &message_close_end_callback_);

	BaseView::afterSetupScreen();

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addAlwaysKeepEvent(1, 1);
	em_.addAlwaysKeepEvent(2, 30);
	em_.addOneTimeEvent(EVENT_TRAN_IN);
	em_.addCountDownEvent(EVENT_TRAN_IN_END, cc_.ScreenTranInDuration + 60 + 1);
}

void ConnectView::tearDownScreen()
{
	ms_->pole_previous_x = pole_.getX();
	ms_->pole_previous_y = pole_.getY();
	ms_->pole_previous_width = pole_.getWidth();
	ms_->pole_previous_height = pole_.getHeight();

	BaseView::tearDownScreen();
}

void ConnectView::backtoButtonClickedHandler(const int source)
{
	if (0 >= count_filter_)
	{
		count_filter_ = 30;
	}
	else
	{
		return;
	}

	ms_->ux_return_button_clicked = true;

	if (ScreenNumber::SCENARIO_4_1 == scenario_prev_ ||
		ScreenNumber::SCENARIO_4_2 == scenario_prev_ || 
		ScreenNumber::SCENARIO_4_3 == scenario_prev_)
	{
		em_.addOneTimeEvent(23);
		em_.addCountDownEvent(24, cc_.ScreenTranOutDuration + 1);
	}
	else
	{
		em_.addOneTimeEvent(20);
		em_.addCountDownEvent(EVENT_TRAN_OUT, cc_.ScreenTranOutDuration);
		em_.addCountDownEvent(22, cc_.ScreenTranOutDuration * 2 + 1);
	}

	sendCommand(scenario_prev_);
}

void ConnectView::buttonClickedHandler(const int source)
{
	if (0 >= count_filter_)
	{
		count_filter_ = 30;
	}
	else
	{
		return;
	}

	ms_->ux_popup_trigger_ = true;

	if (!ms_->popup_opened)
	{
		ms_->ux_popup_number = MessageNumber::MESSAGE_51;
	}
	else
	{
		ms_->ux_popup_number = MessageNumber::MESSAGE_0;
	}
}

void ConnectView::checkingOpenEndHandler(const int source)
{
	em_.addOneTimeEvent(EVENT_AFTER_CHECKING_OPENED);
}

void ConnectView::checkinghideEndHandler(const int source)
{
}

void ConnectView::checkingCloseEndHandler(const int source)
{
	em_.addOneTimeEvent(EVENT_AFTER_CHECKING_CLOSED);
}

void ConnectView::messageOpenEndHandler(const int source)
{
	completedCommand();
	setMask(MaskList::INFO_MASK, true);
}

void ConnectView::messageCloseEndHandler(const int source)
{
	if (source == (int)ReturnValue::RETURN_OK)
	{
		em_.addOneTimeEvent(47);
	}
	else
	{
		em_.addOneTimeEvent(47);
	}

	completedCommand();
	setMask(MaskList::FULL_MASK, false);
}

void ConnectView::carMoveAnimationEndedHandler(const uint8_t source)
{
	animation_locker_--;
}

void ConnectView::footerMoveAnimationEndedHandler(const MoveAnimator<Footer>& source)
{
	animation_locker_--;
}

void ConnectView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 1:
		event1();
		break;
	case 2:
		event2(); //
		break;
	case EVENT_RENDER_GRAPHIC:
		eventRenderGraphic();
		break;
		//case 9:
		  //	event9();
		  //	break;
	case EVENT_TRAN_IN:
		eventTranIn(); //
		break;
	case EVENT_TRAN_IN_END:
		eventTranInEnd(); //
		break;
	case 12:
		event0500(); //
		break;
		//case 13:
		//	event13(); //Out Completed.
		//	break;
	case 15:
		event15();
		break;
	case 16:
		event16(); //
		break;
	case 17:
		event17(); //
		break;
	case EVENT_AFTER_CHECKING_OPENED:
		eventAfterCheckingOpened();
		break;
	case EVENT_AFTER_CHECKING_CLOSED:
		eventAfterCheckingClosed();
		break;
	case 20:
		event20(); //
		break;
	case EVENT_TRAN_OUT:
		eventTranOut(); //
		break;
	case 22:
		event22(); //
		break;
	case 23:
		event23(); //
		break;
	case 24:
		event24(); //
		break;
	case 25:
		event25();
		break;
	case 26:
		eventTranOutEnd();
		break;
	case EVENT_OPEN_CHECKING:
		eventOpenChecking();
		break;
	case EVENT_CLOSE_CHECKING:
		eventCloseChecking();
		break;
	case 43:
		event43();
		break;
	case 45:
		event45();
		break;
	case 46:
		event46();
		break;
	case 47:
		event47();
		break;
	case 48:
		event48();
		break;
	case 49:
		event49();
		break;
	}
}

void ConnectView::event1()
{
	if (UXCommandStatus::UX_COMMAND_ON == ms_->ux_output_command_trigger) return;

	if (ms_->ux_popup_trigger_ != ms_->ux_popup_trigger_prev_ &&
		1 == ms_->ux_popup_trigger_prev_)
	{
		if (!ms_->popup_opened)
		{
			setMessageAction(&message_open_end_callback_, &message_close_end_callback_);
			em_.addOneTimeEvent(45);
		}
		else
		{
			em_.addOneTimeEvent(46);
		}

		ms_->ux_popup_trigger_ = false;
	}
	else if (ms_->ux_popup_number != ms_->ux_popup_number_prev)
	{
		if (!ms_->popup_opened)
		{
			setMessageAction(&message_open_end_callback_, &message_close_end_callback_);
			em_.addOneTimeEvent(45);
		}
	}

	if (ms_->ux_open_checked_prev != ms_->ux_open_checked &&
		1 == ms_->ux_open_checked)
	{
		title_.setSubAnimationDuration(cc_.SubScreenTranDuration);
		title_.beginSubScreenTransitionAnimation(ScreenNumber::SCENARIO_5_2);
		sendCommand(ScreenNumber::SCENARIO_5_2);
		em_.addOneTimeEvent(EVENT_OPEN_CHECKING);
	}

	if (ms_->ux_payment_checked_prev != ms_->ux_payment_checked &&
		1 == ms_->ux_payment_checked)
	{
		title_.setSubAnimationDuration(cc_.SubScreenTranDuration);
		title_.beginSubScreenTransitionAnimation(ScreenNumber::SCENARIO_5_3);
		sendCommand(ScreenNumber::SCENARIO_5_3);
		em_.addOneTimeEvent(EVENT_CLOSE_CHECKING);
	}
}

void ConnectView::event2()
{
}

void ConnectView::eventRenderGraphic()
{
	information_.renderGraphic();
	title_.renderGraphic();
	backto_.renderGraphic();
}

void ConnectView::event9()
{

}

void ConnectView::eventTranIn()
{
	title_.setInAnimationDuration(cc_.ScreenTranInDuration);
	title_.beginTransitionNextInAnimation(ms_->ux_screen_id_next);
	car_.setAnimationDuration(cc_.ScreenTranInDuration);
	car_.beginSlideAnimation(AnimationStyle::SLIDE_IN);

	footer_.beginSlideAnimation(AnimationStyle::SLIDE_IN);
}

void ConnectView::eventTranInEnd()
{
	setMask(MaskList::FULL_MASK, false);
	completedCommand();

	eventRenderGraphic();
}

void ConnectView::event0500()
{
	if (ms_->ux_plugin_lock_into_car != ms_->ux_plugin_lock_into_car_prev)
	{
		if (1 == ms_->ux_plugin_lock_into_car &&
			0 == ms_->ux_plugin_lock_into_car_prev)
		{
			sendCommand(ScreenNumber::SCENARIO_5_2);
			checking_.open();
		}
	}
}

void ConnectView::event15()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		plugin_left_.setVisible(true);
		plugin_out_.setVisible(true);

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_LEFT_BLACK_ID));
		plugin_out_.setXY(768 - 207 - 327, 257);
		plugin_out_.startFadeAnimation(0, ANIMATION_TRANSITION_IN_DURATION);
		plugin_left_.beginAnimation(768 - 178 - 129, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);
	}
	else
	{
		plugin_right_.setVisible(true);
		plugin_out_.setVisible(true);

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID));
		plugin_out_.setXY(207, 257);
		plugin_out_.startFadeAnimation(0, ANIMATION_TRANSITION_IN_DURATION);
		plugin_right_.beginAnimation(178, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);
	}
}

void ConnectView::event16()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		plugin_left_.setVisible(true);
		plugin_out_.setVisible(true);

		checking_.close();

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_LEFT_BLACK_ID));
		plugin_out_.setXY(768 - 207 - 327, 257);
		plugin_out_.startFadeAnimation(255, ANIMATION_TRANSITION_IN_DURATION);
		plugin_left_.beginAnimation(768 - 178 - 129, 257, 129, 593, 0, ANIMATION_TRANSITION_IN_DURATION);
	}
	else
	{
		plugin_right_.setVisible(true);
		plugin_out_.setVisible(true);

		checking_.close();

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID));
		plugin_out_.setXY(207, 257);
		plugin_out_.startFadeAnimation(255, ANIMATION_TRANSITION_IN_DURATION);
		plugin_right_.beginAnimation(178, 257, 129, 593, 0, ANIMATION_TRANSITION_IN_DURATION);
	}

	em_.addLockCountEvent(17, ANIMATION_TRANSITION_IN_DURATION * 4);
}

void ConnectView::event17()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		plugin_left_.setVisible(false);
		plugin_out_.setVisible(true);

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_LEFT_BLUE_ID));
		plugin_out_.setXY(768 - 207 - 327, 257);
		plugin_out_.invalidate();
	}
	else
	{
		plugin_right_.setVisible(false);
		plugin_out_.setVisible(true);

		plugin_out_.setBitmap(Bitmap(BITMAP_PLUGIN_OUT_RIGHT_BLUE_ID));
		plugin_out_.setXY(207, 257);
		plugin_out_.invalidate();
	}
}

void ConnectView::eventAfterCheckingOpened()
{
	completedCommand();
}

void ConnectView::eventAfterCheckingClosed()
{
	completedCommand();
}

void ConnectView::event20()
{
	if (true == checking_.isVisible())
	{
		checking_.hide();
	}
}

void ConnectView::eventTranOut()
{
	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	title_.beginTransitionNextOutAnimation(ms_->ux_screen_id_next);

	car_.beginSlideAnimation(AnimationStyle::SLIDE_OUT);

	int pole_width = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
	int pole_height = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	pole_.setPosition(
		ms_->pole_previous_x,
		ms_->pole_previous_y,
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);
	pole_.startZoomAndMoveAnimation(
		getPoleReturnX(),
		-407,
		pole_width,
		pole_height,
		cc_.ScreenTranOutDuration,
		getPoleReturnZoomMode(),
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);

	socket_right_.beginAnimation(cc_.SocketHomeXR, cc_.SocketHomeY, cc_.SocketHomeW, cc_.SocketHomeH, 255, cc_.ScreenTranOutDuration);
	socket_left_.beginAnimation(cc_.SocketHomeXL, cc_.SocketHomeY, cc_.SocketHomeW, cc_.SocketHomeH, 255, cc_.ScreenTranOutDuration);

	//int shift_r = 31 * 3;
	//int shift_l = -shift_r;
	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	bool is_out_l = ms_->ux_plugin_in_out_status_left;

	if (!is_out_r)
	{
		plugin_right_.beginAnimation(510, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranOutDuration);
	}
	else
	{
		plugin_right_.beginAnimation(510 + 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranOutDuration);
	}

	if (!is_out_l)
	{
		plugin_left_.beginAnimation(-129, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranOutDuration);
	}
	else
	{
		plugin_left_.beginAnimation(-129 - (981 - 387) - 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranOutDuration);
	}

	footer_.setAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	footer_.beginSlideAnimation(AnimationStyle::SLIDE_OUT);
}

void ConnectView::event22()
{
	changeScreen(ScreenNumber::SCREEN_PAYMENT);
}

void ConnectView::event23()
{
	title_.beginTransitionOutAnimation();

	//car_.beginSlideAnimation(AnimationStyle::SLIDE_OUT, (ChargeSocket)ms_->operation_charge_socket_selected);
	car_.beginSlideAnimation(AnimationStyle::SLIDE_OUT);

	int pole_width = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
	int pole_height = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	pole_.startZoomAndMoveAnimation(
		305, 214, //144 + 80, -407, 
		(int)(pole_width * 0.33), (int)(pole_height * 0.33),
		ANIMATION_TRANSITION_OUT_DURATION,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);

	socket_right_.beginAnimation(166 + 249, 482, 32, 60, 255, ANIMATION_TRANSITION_IN_DURATION);
	socket_left_.beginAnimation(70 + 249, 482, 32, 60, 255, ANIMATION_TRANSITION_IN_DURATION);
	//plugin_right_.beginAnimation(178 + 249, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);
	//plugin_left_.beginAnimation(-36 + 249, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);

	int shift_r = 31 * 3;
	int shift_l = -shift_r;
	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	bool is_out_l = ms_->ux_plugin_in_out_status_left;

	if (!is_out_r)
	{
		plugin_right_.beginAnimation(178 + 249, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);
	}
	else
	{
		plugin_right_.beginAnimation(178 + 249 + 31, 257, 327, 585, 255, ANIMATION_TRANSITION_IN_DURATION);
	}

	if (!is_out_l)
	{
		plugin_left_.beginAnimation(-36 + 249, 257, 129, 593, 255, ANIMATION_TRANSITION_IN_DURATION);
	}
	else
	{
		plugin_left_.beginAnimation(-36 + 249 + (-327 - 31 + 129), 257, 327, 585, 255, ANIMATION_TRANSITION_IN_DURATION);
	}

	footer_.setAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	footer_.beginSlideAnimation(AnimationStyle::STATIC_IN);
}

void ConnectView::event24()
{
	changeScreen(ScreenNumber::SCREEN_PAY_RFID);
}

void ConnectView::event25()
{
	if (MessageNumber::MESSAGE_54 == message_->getInitializeType())
	{
		changeScreen(ScreenNumber::SCREEN_HOME);
	}
	else if (MessageNumber::MESSAGE_27 == message_->getInitializeType())
	{
		changeScreen(ScreenNumber::SCREEN_HOME);
	}
}

void ConnectView::eventTranOutEnd()
{
}

void ConnectView::eventOpenChecking()
{
	checking_.setXY(getCheckingX(), 527);
	checking_.setVisible(true);
	checking_.open();
}

void ConnectView::eventCloseChecking()
{
	checking_.setXY(getCheckingX(), 527);
	checking_.setVisible(true);
	checking_.close();
}

#pragma region get style resource
const bool ConnectView::getCarIsMirrored()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return true;
	}
	return false;
}

//const AnimationStyle ConnectView::getCarAnimationStyle()
//{
//	if (ChargeSocket::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
//	{
//		return AnimationStyle::SLIDE_OUT;
//	}
//	return AnimationStyle::SLIDE_IN;
//}

const ChargeSocketSelected ConnectView::getCarChargeSocket()
{
	return (ChargeSocketSelected)ms_->operation_charge_socket_selected;
}

const int16_t ConnectView::getCarX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 0;
	}
	return 384;
}

const int16_t ConnectView::getPoleReturnX()
{
	if (ScreenNumber::SCREEN_PAY_RFID == ms_->ux_screen_id_previous)
	{
		return POLE_SCREEN_40;
		//if (ChargeSocket::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		//{
		//	//return 199;
		//}
		//else
		//{

		//}
	}
	//else
	//{
	//	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	//	{
	//		//return POLE_SCREEN_30_LEFT_X;
	//		return 84;
	//	}
	//}
	return 144;
}
const ZoomAnimationImage::ZoomMode ConnectView::getPoleReturnZoomMode()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return ZoomAnimationImage::FIXED_LEFT_AND_TOP;
	}
	return ZoomAnimationImage::FIXED_LEFT_AND_TOP;
}

const int16_t ConnectView::getCheckingX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 199;
	}
	return 469;
}
#pragma endregion get style resource
