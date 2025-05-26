#include <gui/payment_screen/PaymentView.hpp>
#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

int PaymentView::cam_[] = { 0 ,0 ,0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -10, -10, -9, -8, -7, -6, -5 , -4, -3, -2, -1, 0, 0 };

PaymentView::PaymentView() :
	BaseView(),
	socket_right_(false, ms_),
	socket_left_(true, ms_),
	plugin_right_(false, ms_),
	plugin_left_(true, ms_),
	pla_select_(0),
	//	pla_select_prv_(0),
	payment_method_prv(0),
	backto_button_clicked_callback_(this, &PaymentView::backtoButtonClickedHandler),
	button_clicked_callback_(this, &PaymentView::buttonClickedHandler),
	on_button_clicked_(this, &PaymentView::buttonClickedHandler),
	poleAnimationEndedCallback(this, &PaymentView::poleAnimationEndedHandler),
	footerMoveAnimationEndedCallback(this, &PaymentView::footerMoveAnimationEndedHandler),
	message_open_end_callback_(this, &PaymentView::messageOpenEndHandler),
	message_close_end_callback_(this, &PaymentView::messageCloseEndHandler),
	event_trigger_callback_(this, &PaymentView::eventTriggerHandler)
	//	checking_open_end_callback_(this, &PaymentView::checkingOpenEndHandler),
	//	checking_hide_end_callback_(this, &PaymentView::checkinghideEndHandler),
	//	checking_close_end_callback_(this, &PaymentView::checkingCloseEndHandler)
{
	payment_method_prv = ms_->ux_payment_selector;
}

void PaymentView::setupScreen()
{
	BaseView::setupScreen();

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
	socket_right_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(socket_right_);

	//Element
	socket_left_.initialize(ms_, true);
	socket_left_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(socket_left_);

	//Element
	plugin_right_.initialize(ms_, false);
	plugin_right_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(plugin_right_);

	//Element
	plugin_left_.initialize(ms_, true);
	plugin_left_.setPosition(0, 0, HAL::DISPLAY_WIDTH, getFixedDisplayHeight());
	add(plugin_left_);

	//Element
	title_.setPosition(cc_.TitleX, getScaledY(cc_.TitleY), cc_.TitleWidth, cc_.TitleHeight);
	title_.initialize(ms_);
	title_.setInAnimationDuration(cc_.ScreenTranInDuration);
	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	add(title_);

	//Element
	information_.setPosition(18, getScaledY(18), 43, 43);
	//information_.setPosition(30, 30, 70, 70);
	information_.initialize(ms_);
	information_.setDeepTouchable(true);
	information_.setButtonClickedCallback(button_clicked_callback_);
	add(information_);

	//Element
	language_.initialize(ms_);
	language_.setAnimationDuration(60);
	language_.setPosition(75, getScaledY(20), 241, 40);
	//language_.setPosition(120, 33, 386, 64);
	language_.lock();
	add(language_);

	//Element
	backto_.setPosition(417, getScaledY(18), 43, 43);
	//backto_.setPosition(668, 30, 70, 70);
	backto_.initialize(ms_);
	backto_.setButtonClickedCallback(backto_button_clicked_callback_);
	add(backto_);

	//Payment Method Block
	add(button_qr_);
	add(button_char_);
	add(button_cred_);
	add(arrow_);

	bottom_arrow_2_mask_.setPosition(197, getScaledY(481), 85, 81);
	//bottom_arrow_2_mask_.setPosition(316, 770, 136, 130);
	bottom_arrow_2_mask_.setAlpha(0);
	add(bottom_arrow_2_mask_);


	//QR Code
	qr_code_bg_.setColor(Color::getColorFromRGB(255, 255, 255));
	qr_code_bg_.setAlpha(255);
	add(qr_code_bg_);
	add(qr_code_);

	//Element Block
	add(plo_char_title_);
	add(plo_char_icon_2_);

	//Element
	footer_.initialize(ms_);
	footer_.setPosition(0, getFixedDisplayHeight() - 72, HAL::DISPLAY_WIDTH, 72);
	//footer_.setPosition(0, getFixedDisplayHeight() - 116, HAL::DISPLAY_WIDTH, 116);
	footer_.setAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	footer_.setSlideAnimationEndedCallback(footerMoveAnimationEndedCallback);
	add(footer_);

	//Element
	checking_.initialize(ms_);
	checking_.setPosition(-63, -63, 63, 63);
	//checking_.setPosition(-102, -102, 102, 102);
	checking_.setOpenCompletedCallback(checking_open_end_callback_);
	checking_.setHideCompletedCallback(checking_hide_end_callback_);
	checking_.setCloseCompletedCallback(checking_close_end_callback_);
	checking_.setVisible(false);
	add(checking_);

	//Element
	bottom_mask_.setPosition(0, 225, 480, 352);
	//bottom_mask_.setPosition(0, 360, 768, 564);
	bottom_mask_.setAlpha(0);
	bottom_mask_.setVisible(false);
	add(bottom_mask_);

	BaseView::afterSetupScreen();

	setMask(MaskList::FULL_MASK, true);

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addAlwaysKeepEvent(1, 1);
	em_.addAlwaysKeepEvent(2, 30);
	em_.addAlwaysKeepEvent(EventList::EVENT_RENDER_GRAPHIC, 60);
	em_.addOneTimeEvent(EventList::EVENT_TRAN_IN);
	em_.addCountDownEvent(EventList::EVENT_TRAN_IN_END, cc_.ScreenTranInDuration + cc_.After1Tick);
}

