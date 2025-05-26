#include <gui/home_screen/HomeView.hpp>

#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

HomeView::HomeView()
    :
	socket_right_(false, ms_),
	socket_left_(true, ms_),
	plugin_right_(false, ms_),
	plugin_left_(true, ms_),
	button_clicked_callback_(this, &HomeView::buttonClickedHandler),
	poleAnimationEndedCallback(this, &HomeView::poleAnimationEndedHandler),
	begin_animation_callback_(this, &HomeView::beginAnimationHandler),
	open_container_callback_(this, &HomeView::openContainerCallback),
	close_container_callback_(this, &HomeView::closeContainerCallback),
	message_open_end_callback_(this, &HomeView::messageOpenEndHandler),
	message_close_end_callback_(this, &HomeView::messageCloseEndHandler),
	plug_not_in_socket_callback_(this, &HomeView::plugNotInSocketHandler),
	bar_move_out_animation_end_callback_(this, &HomeView::barMoveOutAnimationEndHandler),
	event_trigger_callback_(this, &HomeView::eventTriggerHandler)
{

}

HomeView::~HomeView()
{
	BaseView::~BaseView();

	ms_->pole_previous_x = pole_.getX();
	ms_->pole_previous_y = pole_.getY();
	ms_->pole_previous_width = pole_.getWidth();
	ms_->pole_previous_height = pole_.getHeight();
}

void HomeView::setupScreen()
{
    HomeViewBase::setupScreen();

	ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_NONE;

	//Element	
	wallpaper_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
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
	pole_.setAnimationEndedCallback(poleAnimationEndedCallback);
	add(pole_);

	//Element
	socket_right_.initialize(ms_, false);
	socket_right_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(socket_right_);

	//Element
	socket_left_.initialize(ms_, true);
	socket_left_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(socket_left_);

	//Element
	plugin_right_.initialize(ms_, false);
	plugin_right_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(plugin_right_);

	//Element
	plugin_left_.initialize(ms_, true);
	plugin_left_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(plugin_left_);

	//Item
	title_.setPosition(cc_.TitleX, getScaledY(cc_.TitleY), cc_.TitleWidth, cc_.TitleHeight);
	title_.initialize(ms_);
	title_.setInAnimationDuration(ANIMATION_TRANSITION_IN_DURATION);
	title_.setOutAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	add(title_);

	//Element
	int16_t socket_slider_y = 468;
	//int16_t socket_slider_y = 750;
	int16_t socket_slider_h = 171;
	//int16_t socket_slider_y = 100 + 174;
	socket_slider_.initialize(ms_);
	socket_slider_.setPosition(0, getScaledY(socket_slider_y), HAL::DISPLAY_WIDTH, socket_slider_h);
	socket_slider_.setPlugNotInSocketCallback(plug_not_in_socket_callback_);
	socket_slider_.setBarMoveOutAnimationEndCallback(bar_move_out_animation_end_callback_);
	socket_slider_.setTouchable(true);
	add(socket_slider_);

	//Element
	information_.setPosition(18, getScaledY(18), 43, 43);
	//information_.setPosition(30, 30, 70, 70);
	information_.initialize(ms_);
	information_.setDeepTouchable(true);
	information_.setButtonClickedCallback(button_clicked_callback_);
	add(information_);

	//Element
	language_.initialize(ms_);
	language_.setAnimationDuration(15);
	language_.setPosition(75, getScaledY(20), 241, 40);
	//language_.setPosition(120, 33, 386, 64);
	language_.setBeginAnimationCallback(begin_animation_callback_);
	language_.setOpenContainerCallback(open_container_callback_);
	language_.setCloseContainerCallback(close_container_callback_);
	add(language_);

	//Element
	lang_mask_.setPosition(0, getScaledY(0), HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	lang_mask_.setAlpha(0);
	lang_mask_.setVisible(false);
	lang_mask_.setTouchable(false);
	add(lang_mask_);

	//Element
	uint16_t foot_reduce_y = 72; // 800x480
	footer_.initialize(ms_);
	//footer_.setPosition(0, HAL::DISPLAY_HEIGHT - foot_reduce_y, HAL::DISPLAY_WIDTH, foot_reduce_y);
	footer_.setPosition(0, getFixedDisplayHeight() - foot_reduce_y - ratio_height_, HAL::DISPLAY_WIDTH, foot_reduce_y); // 
	footer_.setAnimationDuration(ANIMATION_TRANSITION_IN_DURATION);
	add(footer_);

#ifdef SIMULATOR
	em_.addCountDownEvent(39, 60);

	char selector_x_name_[] = "selector_x_";
	float selector_x_v_ = 00.00f;
	selector_x_.setPosition(0, getScaledY(125), 187, 12);
	//selector_x_.setPosition(0, 200, 300, 20);
	selector_x_.initialize(selector_x_name_, selector_x_v_);
	add(selector_x_);

	char selector_vx_name_[] = "selector_vx_";
	float selector_vx_v_ = 00.00f;
	selector_vx_.setPosition(0, getScaledY(137), 187, 12);
	//selector_vx_.setPosition(0, 220, 300, 20);
	selector_vx_.initialize(selector_vx_name_, selector_vx_v_);
	add(selector_vx_);
#endif

	setMessageAction(&message_open_end_callback_, &message_close_end_callback_);

	BaseView::afterSetupScreen();

	setMask(MaskList::FULL_MASK, true);

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addAlwaysKeepEvent(1, 1);
	em_.addAlwaysKeepEvent(2, 30);
	em_.addOneTimeEvent(EVENT_RENDER_GRAPHIC);
	em_.addOneTimeEvent(EventList::EVENT_TRAN_IN);
	em_.addCountDownEvent(EventList::EVENT_TRAN_IN_END, cc_.ScreenTranInDuration);
}

void HomeView::tearDownScreen()
{
	ms_->pole_previous_x = pole_.getX();
	ms_->pole_previous_y = pole_.getY();
	ms_->pole_previous_width = pole_.getWidth();
	ms_->pole_previous_height = pole_.getHeight();

    HomeViewBase::tearDownScreen();
}

void HomeView::buttonClickedHandler(const int source)
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

	if (!ms_->popup_opened && nullptr == message_)
	{
		ms_->ux_popup_number = MessageNumber::MESSAGE_21;
	}
	else
	{
		ms_->ux_popup_number = MessageNumber::MESSAGE_0;
	}
}

