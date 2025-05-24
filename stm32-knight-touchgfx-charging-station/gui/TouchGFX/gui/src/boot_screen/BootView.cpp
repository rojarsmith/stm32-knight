#include <gui/boot_screen/BootView.hpp>

#include <Bitmapdatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>
#include <gui/common/CommonConstant.hpp>

BootView::BootView()
	:
	event_trigger_callback_(this, &BootView::eventTriggerHandler)
{

}

void BootView::setupScreen()
{
	BaseView::setupScreen();

	cc_.DisplayWidthHalf = HAL::DISPLAY_WIDTH / 2;
	cc_.DisplayHeightHalf = getFixedDisplayHeight() / 2;
	cc_.TitleX = 0;
    cc_.TitleY = 16;
    cc_.TitleWidth = 480;
    cc_.TitleHeight = 75;
	//cc_.TitleX = 0;
	//cc_.TitleY = 26;
	//cc_.TitleWidth = 768;
	//cc_.TitleHeight = 120;

	ms_->ux_screen_id_previous = ScreenNumber::NULL_SCREEN; //None previous screen.
	ms_->ux_screen_id_current = ScreenNumber::SCREEN_BOOT;
	ms_->ux_screen_id_next = ScreenNumber::NULL_SCREEN;

	ms_->ux_return_value = ReturnValue::RETURN_NONE;

	int pole_width = Bitmap(BITMAP_POLE_DAY_SMALL_ID).getWidth(); //320
	int pole_height = Bitmap(BITMAP_POLE_DAY_SMALL_ID).getHeight(); //1404
	int socket_width = Bitmap(BITMAP_SOCKET_GREEN_RIGHT_ID).getWidth(); //96
	int socket_height = Bitmap(BITMAP_SOCKET_GREEN_RIGHT_ID).getHeight(); //180
	int plugin_width = Bitmap(BITMAP_PLUGIN_IN_RIGHT_BLACK_ID).getWidth(); //387
	int plugin_height = Bitmap(BITMAP_PLUGIN_IN_RIGHT_BLACK_ID).getHeight(); //1779
	int plugin_width_o = Bitmap(BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID).getWidth() * 3; //981
	int plugin_height_o = Bitmap(BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID).getHeight() * 3; //1755
	//int plugin_height_o_shift = 31 * 3;
	int plugin_height_o_shift = 19 * 3; // 800x480

	ms_->ux_drag_selector_vx = 0;
	ms_->ux_drag_selector_x = 0;

	ms_->ux_popup_command_lock = false;
	ms_->ux_popup_command_lock_time = 0;
	ms_->ux_popup_number = MessageNumber::MESSAGE_0;
	ms_->ux_popup_number_virtual = false;
	ms_->operation_charge_socket_selected = ChargeSocketSelected::CHARGE_SOCKET_NONE;

	ms_->pole_previous_x = 140;
	ms_->pole_previous_y = -877;
	//ms_->pole_previous_x = 224;
	//ms_->pole_previous_y = -1404;
	ms_->pole_previous_width = pole_width;
	ms_->pole_previous_height = pole_height;

	ms_->socket_right_previous_x = HAL::DISPLAY_WIDTH;
	ms_->socket_right_previous_y = 263;
	//ms_->socket_right_previous_y = 421;
	ms_->socket_right_previous_width = socket_width;
	ms_->socket_right_previous_height = socket_height;
	ms_->socket_right_previous_alpha = 0;
	ms_->socket_right_image_id_small = BITMAP_SOCKET_GREEN_RIGHT_ID;
	ms_->socket_right_image_id_large = BITMAP_SOCKET_GREEN_RIGHT_LARGE_ID;

	ms_->socket_left_previous_x = -60;
	ms_->socket_left_previous_y = 263;
	//ms_->socket_left_previous_x = 0 - 96;
	//ms_->socket_left_previous_y = 421;
	ms_->socket_left_previous_width = socket_width;
	ms_->socket_left_previous_height = socket_height;
	ms_->socket_left_previous_alpha = 0;
	ms_->socket_left_image_id_small = BITMAP_SOCKET_GREEN_LEFT_ID;
	ms_->socket_left_image_id_large = BITMAP_SOCKET_GREEN_LEFT_LARGE_ID;

	int is_out_r = ms_->ux_plugin_in_out_status_right;
	int if_usability_r = ms_->ux_plugin_usability_status_right;

	if (1 != is_out_r)
	{
		ms_->plugin_right_x = HAL::DISPLAY_WIDTH + 62;
		//ms_->plugin_right_x = HAL::DISPLAY_WIDTH + 100;
		ms_->plugin_right_y = PLUGIN_RIGHT_SCREEN_HOME_ORIGINAL_POINT_Y;
		ms_->plugin_right_width = plugin_width;
		ms_->plugin_right_height = plugin_height;
		ms_->plugin_right_alpha = 255;

		if (0 != if_usability_r)
		{
			ms_->plugin_right_image_id_small = BITMAP_PLUGIN_IN_RIGHT_BLACK_ID;
			ms_->plugin_right_image_id_large = BITMAP_PLUGIN_IN_RIGHT_BLACK_LARGE_ID;
		}
		else
		{
			ms_->plugin_right_image_id_small = BITMAP_PLUGIN_IN_RIGHT_BLUE_ID;
			ms_->plugin_right_image_id_large = BITMAP_PLUGIN_IN_RIGHT_BLUE_LARGE_ID;
		}
	}
	else
	{
		ms_->plugin_right_x = HAL::DISPLAY_WIDTH + plugin_height_o_shift;
		ms_->plugin_right_y = PLUGIN_RIGHT_SCREEN_HOME_ORIGINAL_POINT_Y;
		ms_->plugin_right_width = plugin_width_o;
		ms_->plugin_right_height = plugin_height_o;
		ms_->plugin_right_alpha = 255;
		if (0 != if_usability_r)
		{
			ms_->plugin_right_image_id_small = BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID;
			ms_->plugin_right_image_id_large = BITMAP_PLUGIN_OUT_RIGHT_BLACK_LARGE_ID;
		}
		else
		{
			ms_->plugin_right_image_id_small = BITMAP_PLUGIN_OUT_RIGHT_BLUE_ID;
			ms_->plugin_right_image_id_large = BITMAP_PLUGIN_OUT_RIGHT_BLUE_LARGE_ID;
		}
	}

	ms_->plugin_left_x = -304;
	//ms_->plugin_left_x = -387 - 100;
	ms_->plugin_left_y = PLUGIN_RIGHT_SCREEN_HOME_ORIGINAL_POINT_Y;
	ms_->plugin_left_width = plugin_width;
	ms_->plugin_left_height = plugin_height;
	ms_->plugin_left_alpha = 255;
	ms_->plugin_left_image_id_small = BITMAP_PLUGIN_IN_LEFT_BLACK_ID;
	ms_->plugin_left_image_id_large = BITMAP_PLUGIN_IN_LEFT_BLACK_LARGE_ID;

	ms_->title_alpha = 0;
	ms_->subtitle_alpha = 0;

	ms_->footer_y = 72; // 800x480
	//ms_->footer_y = 116;

	ms_->ux_loading_status = UXLoadingStatus::UX_LOADING_NONE;

	ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_OFF;
	ms_->ux_output_command_trigger_prev = UXCommandStatus::UX_COMMAND_OFF;
	ms_->ux_output_command_trigger_count = 0;
	ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;

#ifdef SIMULATOR
	box1_.setPosition(0, 0, HAL::DISPLAY_WIDTH, cc_.DisplayHeightHalf);
	box1_.setColor(Color::getColorFromRGB(255, 255, 0));

	add(box1_);

	box2_.setPosition(0, cc_.DisplayHeightHalf, HAL::DISPLAY_WIDTH, cc_.DisplayHeightHalf);
	box2_.setColor(Color::getColorFromRGB(255, 0, 0));

	add(box2_);
#endif

	em_.setEventTriggerCallback(event_trigger_callback_);
	em_.addCountDownEvent(EventList::EVENT_SEND_COMMAND, cc_.After1Tick);
}

