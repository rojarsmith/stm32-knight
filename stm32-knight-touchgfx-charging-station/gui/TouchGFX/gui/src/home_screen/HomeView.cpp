#include <gui/home_screen/HomeView.hpp>

#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

HomeView::HomeView()
    :
	//socket_right_(false, ms_),
	//socket_left_(true, ms_),
	//plugin_right_(false, ms_),
	//plugin_left_(true, ms_),
	button_clicked_callback_(this, &HomeView::buttonClickedHandler),
	poleAnimationEndedCallback(this, &HomeView::poleAnimationEndedHandler),
	//begin_animation_callback_(this, &HomeView::beginAnimationHandler),
	//open_container_callback_(this, &HomeView::openContainerCallback),
	//close_container_callback_(this, &HomeView::closeContainerCallback),
	//message_open_end_callback_(this, &HomeView::messageOpenEndHandler),
	//message_close_end_callback_(this, &HomeView::messageCloseEndHandler),
	//plug_not_in_socket_callback_(this, &HomeView::plugNotInSocketHandler),
	//bar_move_out_animation_end_callback_(this, &HomeView::barMoveOutAnimationEndHandler),
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
		ms_->pole_previous_y,
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);
	pole_.setAnimationEndedCallback(poleAnimationEndedCallback);
	add(pole_);

	//Item
	title_.setPosition(cc_.TitleX, cc_.TitleY, cc_.TitleWidth, cc_.TitleHeight);
	title_.initialize(ms_);
	title_.setInAnimationDuration(ANIMATION_TRANSITION_IN_DURATION);
	title_.setOutAnimationDuration(ANIMATION_TRANSITION_OUT_DURATION);
	add(title_);

	//Element
	uint16_t foot_reduce_y = (uint16_t)(116 / 1.6); // 800x480
	footer_.initialize(ms_);
	//footer_.setPosition(0, HAL::DISPLAY_HEIGHT - foot_reduce_y, HAL::DISPLAY_WIDTH, foot_reduce_y);
	footer_.setPosition(0, getFixedDisplayHeight() - foot_reduce_y - ratio_height_, HAL::DISPLAY_WIDTH, foot_reduce_y); // 
	footer_.setAnimationDuration(ANIMATION_TRANSITION_IN_DURATION);
	//footer_.set
	add(footer_);

	BaseView::afterSetupScreen();

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addAlwaysKeepEvent(1, 1);
	em_.addAlwaysKeepEvent(2, 30);
	em_.addOneTimeEvent(EVENT_RENDER_GRAPHIC);
	em_.addOneTimeEvent(EventList::EVENT_TRAN_IN);
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

void HomeView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 2:
		event2();
		break;
	case EVENT_RENDER_GRAPHIC:
		eventRenderGraphic();
		break;
	case 6:
		event6();
		break;
	case EVENT_TRAN_IN:
		eventTranIn();
		break;
	case EVENT_TRAN_OUT:
		eventTranOut();
		break;
	}
}

void HomeView::event2()
{
	footer_.renderGraphic();
}

void HomeView::eventRenderGraphic()
{
	//information_.renderGraphic();
	title_.renderGraphic();
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
		ms_->pole_previous_y,
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);

	//socket_right_.renderGraphic();
	//socket_left_.renderGraphic();
	//information_.renderGraphic();
	//title_.renderGraphic();
	footer_.renderGraphic();
	//wallpaper_.renderGraphic();
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
		ms_->pole_previous_y,
		ms_->pole_previous_width,
		ms_->pole_previous_height
	);
	pole_.setVisible(true);

	int16_t item_end_x = (int16_t)(144 / 1.6); // 800x480
	int16_t item_end_y = (int16_t)( -407 / 1.6); // 800x480

	pole_.startZoomAndMoveAnimation(
		item_end_x,
		item_end_y,
		pole_width,
		pole_height,
		cc_.ScreenTranInDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone);

	//socket_right_.beginAnimation(480, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);
	//socket_left_.beginAnimation(192, 421, 96, 180, cc_.SocketAlphaHomeBegin, cc_.ScreenTranInDuration);

	//if (!is_out_r)
	//{
	//	plugin_right_.beginAnimation(510, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranInDuration);
	//}
	//else
	//{
	//	plugin_right_.beginAnimation(510 + 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranInDuration);
	//}

	//if (!is_out_l)
	//{
	//	plugin_left_.beginAnimation(-129, -254 + POLE_DEBUG_Y_SHIFT, 387, 1779, 255, cc_.ScreenTranInDuration);
	//}
	//else
	//{
	//	plugin_left_.beginAnimation(-129 - (981 - 387) - 93, -254 + POLE_DEBUG_Y_SHIFT, 981, 1755, 255, cc_.ScreenTranInDuration);
	//}

	title_.setInAnimationDuration(cc_.ScreenTranInDuration);
	title_.beginTransitionNextInAnimation(ms_->ux_screen_id_next);

	footer_.beginSlideAnimation(AnimationStyle::SLIDE_IN);

	//if (ScreenNumber::SCREEN_PAY_RFID == ms_->ux_screen_id_previous ||
	//	ScreenNumber::SCREEN_BOOT == ms_->ux_screen_id_previous ||
	//	ScreenNumber::SCREEN_STANDBY == ms_->ux_screen_id_previous ||
	//	ScreenNumber::SCREEN_WELCOME == ms_->ux_screen_id_previous)
	//{
	//	socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN_FROM_BOTTON, true);
	//}
	//else
	//{
	//	if (ChargeSocketSelected::CHARGE_SOCKET_RIGHT == ms_->operation_charge_socket_selected)
	//	{
	//		socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN, true);
	//	}
	//	else if (ChargeSocketSelected::CHARGE_SOCKET_LEFT == ms_->operation_charge_socket_selected)
	//	{
	//		socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN, false);
	//	}
	//	else
	//	{
	//		socket_slider_.beginSlideAnimation(AnimationStyle::SLIDE_IN_FROM_BOTTON, true);
	//	}
	//}
}

void HomeView::eventTranOut()
{
	pole_.startZoomAndMoveAnimation(
		144,
		-407,
		pole_day_width_,
		pole_day_height_,
		cc_.ScreenTranOutDuration,
		ZoomAnimationImage::FIXED_LEFT_AND_TOP,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone,
		EasingEquations::linearEaseNone, EasingEquations::linearEaseNone);

	title_.setOutAnimationDuration(cc_.ScreenTranOutDuration);
	title_.beginTransitionOutAnimation();

	footer_.setAnimationDuration(cc_.ScreenTranOutDuration);
	footer_.beginSlideAnimation(AnimationStyle::STATIC_IN);
}