void PaymentView::tearDownScreen()
{
	code_.gc();
	remove(qr_code_);

	ms_->pole_previous_x = pole_.getX();
	ms_->pole_previous_y = pole_.getY();
	ms_->pole_previous_width = pole_.getWidth();
	ms_->pole_previous_height = pole_.getHeight();

	BaseView::tearDownScreen();
}

void PaymentView::afterTransition()
{
}

//void PaymentView::updateGraphic()
//{
//	pole_.setBitmaps(Bitmap(getPoleBitmapSmall()), Bitmap(getPoleBitmapLarge()));
//	if (WeatherStyle::NIGHT == ms_->ux_weather)
//	{
//		//pole_.setBitmaps(Bitmap(BITMAP_POLE_NIGHT_SMALL_ID), Bitmap(BITMAP_POLE_NIGHT_ID));
//		pole_.setPosition(
//			ms_->pole_previous_x,
//			ms_->pole_previous_y,
//			ms_->pole_previous_width,
//			ms_->pole_previous_height
//		);
//		pole_.setAnimationEndedCallback(poleAnimationEndedCallback);
//	}
//	else
//	{
//		//pole_.setBitmaps(Bitmap(BITMAP_POLE_DAY_SMALL_ID), Bitmap(BITMAP_POLE_DAY_ID));
//		pole_.setPosition(
//			ms_->pole_previous_x,
//			ms_->pole_previous_y,
//			ms_->pole_previous_width,
//			ms_->pole_previous_height
//		);
//		pole_.setAnimationEndedCallback(poleAnimationEndedCallback);
//	}
//}

void PaymentView::poleAnimationEndedHandler(const ZoomAnimationImage& image)
{
	animation_locker_--;
	animation_locker_count_++;
}

void PaymentView::footerMoveAnimationEndedHandler(const uint8_t source)
{
	animation_locker_--;
	animation_locker_count_++;
}

void PaymentView::buttonClickedHandler(const int source)
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
		//saveCommand();

		switch (ms_->ux_screen_id_current)
		{
		case ScreenNumber::SCENARIO_2_30:
			ms_->ux_popup_number = MessageNumber::MESSAGE_31;
			sendCommand(ScreenNumber::SCENARIO_2_36);
			break;
		case ScreenNumber::SCENARIO_2_31:
			ms_->ux_popup_number = MessageNumber::MESSAGE_32;
			sendCommand(ScreenNumber::SCENARIO_2_37);
			break;
		case ScreenNumber::SCENARIO_2_32:
			ms_->ux_popup_number = MessageNumber::MESSAGE_33;
			sendCommand(ScreenNumber::SCENARIO_2_38);
			break;
		default:
			break;
		}
	}
	else
	{
		ms_->ux_popup_number = MessageNumber::MESSAGE_0;
	}
}

void PaymentView::backtoButtonClickedHandler(const int source)
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

	//if (ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current)
	//{
	//	ms_->ux_return_button_clicked = true;
	//}
	//else
	//{
	//	int cd = 0;
	//	if (ms_->ux_loading_status == UXLoadingStatus::UX_LOADING_RUNNING)
	//	{
	//		cd = ANIMATION_LOADING_HIDE_DURATION;
	//		checking_.hide();
	//	}

	//	em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
	//	em_.addCountDownEvent(EVENT_SEND_COMMAND_TO_0200, cd + cc_.ScreenTranOutDuration + 1);
	//}
}

void PaymentView::buttonClickedHandler(const AbstractButton& source)
{
	if (0 >= count_filter_)
	{
		count_filter_ = 30;
	}
	else
	{
		return;
	}

	if (&button_char_ == &source)
	{
		ms_->ux_return_s02button1_clicked = true;
		ms_->ux_return_s02button2_clicked = true;
		sendCommand(ScreenNumber::SCENARIO_2_30);
	}
	else if (&button_cred_ == &source)
	{
		ms_->ux_return_s02button1_clicked = true;
		ms_->ux_return_s02button2_clicked = true;
		sendCommand(ScreenNumber::SCENARIO_2_31);
	}
	else if (&button_qr_ == &source)
	{
		ms_->ux_return_s02button1_clicked = true;
		ms_->ux_return_s02button2_clicked = true;
		sendCommand(ScreenNumber::SCENARIO_2_32);
	}

	em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
	em_.addCountDownEvent(EVENT_CHANGE_PAYMENT_METHOD_IN, cc_.ScreenTranInDuration / 2);
}

void PaymentView::messageOpenEndHandler(const int source)
{
	completedCommand();
	setMask(MaskList::INFO_MASK, true);

	application().drawCachedAreas();
}

void PaymentView::messageCloseEndHandler(const int source)
{
	if (source == (int)ReturnValue::RETURN_OK)
	{
		em_.addOneTimeEvent(47);
	}
	else
	{
		em_.addOneTimeEvent(47);
	}

	//loadCommand();
	completedCommand();

	setMask(MaskList::FULL_MASK, false);

	Application::getInstance()->drawCachedAreas();
}