void BootView::tearDownScreen()
{
	BaseView::tearDownScreen();
}

void BootView::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case EventList::EVENT_SEND_COMMAND:
		eventSendCommand();
		break;
	case EventList::EVENT_CHANGE_SCREEN:
		eventChangeScreen();
		break;
	case 43:
		event43();
		break;
	case 49:
		event49();
		break;
	}
}

void BootView::eventSendCommand()
{
	em_.removeAll();

#ifdef CES2019
	sendCommand(ScreenNumber::SCREEN_HOME);
#else
	sendCommand(ScreenNumber::SCREEN_INTRO);
#endif	

	em_.addCountDownEvent(EventList::EVENT_CHANGE_SCREEN, cc_.After1Tick);
}

void BootView::eventChangeScreen()
{
	em_.removeAll();

	ms_->ui_language = ms_->ux_culture;

	if (LanguageList::ENGISH == ms_->ui_language)
	{
		Texts::setLanguage(LANGUAGES::GB);
	}
	else if (LanguageList::SPANISH == ms_->ui_language)
	{
		Texts::setLanguage(LANGUAGES::SPA);
	}
	else if (LanguageList::GERMAN == ms_->ui_language)
	{
		Texts::setLanguage(LANGUAGES::GER);
	}
	else
	{
		Texts::setLanguage(LANGUAGES::FRE);
	}

#ifdef CES2019
	changeScreen(ScreenNumber::SCREEN_HOME);
#else
	changeScreen(ScreenNumber::SCREEN_INTRO);
#endif
}