void HomeView::poleAnimationEndedHandler(const ZoomAnimationImage& image)
{
}

void HomeView::plugNotInSocketHandler(ChargeSocketSelected socket)
{
	socket_ret1_ = socket;
	em_.addOneTimeEvent(EVENT_PLUG_NOT_IN_SOCKET);
}

void HomeView::barMoveOutAnimationEndHandler(ChargeSocketSelected socket)
{
	//if (ms_->ux_drag_selector_vx > 220)
	if (ms_->ux_drag_selector_vx > 137)
	{
		ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_RIGHT;
	}
	//else if (ms_->ux_drag_selector_vx < -220)
	else if (ms_->ux_drag_selector_vx < -137)
	{
		ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_LEFT;
	}
	else
	{
		ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_NONE;
	}

	em_.addOneTimeEvent(EVENT_TRAN_OUT);

	em_.addCountDownEvent(EVENT_SEND_COMMAND_TO_0300, cc_.ScreenTranOutDuration + 1);
}

void HomeView::openContainerCallback(int callback)
{
	setMask(MaskList::LANGUAGE_MASK, true);
}

void HomeView::beginAnimationHandler(const int source)
{
}

void HomeView::messageOpenEndHandler(const int source)
{
	completedCommand();
	setMask(MaskList::INFO_MASK, true);
}

void HomeView::messageCloseEndHandler(const int source)
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

void HomeView::closeContainerCallback(int callback)
{
	if (LanguageList::ENGISH == ms_->ui_language)
	{
		//Texts::setLanguage(GB);
	}
	else if (LanguageList::SPANISH == ms_->ui_language)
	{
		//Texts::setLanguage(SPA);
	}
	else if (LanguageList::GERMAN == ms_->ui_language)
	{
		//Texts::setLanguage(SPA);
	}
	else if (LanguageList::FRENCH == ms_->ui_language)
	{
		//Texts::setLanguage(SPA);
	}
	application().drawCachedAreas();

	setMask(MaskList::FULL_MASK, false);
}