//void PaymentView::checkingOpenEndHandler(const int source)
//{
//	//pla_select_prv_ = pla_select_;
//    
//	//em_.addAlwaysKeepEvent(21, 30);
//}
//
//void PaymentView::checkinghideEndHandler(const int source)
//{	
//}
//
//void PaymentView::checkingCloseEndHandler(const int source)
//{
//	//ms_->ux_screen_id_previous = ms_->ux_screen_id_current;
//	//ms_->ux_screen_id_next = ScreenNumber::SCENARIO_2_34;
//	//ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
//	//ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;
//
//	//em_.removeAllEvent();
//	//em_.addOneTimeEvent(12);
//	//em_.addOneTimeEvent(24);
//	//em_.addCountDownEvent(23, ANIMATION_TRANSITION_IN_DURATION + 1);
//}
//
void PaymentView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 1:
		event1();
		break;
		//	case 2:
		//		event2(); //
		//		break;
	case EVENT_RENDER_GRAPHIC:
		eventRenderGraphic();
		break;
	case EVENT_ARROW_ANI:
		eventArrowAni(); //
		break;
		//	case 7:
		//		event7(); //
		//		break;
		//	case 8:
		//		event8(); //
		//		break;
		//	case 9:
		//		event9(); //
		//		break;
	case EVENT_TRAN_IN:
		eventTranIn(); //Tran in.
		break;
	case EVENT_TRAN_IN_END:
		eventTranInEnd(); //In Completed.
		break;
		//	case 12:
		//		//event12(); //Fade out label.
		//		break;
	case EVENT_SEND_COMMAND_TO_0200:
		eventSendCommandTo0200(); //Out Completed.
		break;
	case EVENT_CHANGE_SCREEN_TO_0200:
		eventChangeScreenTo0200(); //Out Completed.
		break;
		//	//case EVENT_POP_OPEN:
		//	//	eventPopOpen(); //Open Info.
		//	//	break;
		//	//case 16:
		//	//	event16(); //Open Info Completed.
		//	//	break;
		//	//case EVENT_POP_DELETE:
		//	//	eventPopDelete(); //release Info.
		//	//	break;
		//	case EVENT_CHANGE_SCREEN_TO_0230:
		//		eventChangeScenarioTo0230();		
		//		break;
		//	case EVENT_CHANGE_SCREEN_TO_0231:
		//		eventChangeScenarioTo0231();
		//		break;
		//	case EVENT_CHANGE_SCREEN_TO_0232:
		//		eventChangeScenarioTo0232();
		//		break;
		//	case 21:
		//		event21(); //
		//		break;
		//	//case EVENT_POP_OPEN_BTN:
		//	//	eventPopOpenBtn(); //
		//	//	break;
	case 23:
		event23(); //
		break;
	case 24:
		event24(); //Move out to connect view.
		break;
	case EVENT_CHANGE_PAYMENT_METHOD_IN:
		eventChangePaymentMethodIn();
		break;
	case EVENT_CHANGE_PAYMENT_METHOD_OUT:
		eventChangePaymentMethodOut();
		break;
	case EVENT_WAIT_ACTIVE_PAY:
		eventWaitActivePay();
		break;
	case EVENT_ACCEPTED_PAYMENT:
		eventAcceptedPayment();
		break;
	case EVENT_WAIT_VERIFY:
		eventWaitVerify();
		break;
	case EVENT_ACCEPTED_WAIT_PAYMENT:
		eventAcceptedWaitPayment();
		break;
		//	case EVENT_CHANGE_PAYMENT_METHOD_IN_END:
		//		eventChangePaymentMethodInEnd();
		//		break;
	case EVENT_ACCEPTED_PAYMENT_QR:
		eventAcceptedPaymentQR();
		break;
	case EVENT_UNLOCK_SELECTED_PLUG:
		eventUnlockSelectedPlug();
		break;
	case EVENT_TRAN_OUT:
		eventTranOut();
		break;
		//	case 40:
		//		event40();
		//		break;
		//	case 41:
		//		event41();
		//		break;
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

void PaymentView::event1()
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
}

void PaymentView::eventRenderGraphic()
{
	socket_right_.renderGraphic();
	socket_left_.renderGraphic();
	information_.renderGraphic();
	backto_.renderGraphic();
	//	title_.renderGraphic();
	footer_.renderGraphic();
	wallpaper_.renderGraphic();
}

void PaymentView::eventArrowAni()
{
	int idx = bottom_arrow_2_tick_ % 26;

	arrow_.setXY(arrow_.getX(), bottom_arrow_2_sy_ + cam_[idx]);
	arrow_.invalidate();
	bottom_arrow_2_mask_.invalidate();

	bottom_arrow_2_tick_++;
}

void PaymentView::eventTranIn()
{
	//	int shift_r = 31 * 3;
	//	int shift_l = -shift_r;
	//	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	//	bool is_out_l = ms_->ux_plugin_in_out_status_left;
	//	
	//	socket_right_.beginAnimation(480, 421, 96, 180, getSocketRightAlpha(), cc_.ScreenTranInDuration);
	//	socket_left_.beginAnimation(192, 421, 96, 180, getSocketLeftAlpha(), cc_.ScreenTranInDuration);
	//
	//	if (!is_out_r)
	//	{
	//		plugin_right_.beginAnimation(
	//			510,
	//			cc_.PluginLargeEndY + POLE_DEBUG_Y_SHIFT,
	//			387,
	//			1779,
	//			255,
	//			cc_.ScreenTranInDuration);
	//	}
	//	else
	//	{
	//		plugin_right_.beginAnimation(
	//			510 + cc_.PluginRightLargeXShift,
	//			cc_.PluginLargeEndY + POLE_DEBUG_Y_SHIFT,
	//			981,
	//			1755,
	//			255,
	//			cc_.ScreenTranInDuration);
	//	}
	//
	//	if (!is_out_l)
	//	{
	//		plugin_left_.beginAnimation(
	//			-129,
	//			cc_.PluginLargeEndY + POLE_DEBUG_Y_SHIFT,
	//			387,
	//			1779,
	//			255,
	//			cc_.ScreenTranInDuration);
	//	}
	//	else
	//	{
	//		plugin_left_.beginAnimation(
	//			-129 - cc_.PluginLeftLargeXShift,
	//			cc_.PluginLargeEndY + POLE_DEBUG_Y_SHIFT,
	//			981,
	//			1755,
	//			255,
	//			cc_.ScreenTranInDuration);
	//	}

	bool is_out_r = ms_->ux_plugin_in_out_status_right;
	bool is_out_l = ms_->ux_plugin_in_out_status_left;

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

	if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == ms_->operation_charge_socket_selected)
	{
		socket_right_.beginAnimation(300, 263, 60, 112, cc_.SocketAlphaGeneral, cc_.ScreenTranInDuration);
		//socket_right_.beginAnimation(480, 421, 96, 180, cc_.SocketAlphaGeneral, cc_.ScreenTranInDuration);
	}
	else
	{
		socket_right_.beginAnimation(300, 263, 60, 112, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
		//socket_right_.beginAnimation(480, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
	}

	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		socket_left_.beginAnimation(120, getScaledY(263), 60, 112, cc_.SocketAlphaGeneral, cc_.ScreenTranInDuration);
		//socket_left_.beginAnimation(192, 421, 96, 180, cc_.SocketAlphaGeneral, cc_.ScreenTranInDuration);
	}
	else
	{
		socket_left_.beginAnimation(120, getScaledY(263), 60, 112, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
		//socket_left_.beginAnimation(192, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
	}

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
		plugin_left_.beginAnimation(-80, getScaledY(-209 + POLE_DEBUG_Y_SHIFT), 241, 1111, 255, cc_.ScreenTranInDuration);
		//plugin_left_.beginAnimation(-129, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranInDuration);
	}
	else
	{
		plugin_left_.beginAnimation(-510, getScaledY(-209 + POLE_DEBUG_Y_SHIFT), 613, 1096, 255, cc_.ScreenTranInDuration);
		//plugin_left_.beginAnimation(-129 - (981 - 387) - 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranInDuration);
	}

	if (
		ScreenNumber::SCREEN_PAY_RFID == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_BOOT == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_STANDBY == ms_->ux_screen_id_previous ||
		ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_previous)
	{
		footer_.beginSlideAnimation(AnimationStyle::STATIC_IN);
	}
	else
	{
		footer_.beginSlideAnimation(AnimationStyle::SLIDE_IN);
	}

	em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_IN);

	//Payment Logo - QR Code
	code_.setRawData(ms_->ux_qr_data);
	qr_code_.setQRCode(&code_);
	qr_code_.setScale(8);
	int16_t qcpx = 240;
	int16_t qcpy = 340;
	//int16_t qcpx = 384;
	//int16_t qcpy = 545;
	int cw = code_.getWidth();
	int ch = code_.getHeight();
	int qw = qr_code_.getWidth();
	int qh = qr_code_.getHeight();
	int16_t qx = 240 - (qw / 2);
	int16_t qy = 331 - (qh / 2);
	//int16_t qx = 384 - (qw / 2);
	//int16_t qy = 530 - (qh / 2);
	qr_code_.setXY(qx, qy);
	qr_code_.setQRCode(&code_);
	qr_code_.setScale(8);
	qr_code_.setAlpha(0);
	qr_code_.setColor(getPLOQrR(), getPLOQrG(), getPLOQrB());
	qr_code_.setBackgroundColor(255, 255, 255);
	qr_code_.setVisible(false);

	qr_code_bg_.setPosition(
		qr_code_.getX() - 12,
		qr_code_.getY() - 12,
		qr_code_.getWidth() + 25,
		qr_code_.getHeight() + 25
	);
	//qr_code_bg_.setPosition(
	//	qr_code_.getX() - 20,
	//	qr_code_.getY() - 20,
	//	qr_code_.getWidth() + 40,
	//	qr_code_.getHeight() + 40
	//);
	qr_code_bg_.setVisible(false);

	qr_code_end_x_ = qr_code_.getX();
	qr_code_end_y_ = qr_code_.getY();
	qr_code_bg_end_x_ = qr_code_bg_.getX();
	qr_code_bg_end_y_ = qr_code_bg_.getY();
}

void PaymentView::eventTranInEnd()
{
	setMask(MaskList::FULL_MASK, false);
}

void PaymentView::eventSendCommandTo0200()
{
	sendCommand(ScreenNumber::SCREEN_HOME);

	em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN_TO_0200, cc_.After2Tick);
}

void PaymentView::eventChangeScreenTo0200()
{
	changeScreen(ScreenNumber::SCREEN_HOME);
}

void PaymentView::event23()
{
	changeScreen(ScreenNumber::SCREEN_CONNECT);
}

void PaymentView::event24()
{

}