void HomeView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 1:
		event1();
		break;
	case 2:
		event2();
		break;
	case EVENT_RENDER_GRAPHIC:
		eventRenderGraphic();
		break;
	case EVENT_CHANGE_TO_STANDBY:
		eventChangeToStandby();
		break;
	case 6:
		event6();
		break;
	case EVENT_COUNTDOWN_TO_STANDBY_SEND_COMMAND:
		eventCountdownToStandbySendCommand();
		break;
	case 8:
		event8();
		break;
	case EVENT_ONE_TIME_RENDER:
		eventEventOneTimeRender();
		break;
	case EVENT_PLUG_NOT_IN_SOCKET:
		eventPlugNotInSocket();
		break;
	case 20:
		eventTranOutRFID();
		break;
	case EVENT_TRAN_IN:
		eventTranIn();
		break;
	case EVENT_TRAN_IN_END:
		eventTranInEnd();
		break;
	case EVENT_TRAN_OUT:
		eventTranOut();
		break;
	case 26:
		event26();
		break;
	case EVENT_SEND_COMMAND_TO_0300:
		eventSendCommandTo0300();
		break;
	case EVENT_CHANGE_SCREEN_TO_0300:
		eventChangeScreentTo0300();
		break;
	case 43:
		event43();
		break;
	case 44:
		event44();
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

void HomeView::event1()
{
	if (UXCommandStatus::UX_COMMAND_ON == ms_->ux_output_command_trigger) return;

	if (ms_->ux_popup_trigger_ != ms_->ux_popup_trigger_prev_ &&
		1 == ms_->ux_popup_trigger_prev_)
	{
		//if (0 >= count_filter_pop_)
		//{
		//	count_filter_pop_ = 30;

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
		//}
	}
	else if (ms_->ux_popup_number != ms_->ux_popup_number_prev)
	{
		//if (0 >= count_filter_pop_)
		//{
		//	count_filter_pop_ = 30;

		if (!ms_->popup_opened)
		{
			setMessageAction(&message_open_end_callback_, &message_close_end_callback_);
			em_.addOneTimeEvent(45);
		}
		//}
	}

	if (ms_->popup_opened)
	{
		em_.setOp1(EVENT_COUNTDOWN_TO_STANDBY_SEND_COMMAND, ms_->ux_delay_0200_to_0000);
		socket_slider_.setTouch(false);
	}
	else
	{
		socket_slider_.setTouch(true);
	}

	if (ms_->ux_prox_sensor_detect_user_prev != ms_->ux_prox_sensor_detect_user)
	{
		if (!ms_->ux_prox_sensor_detect_user)
		{
			em_.addCountDownEvent(EVENT_COUNTDOWN_TO_STANDBY_SEND_COMMAND, ms_->ux_delay_0200_to_0000);
		}
		else
		{
			em_.removeEvent(EVENT_COUNTDOWN_TO_STANDBY_SEND_COMMAND);
		}
	}
	ms_->ux_prox_sensor_detect_user_prev = ms_->ux_prox_sensor_detect_user;

	if (ms_->ux_home_rfid_status_prev != ms_->ux_home_rfid_status)
	{
		if (2 == ms_->ux_home_rfid_status)
		{
			em_.addOneTimeEvent(EVENT_TRAN_OUT_RFID);
			em_.addCountDownEvent(8, cc_.ScreenTranOutDuration + 1);
		}
	}

	if (ms_->ux_weather != ms_->ux_weather_prev ||
		ms_->ux_socket_status_right != ms_->ux_socket_status_right_prev ||
		ms_->ux_socket_status_left != ms_->ux_socket_status_left_prev)
	{
		em_.addOneTimeEvent(6);
	}

	if (0 != ms_->ux_drag_selector_vx)
	{
	}

#ifdef SIMULATOR
	if (ms_->ux_drag_selector_vx_prev != ms_->ux_drag_selector_vx)
	{
		selector_x_.updateValue(ms_->ux_drag_selector_vx);
	}

	if (ms_->ux_drag_selector_x_prev != ms_->ux_drag_selector_x)
	{
		selector_vx_.updateValue(ms_->ux_drag_selector_x);
	}
#endif
}

void HomeView::event2()
{
	footer_.renderGraphic();
}

void HomeView::eventRenderGraphic()
{
	information_.renderGraphic();
	title_.renderGraphic();
}

void HomeView::eventChangeToStandby()
{
	changeScreen(ScreenNumber::SCREEN_STANDBY);
}