void PaymentView::eventChangePaymentMethodIn()
{
	ScreenNumber sn = ms_->ux_screen_id_next;

	switch (sn)
	{
	case ScreenNumber::SCENARIO_2_30:
		//ms_->ux_screen_id_current = ScreenNumber::SCENARIO_2_30;		
		button_qr_.setXY(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY));
		button_qr_.setBitmaps(Bitmap(BITMAP_PAY_QRCODE_BUTTON_ID), Bitmap(BITMAP_PAY_QRCODE_BUTTON_ID));
		button_qr_.setLabelText(TypedText(T_S0210_B_BUTTON_1));
		button_qr_.setLabelTextXPrefixOffset(46);
		//button_qr_.setLabelTextXPrefixOffset(24 + 50);
		button_qr_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_qr_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_qr_.setAlpha(0);
		button_qr_.setVisible(true);
		button_qr_.setAction(on_button_clicked_);
		button_qr_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_qr_.startMoveAnimation(cc_.PaymentBtnXRight, cc_.PaymentBtnQrEndY, cc_.ScreenTranInDuration / 2);

		button_char_.setVisible(false);

		button_cred_.setXY(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY + cc_.PaymentBtnSplitY));
		button_cred_.setBitmaps(Bitmap(BITMAP_PAY_CREDITCARD_BUTTON_ID), Bitmap(BITMAP_PAY_CREDITCARD_BUTTON_ID));
		button_cred_.setLabelText(TypedText(T_S0210_C_BUTTON_2));
		button_cred_.setLabelTextXPrefixOffset(46);
		//button_cred_.setLabelTextXPrefixOffset(24 + 50);
		button_cred_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_cred_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_cred_.setAlpha(0);
		button_cred_.setVisible(true);
		button_cred_.setAction(on_button_clicked_);
		button_cred_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_cred_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY), cc_.ScreenTranInDuration / 2);

		plo_char_icon_2_.setBitmap(Bitmap(BITMAP_PAYMENT_IDX_CHARGE_CARD_BLUE_ID));
		plo_char_icon_2_.setXY(197, getScaledY(340));
		//plo_char_icon_2_.setXY(316, 597 - 53);
		plo_char_icon_2_.setAlpha(0);
		plo_char_icon_2_.setVisible(true);
		plo_char_icon_2_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		plo_char_title_.setTypedText(TypedText(T_S0210_A_BODY));
		plo_char_title_.setColor(touchgfx::Color::getColorFromRGB(getDayBlockNightWhiteR(), getDayBlockNightWhiteG(), getDayBlockNightWhiteB()));
		plo_char_title_.setPosition(140, getScaledY(431), 200, 46);
		//plo_char_title_.setPosition(224, 690, 320, 74);
		plo_char_title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
		plo_char_title_.setAlpha(0);
		plo_char_title_.setVisible(true);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		arrow_.setBitmap(Bitmap(BITMAP_PAYMENT_ARROW_ID));
		arrow_.setXY(197, getScaledY(cc_.arrowBeginY));
		//arrow_.setXY(316, cc_.arrowBeginY);
		arrow_.setAlpha(0);
		arrow_.setVisible(true);
		arrow_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		bottom_arrow_2_sy_ = arrow_.getY();
		bottom_arrow_2_tick_ = 0;
		em_.addAlwaysKeepEvent(EVENT_ARROW_ANI, 4);

		em_.addAlwaysKeepEvent(EVENT_WAIT_ACTIVE_PAY, 1);

		completedCommand();

		title_.renderGraphic();
		title_.beginTransitionInAnimationFast();
		eventRenderGraphic();
		break;
	case ScreenNumber::SCENARIO_2_31:
		//ms_->ux_screen_id_current = ScreenNumber::SCENARIO_2_31;		
		button_qr_.setXY(cc_.PaymentBtnXRight, cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY);
		button_qr_.setBitmaps(Bitmap(BITMAP_PAY_QRCODE_BUTTON_ID), Bitmap(BITMAP_PAY_QRCODE_BUTTON_ID));
		button_qr_.setLabelText(TypedText(T_S0210_B_BUTTON_1));
		button_qr_.setLabelTextXPrefixOffset(46);
		//button_qr_.setLabelTextXPrefixOffset(24 + 50);
		button_qr_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_qr_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_qr_.setAlpha(0);
		button_qr_.setVisible(true);
		button_qr_.setAction(on_button_clicked_);
		button_qr_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_qr_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY), cc_.ScreenTranInDuration / 2);

		button_char_.setXY(cc_.PaymentBtnXRight, cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY + cc_.PaymentBtnStartShiftY);
		button_char_.setBitmaps(Bitmap(BITMAP_PAY_CHARGECARD_BUTTON_ID), Bitmap(BITMAP_PAY_CHARGECARD_BUTTON_ID));
		button_char_.setLabelText(TypedText(T_S0210_B_BUTTON_2));
		button_char_.setLabelTextXPrefixOffset(46);
		//button_char_.setLabelTextXPrefixOffset(24 + 50);
		button_char_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_char_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_char_.setAlpha(0);
		button_char_.setVisible(true);
		button_char_.setAction(on_button_clicked_);
		button_char_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_char_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY), cc_.ScreenTranInDuration / 2);

		button_cred_.setVisible(false);

		plo_char_icon_2_.setBitmap(Bitmap(BITMAP_PAYMENT_IDXCREDIT_CARD_BLUE_ID));
		plo_char_icon_2_.setXY(188, 377);
		//plo_char_icon_2_.setXY(302, 657 - 53);
		plo_char_icon_2_.setAlpha(0);
		plo_char_icon_2_.setVisible(true);
		plo_char_icon_2_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		plo_char_title_.setTypedText(TypedText(T_S0210_B_BODY));
		plo_char_title_.setColor(touchgfx::Color::getColorFromRGB(getDayBlockNightWhiteR(), getDayBlockNightWhiteG(), getDayBlockNightWhiteB()));
		plo_char_title_.setPosition(140, getScaledY(431), 200, 46);
		//plo_char_title_.setPosition(224, 690, 320 + 100 - 100, 74);
		plo_char_title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
		plo_char_title_.setAlpha(0);
		plo_char_title_.setVisible(true);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		arrow_.setBitmap(Bitmap(BITMAP_PAYMENT_ARROW_ID));
		arrow_.setXY(316, cc_.arrowBeginY);
		arrow_.setAlpha(0);
		arrow_.setVisible(true);
		arrow_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		bottom_arrow_2_sy_ = arrow_.getY();
		bottom_arrow_2_tick_ = 0;
		em_.addAlwaysKeepEvent(EVENT_ARROW_ANI, 4);

		em_.addAlwaysKeepEvent(EVENT_WAIT_ACTIVE_PAY, 1);

		completedCommand();
		title_.renderGraphic();
		title_.beginTransitionInAnimation();
		break;
	case ScreenNumber::SCENARIO_2_32:
		//ms_->ux_screen_id_current = ScreenNumber::SCENARIO_2_32;

		button_qr_.setVisible(false);

		button_char_.setXY(cc_.PaymentBtnXRight, cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY);
		button_char_.setBitmaps(Bitmap(BITMAP_PAY_CHARGECARD_BUTTON_ID), Bitmap(BITMAP_PAY_CHARGECARD_BUTTON_ID));
		button_char_.setLabelText(TypedText(T_S0210_B_BUTTON_2));
		button_char_.setLabelTextXPrefixOffset(46);
		//button_char_.setLabelTextXPrefixOffset(24 + 50);
		button_char_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_char_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_char_.setAlpha(0);
		button_char_.setVisible(true);
		button_char_.setAction(on_button_clicked_);
		button_char_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_char_.startMoveAnimation(cc_.PaymentBtnXRight, cc_.PaymentBtnQrEndY, cc_.ScreenTranInDuration / 2);

		button_cred_.setXY(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY + cc_.PaymentBtnSplitY));
		button_cred_.setBitmaps(Bitmap(BITMAP_PAY_CREDITCARD_BUTTON_ID), Bitmap(BITMAP_PAY_CREDITCARD_BUTTON_ID));
		button_cred_.setLabelText(TypedText(T_S0210_C_BUTTON_2));
		button_cred_.setLabelTextXPrefixOffset(46);
		//button_cred_.setLabelTextXPrefixOffset(24 + 50);
		button_cred_.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_cred_.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
		button_cred_.setAlpha(0);
		button_cred_.setVisible(true);
		button_cred_.setAction(on_button_clicked_);
		button_cred_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);
		button_cred_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY), cc_.ScreenTranInDuration / 2);

		plo_char_title_.setTypedText(TypedText(T_S0210_C_BODY));
		plo_char_title_.setColor(touchgfx::Color::getColorFromRGB(getDayBlockNightWhiteR(), getDayBlockNightWhiteG(), getDayBlockNightWhiteB()));
		plo_char_title_.setPosition(140, getScaledY(493), 200, 46);
		//plo_char_title_.setPosition(224, 690 + 100, 320, 74);
		plo_char_title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
		plo_char_title_.setAlpha(0);
		plo_char_title_.setVisible(true);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		qr_code_.setVisible(true);
		qr_code_bg_.setVisible(true);

		qr_code_.setY(getScaledY(getFixedDisplayHeight() + 20));
		qr_code_bg_.setY(getScaledY(getFixedDisplayHeight()));
		//qr_code_.setY(HAL::DISPLAY_HEIGHT + 20);
		//qr_code_bg_.setY(HAL::DISPLAY_HEIGHT);
		qr_code_.startMoveAnimation(qr_code_end_x_, qr_code_end_y_, cc_.ScreenTranInDuration / 2);
		qr_code_bg_.startMoveAnimation(qr_code_bg_end_x_, getScaledY(qr_code_bg_end_y_), cc_.ScreenTranInDuration / 2);

		em_.addAlwaysKeepEvent(EVENT_WAIT_ACTIVE_PAY, 1);

		completedCommand();

		title_.renderGraphic();
		title_.beginTransitionInAnimation();
		break;
	case ScreenNumber::SCENARIO_2_33:
		//ms_->ux_screen_id_current = ScreenNumber::SCENARIO_2_33;

		plo_char_title_.setTypedText(TypedText(T_S40_TITLE));
		plo_char_title_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		plo_char_title_.setPosition(108, getScaledY(431), 262, 46);
		//plo_char_title_.setPosition(224 - 50, 690, 320 + 100, 74);
		plo_char_title_.setWideTextAction(WIDE_TEXT_WORDWRAP);
		plo_char_title_.setAlpha(0);
		plo_char_title_.setVisible(true);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaEnd, cc_.ScreenTranInDuration / 2);

		checking_.setAnimationDuration(cc_.ScreenTranInDuration / 2);
		checking_.setXY(208, getScaledY(485));
		//checking_.setXY(333, 776);
		checking_.setVisible(true);
		checking_.open();

		em_.addCountDownEvent(EVENT_WAIT_VERIFY, cc_.ScreenTranInDuration / 2);

		completedCommand();

		title_.renderGraphic();
		title_.beginTransitionInAnimationFast();
		break;
	case ScreenNumber::SCENARIO_2_34:
		//ms_->ux_screen_id_current = ScreenNumber::SCENARIO_2_34;

		checking_.setAnimationDuration(cc_.ScreenTranInDuration / 2);
		checking_.setXY(208, getScaledY(485));
		//checking_.setXY(333, 776);
		checking_.setVisible(true);
		checking_.checked();

		plo_char_title_.setVisible(false);

		em_.addCountDownEvent(EVENT_ACCEPTED_PAYMENT, cc_.ScreenTranInDuration);

		completedCommand();

		title_.renderGraphic();
		title_.beginTransitionInAnimationFast();
		break;
	default:
		break;
	}
}

void PaymentView::eventChangePaymentMethodOut()
{
	ScreenNumber sn = ms_->ux_screen_id_current;

	switch (sn)
	{
	case ScreenNumber::SCENARIO_2_30:
		title_.beginTransitionOutAnimationFast();
		button_qr_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_qr_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		button_cred_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_cred_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		plo_char_icon_2_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		arrow_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		em_.removeEvent(EVENT_ARROW_ANI);
		break;
	case ScreenNumber::SCENARIO_2_31:
		title_.beginTransitionOutAnimationFast();
		button_qr_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_qr_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		button_char_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_char_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		plo_char_icon_2_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		arrow_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		em_.removeEvent(EVENT_ARROW_ANI);
		break;
	case ScreenNumber::SCENARIO_2_32:
		title_.beginTransitionOutAnimationFast();
		button_char_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_char_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		button_cred_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		button_cred_.startMoveAnimation(cc_.PaymentBtnXRight, getScaledY(cc_.PaymentBtnQrEndY + cc_.PaymentBtnSplitY + cc_.PaymentBtnStartShiftY), cc_.ScreenTranOutDuration / 2);
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		qr_code_.startMoveAnimation(qr_code_end_x_, getScaledY(getFixedDisplayHeight() + 20), cc_.ScreenTranInDuration / 2);
		qr_code_bg_.startMoveAnimation(qr_code_bg_end_x_, getScaledY(getFixedDisplayHeight()), cc_.ScreenTranInDuration / 2);
		break;
	case ScreenNumber::SCENARIO_2_33:
		title_.beginTransitionOutAnimationFast();
		plo_char_title_.startFadeAnimation(cc_.PaymentAlphaBegin, cc_.ScreenTranOutDuration / 2);
		break;
	default:
		break;
	}
	//	bottom_mask_.setVisible(true);
	//
	//	em_.addCountDownEvent(EventList::EVENT_TRAN_IN_END, cc_.ScreenTranOutDuration / 2 + cc_.After1Tick);
}