void HomeView::event6()
{
	ms_->pole_previous_x = pole_.getX();
	ms_->pole_previous_y = pole_.getY();
	ms_->pole_previous_width = pole_.getWidth();
	ms_->pole_previous_height = pole_.getHeight();

	pole_.setBitmaps(Bitmap(getPoleBitmapSmall()), Bitmap(getPoleBitmapLarge()));
	pole_.setPosition(
		ms_->pole_previous_x,
		getScaledY(ms_->pole_previous_y),
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);

	socket_right_.renderGraphic();
	socket_left_.renderGraphic();
	information_.renderGraphic();
	title_.renderGraphic();
	footer_.renderGraphic();
	wallpaper_.renderGraphic();
}

void HomeView::eventCountdownToStandbySendCommand()
{
	sendCommand(ScreenNumber::SCREEN_STANDBY);

	em_.addOneTimeEvent(EventList::EVENT_CHANGE_TO_STANDBY);
}

void HomeView::event8()
{
	sendCommand(ScreenNumber::SCENARIO_4_1);

	changeScreen(ScreenNumber::SCREEN_PAY_RFID);
}

void HomeView::eventEventOneTimeRender()
{
}

void HomeView::eventPlugNotInSocket()
{
	if (!ms_->popup_opened)
	{
		if (ms_->ux_socket_status_limit)
		{
			int target = ms_->ux_socket_status_limit_target;
			int sta = 0;

			if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == target)
			{
				sta = ms_->ux_socket_status_right;
			}
			else
			{
				sta = ms_->ux_socket_status_left;
			}

			if (
				UXSocketStatus::UX_SOCKET_ERROR == sta ||
				UXSocketStatus::UX_SOCKET_WARNING == sta)
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_E3;
				sendCommand(ScreenNumber::SCENARIO_9_3);
			}
			else if (UXSocketStatus::UX_SOCKET_CHARGING == sta ||
				UXSocketStatus::UX_SOCKET_CHARGING == sta)
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_23;
				sendCommand(ScreenNumber::SCENARIO_2_3);
			}
			else
			{
				//ms_->ux_popup_trigger_ = true;
				//ms_->ux_popup_number = MessageNumber::MESSAGE_25;
				//sendCommand(ScreenNumber::SCENARIO_2_5);
			}

		}
		else if (socket_ret1_ == ChargeSocketSelected::CHARGE_SOCKET_RIGHT)
		{
			if (UXSocketStatus::UX_SOCKET_CHARGING == ms_->ux_socket_status_right)
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_25;
				sendCommand(ScreenNumber::SCENARIO_2_5);
			}
			else
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_E3;
				sendCommand(ScreenNumber::SCENARIO_9_3);
			}
		}
		else if (socket_ret1_ == ChargeSocketSelected::CHARGE_SOCKET_LEFT)
		{
			if (UXSocketStatus::UX_SOCKET_CHARGING == ms_->ux_socket_status_left)
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_25;
				sendCommand(ScreenNumber::SCENARIO_2_5);
			}
			else
			{
				ms_->ux_popup_trigger_ = true;
				ms_->ux_popup_number = MessageNumber::MESSAGE_E3;
				sendCommand(ScreenNumber::SCENARIO_9_3);
			}
		}
	}

	ms_->ux_socket_status_limit = false;
	ms_->ux_socket_status_limit_target = 0;
}

void HomeView::eventTranOutRFID()
{
	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	title_.beginTransitionOutAnimation();

	int pole_width = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
	int pole_height = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	pole_.startZoomAndMoveAnimation(
		305,
		getScaledY(214),
		(int)(pole_width * 0.33),
		(int)(pole_height * 0.33),
		cc_.ScreenTranOutDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone);

	socket_right_.beginAnimation(
		166 + 249,
		482,
		32,
		60,
		255,
		cc_.ScreenTranOutDuration);
	socket_left_.beginAnimation(
		70 + 249,
		482,
		32,
		60,
		255,
		cc_.ScreenTranOutDuration);

	int shift_r = 31 * 3;
	int shift_l = -shift_r;
	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	bool is_out_l = ms_->ux_plugin_in_out_status_left;

	if (!is_out_r)
	{
		plugin_right_.beginAnimation(178 + 249, getScaledY(257), 129, 593, 255, cc_.ScreenTranOutDuration);
	}
	else
	{
		plugin_right_.beginAnimation(178 + 249 + 31, getScaledY(257), 327, 585, 255, cc_.ScreenTranOutDuration);
	}

	if (!is_out_l)
	{
		plugin_left_.beginAnimation(-36 + 249, getScaledY(257), 129, 593, 255, cc_.ScreenTranOutDuration);
	}
	else
	{
		plugin_left_.beginAnimation(-36 + 249 + (-327 - 31 + 129), getScaledY(257), 327, 585, 255, cc_.ScreenTranOutDuration);
	}

	socket_slider_.setSlideDuration(cc_.ScreenTranOutDuration);
	socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_OUT_TO_BOTTON, true);
}