void PaymentView::eventWaitActivePay()
{
	if (1 != ms_->ux_payment_user_selector &&
		2 != ms_->ux_payment_user_selector &&
		4 != ms_->ux_payment_user_selector)
	{
		return;
	}

	if (ms_->ux_payment_user_selector != ms_->ux_payment_user_selector_prev)
	{
		pla_select_ = ms_->ux_payment_user_selector;

		switch (pla_select_)
		{
		case 1:
			sendCommand(ScreenNumber::SCENARIO_2_34);

			em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
			em_.addCountDownEvent(EVENT_ACCEPTED_PAYMENT_QR, cc_.ScreenTranInDuration / 2);
			em_.addCountDownEvent(EVENT_CHANGE_PAYMENT_METHOD_IN, cc_.ScreenTranInDuration);

			break;
		case 2:
		case 4:
			sendCommand(ScreenNumber::SCENARIO_2_33);

			em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
			em_.addCountDownEvent(EVENT_CHANGE_PAYMENT_METHOD_IN, cc_.ScreenTranInDuration / 2);

			break;
		default:

			break;
		}

		em_.removeEvent(EVENT_WAIT_ACTIVE_PAY);
	}
}

void PaymentView::eventAcceptedPayment()
{
	em_.addAlwaysKeepEvent(EVENT_UNLOCK_SELECTED_PLUG, 1);
}

void PaymentView::eventWaitVerify()
{
	em_.addAlwaysKeepEvent(EVENT_ACCEPTED_WAIT_PAYMENT, 1);
}

void PaymentView::eventAcceptedWaitPayment()
{
	if (1 != ms_->ux_payment_selector &&
		2 != ms_->ux_payment_selector &&
		4 != ms_->ux_payment_selector)
	{
		return;
	}

	if (ms_->ux_payment_selector_prev != ms_->ux_payment_selector)
	{
		switch (pla_select_)
		{
		case 1:
			ms_->ux_screen_id_previous = ms_->ux_screen_id_current;
			ms_->ux_screen_id_next = ScreenNumber::SCENARIO_2_34;
			ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
			ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;

			em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
			em_.addCountDownEvent(EVENT_CHANGE_PAYMENT_METHOD_IN, cc_.ScreenTranInDuration / 2);
			break;
		case 2:
		case 4:
			ms_->ux_screen_id_previous = ms_->ux_screen_id_current;
			ms_->ux_screen_id_next = ScreenNumber::SCENARIO_2_34;
			ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
			ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;

			em_.addOneTimeEvent(EVENT_CHANGE_PAYMENT_METHOD_OUT);
			em_.addCountDownEvent(EVENT_CHANGE_PAYMENT_METHOD_IN, cc_.ScreenTranInDuration / 2);
			break;
		default:
			break;
		}

		em_.removeEvent(EVENT_ACCEPTED_WAIT_PAYMENT);
	}

	payment_method_prv = ms_->ux_payment_selector;
}

//void PaymentView::eventChangePaymentMethodInEnd()
//{
//}

void PaymentView::eventAcceptedPaymentQR()
{
	checking_.setAnimationDuration(cc_.ScreenTranInDuration / 2);
	checking_.setXY(208, 485);
	//checking_.setXY(333, 776);
	checking_.setVisible(true);
	checking_.open();
}

void PaymentView::eventUnlockSelectedPlug()
{
	if (ms_->ux_payment_checked_prev != ms_->ux_payment_checked &&
		1 == ms_->ux_payment_checked)
	{
		sendCommand(ScreenNumber::SCREEN_CONNECT);

		checking_.setAnimationDuration(cc_.ScreenTranOutDuration);
		checking_.hideChecked();

		//em_.removeAllEvent();
		em_.addCountDownEvent(EVENT_TRAN_OUT, cc_.ScreenTranOutDuration + 1);
	}
}