void HomeView::eventTranIn()
{
	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	bool is_out_l = ms_->ux_plugin_in_out_status_left;

	int pole_width = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
	int pole_height = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	//int pole_width = (int)(Bitmap(BITMAP_POLE_DAY_ID).getWidth() / 1.6);
	//int pole_height = (int)(Bitmap(BITMAP_POLE_DAY_ID).getHeight() / 1.6);
	pole_.setPosition(
		ms_->pole_previous_x,
		getScaledY(ms_->pole_previous_y),
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);
	pole_.setVisible(true);

	int16_t item_end_x = (int16_t)(144 / 1.6); // 800x480
	int16_t item_end_y = (int16_t)(-407 / 1.6); // 800x480

	pole_.startZoomAndMoveAnimation(
		item_end_x,
		getScaledY(item_end_y),
		pole_width,
		pole_height,
		cc_.ScreenTranInDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone);

	socket_right_.beginAnimation(300, 263, 60, 112, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration); // 800x480
    socket_left_.beginAnimation(120, 263, 60, 112, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration); // 800x480
	//socket_right_.beginAnimation(480, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
	//socket_left_.beginAnimation(192, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);

	if (!is_out_r)
	{
		plugin_right_.beginAnimation(318, -158 + POLE_DEBUG_Y_SHIFT, 241, 1111, 255, cc_.ScreenTranInDuration);
		//plugin_right_.beginAnimation(510, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranInDuration);
	}
	else
	{
		plugin_right_.beginAnimation(376, -158 + POLE_DEBUG_Y_SHIFT, 613, 1096, 255, cc_.ScreenTranInDuration);
		//plugin_right_.beginAnimation(510 + 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranInDuration);
	}

	if (!is_out_l)
	{
		plugin_left_.beginAnimation(-80, -158 + POLE_DEBUG_Y_SHIFT, 241, 1111, 255, cc_.ScreenTranInDuration);
		//plugin_left_.beginAnimation(-129, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranInDuration);
	}
	else
	{
		plugin_left_.beginAnimation(-510, -158 + POLE_DEBUG_Y_SHIFT, 613, 1096, 255, cc_.ScreenTranInDuration);
		//plugin_left_.beginAnimation(-129 - (981 - 387) - 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranInDuration);
	}

	title_.setInAnimationDuration(cc_.ScreenTranInDuration);
	title_.beginTransitionNextInAnimation(ms_->ux_screen_id_next);

	footer_.beginSlideAnimation(AnimationStyle::SLIDE_IN);

	if (ScreenNumber::SCREEN_PAY_RFID == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_BOOT == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_STANDBY == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_previous)
	{
		socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN_FROM_BOTTON, true);
	}
	else
	{
		if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == ms_->operation_charge_socket_selected)
		{
			socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN, true);
		}
		else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		{
			socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN, false);
		}
		else
		{
			socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN_FROM_BOTTON, true);
		}
	}
}

void HomeView::eventTranInEnd()
{
	setMask(MaskList::FULL_MASK, false);

	completedCommand();

	event2();
	eventRenderGraphic();
}

void HomeView::eventTranOut()
{
	pole_.startZoomAndMoveAnimation(
		90,
		getScaledY(-254),
		//144,
		//-407,
		pole_day_width_,
		pole_day_height_,
		cc_.ScreenTranOutDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);

	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	title_.beginTransitionOutAnimation();

	footer_.setAnimationDuration(cc_.ScreenTranOutDuration);
	footer_.beginSlideAnimation(AnimationStyle::SLIDE_OUT);
}

void HomeView::event26()
{
}

void HomeView::eventSendCommandTo0300()
{
	sendCommand(ScreenNumber::SCENARIO_2_30);

	em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN_TO_0300, cc_.AfterXSec);
}

void HomeView::eventChangeScreentTo0300()
{
	changeScreen(ScreenNumber::SCREEN_PAYMENT);
}