void PaymentView::eventTranOut()
{
	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	title_.beginTransitionNextOutAnimation(ms_->ux_screen_id_next);

	int pole_width = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
	int pole_height = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	pole_.startZoomAndMoveAnimation(
		getPoleNextX(),
		getScaledY(133),
		//214,
		(int)(pole_width * 0.33),
		(int)(pole_height * 0.33),
		cc_.ScreenTranOutDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);

	socket_right_.setVisible(true);
	socket_left_.setVisible(true);
	plugin_right_.setVisible(true);
	plugin_left_.setVisible(true);

	socket_right_.beginAnimation(getSocketRightNextX(), getScaledY(301), 20, 37, 255, cc_.ScreenTranOutDuration);
	socket_left_.beginAnimation(getSocketLeftNextX(), getScaledY(301), 20, 37, 255, cc_.ScreenTranOutDuration);
	plugin_right_.beginAnimation(getPluginRightNextX(), getScaledY(160), getPluginRightNextWidth(), getPluginRightNextHeight(), 255, cc_.ScreenTranOutDuration);
	plugin_left_.beginAnimation(getPluginLeftNextX(), getScaledY(160), getPluginLeftNextWidth(), getPluginLeftNextHeight(), 255, cc_.ScreenTranOutDuration);
	//socket_right_.beginAnimation(getSocketRightNextX(), 482, 32, 60, 255, cc_.ScreenTranOutDuration);
	//socket_left_.beginAnimation(getSocketLeftNextX(), 482, 32, 60, 255, cc_.ScreenTranOutDuration);
	//plugin_right_.beginAnimation(getPluginRightNextX(), 257, getPluginRightNextWidth(), getPluginRightNextHeight(), 255, cc_.ScreenTranOutDuration);
	//plugin_left_.beginAnimation(getPluginLeftNextX(), 257, getPluginLeftNextWidth(), getPluginLeftNextHeight(), 255, cc_.ScreenTranOutDuration);

	//em_.removeAllEvent();
	//em_.addOneTimeEvent(24);
	em_.addCountDownEvent(23, cc_.ScreenTranOutDuration + 1);
}

#pragma region Style Resource
const int16_t PaymentView::getPoleNextX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 347;
		//return 768 - 56 - 160 + 4;
	}
	return 35;
	//return 56;
}

const int16_t PaymentView::getSocketRightNextX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 416;
		//return 768 - 70 - 32;
	}
	return 103;
	//return 166;
}

const int16_t PaymentView::getSocketLeftNextX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 356;
		//return 768 - 166 - 32;
	}
	return 43;
	//return 70;
}

const int16_t PaymentView::getPluginRightNextWidth()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_right)
	{
		return 80;
		//return 129;
	}

	return 204;
	//return 327;
}

const int16_t PaymentView::getPluginLeftNextWidth()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_left)
	{
		return 80;
		//return 129;
	}

	return 204;
	//return 327;
}

const int16_t PaymentView::getPluginRightNextHeight()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_right)
	{
		return 370;
		//return 593;
	}

	return 365;
	//return 585;
}

const int16_t PaymentView::getPluginLeftNextHeight()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_left)
	{
		return 370;
		//return 593;
	}

	return 365;
	//return 585;
}

const int16_t PaymentView::getPluginRightNextX()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_right)
	{
		if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		{
			return 423; //TODO : mod
			//return 178 + 552 - 56 + 4; //TODO : mod
		}

		return 111;
		//return 178;
	}
	else
	{
		if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		{
			return 445; //TODO : mod
			//return -36 + 552 - 56 + 4 + 248; //TODO : mod
		}

		return 132;
		//return -36 + 248;
	}
}

const int16_t PaymentView::getPluginLeftNextX()
{
	if (UXPlugInOutStatus::UX_PLUGIN_IN == ms_->ux_plugin_in_out_status_left)
	{
		if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		{
			return 290;
			//return -36 + 552 - 56 + 4;
		}

		return -22;
		//return -36;
	}
	else
	{
		if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
		{
			return 146;
			//return -36 + 552 - 56 + 4 - 248 + 19;
		}

		return 165;
		//return -36 - 248 + 19;
	}
}

const int16_t PaymentView::getPoleStaticX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 52;
		//return 84;
	}

	return 0;
}

const uint16_t PaymentView::getPluginStaticBitmap()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return BITMAP_PLUGIN_IN_LEFT_BLACK_LARGE_PART_ID;
	}

	return BITMAP_PLUGIN_IN_RIGHT_BLACK_LARGE_PART_ID;
}

const int16_t PaymentView::getPluginStaticX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 0;
	}

	return 285;
	//return 456;
}

const int16_t PaymentView::getPLOQrCodeX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 312;
		//return 500;
	}

	return 84;
	//return 135;
}

const int16_t PaymentView::getPLOQrIdxX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 279;
		//return 768 - 87 - 234;
	}

	return 54;
	//return 87;
}

const uint8_t PaymentView::getPLOQrR()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)0;
	}

	return (uint8_t)0;
}

const uint8_t PaymentView::getPLOQrG()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)0;
	}

	return (uint8_t)0;
}

const uint8_t PaymentView::getPLOQrB()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)0;
	}

	return (uint8_t)0;
}

const uint8_t PaymentView::getPLOQrMaskR()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)33;
	}

	return (uint8_t)198;
}

const uint8_t PaymentView::getPLOQrMaskG()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)32;
	}

	return (uint8_t)199;
}
const uint8_t PaymentView::getPLOQrMaskB()
{
	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		return (uint8_t)33;
	}

	return (uint8_t)206;
}

const int16_t PaymentView::getPLOCharIconX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 331;
		//return 768 - 165 - 73;
	}

	return 103;
	//return 165;
}

const int16_t PaymentView::getPLOCharIdxX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 268;
		//return 429;
	}

	return 40;
	//return 65;
}

const int16_t PaymentView::getPLOCredIconX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 318;
		//return 510;
	}

	return 93;
	//return 149;
}

const int16_t PaymentView::getPLOCredIdxX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 262;
		//return 420;
	}

	return 31;
	//return 50;
}

const int16_t PaymentView::getCheckingX()
{
	if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	{
		return 180;
		//return 288;
	}

	return 236;
	//return 378;
}
#pragma endregion Style Resource
