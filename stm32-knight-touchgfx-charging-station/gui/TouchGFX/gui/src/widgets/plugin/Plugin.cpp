#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/widgets/plugin/Plugin.hpp>

Plugin::Plugin(bool is_mirrored, MachineStatus *machine_status)
	:
	is_mirrored_(false),
	is_inoutexg_(false),
	ms_(nullptr),
	alpha_(255),
	alpha_delta_(0),
	plugin_mask_alpha_(255),
	event_trigger_callback_(this, &Plugin::eventTriggerHandler),
	item_zoom_animation_ended_callback_(this, &Plugin::itemZoomAnimationEndedHandler)
{
}

Plugin::~Plugin()
{	
	saveMachineStatus();	
}

void Plugin::initialize(MachineStatus* status, bool is_mirrored)
{
	ms_ = status;
	is_mirrored_ = is_mirrored;

	if (!is_mirrored)
	{
		ux_plugin_in_out_status_prev_ = ms_->ux_plugin_in_out_status_right;
		ux_plugin_usability_status_prev_ = ms_->ux_plugin_usability_status_right;
	}
	else
	{
		ux_plugin_in_out_status_prev_ = ms_->ux_plugin_in_out_status_left;
		ux_plugin_usability_status_prev_ = ms_->ux_plugin_usability_status_left;
	}
	
	plugin_.setAnimationEndedCallback(item_zoom_animation_ended_callback_);
	add(plugin_);

	add(plugin_mask_);

	em_.setEventTriggerCallback(event_trigger_callback_);
	add(em_);

	renderGraphic();

	em_.addAlwaysKeepEvent(1, 1);
}

void Plugin::renderGraphic()
{
	if (UXCommandStatus::UX_COMMAND_ON == ms_->ux_output_command_trigger)
	{
		return;
	}

	ms_->plugin_right_image_id_small = getBitmapPluginIdSmall();
	ms_->plugin_right_image_id_large = getBitmapPluginIdLarge();
	plugin_.setBitmaps(
		Bitmap(ms_->plugin_right_image_id_small),
		Bitmap(ms_->plugin_right_image_id_large)
	);

	if (!is_mirrored_)
	{
		if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
		{
			plugin_.setPosition(
				getBitmapPluginX(),
				getBitmapPluginY(),
				ms_->plugin_right_width,
				ms_->plugin_right_height);
			plugin_.setAlpha(ms_->plugin_right_alpha);
		}
		//else if (
		//	ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		//{
		//	plugin_.setPosition(
		//		PLUGIN_HOME_IN_X_OG_RIGHT_,
		//		PLUGIN_HOME_IN_Y_OG_,
		//		PLUGIN_HOME_IN_W_OG_,
		//		PLUGIN_HOME_IN_H_OG_);
		//	plugin_.setAlpha(ms_->plugin_right_alpha);
		//}
		else
		{
			plugin_.setPosition(
				ms_->plugin_right_x,
				ms_->plugin_right_y,
				ms_->plugin_right_width,
				ms_->plugin_right_height);
			plugin_.setAlpha(ms_->plugin_right_alpha);
		}
	}
	else
	{
		if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
		{
			plugin_.setPosition(
				getBitmapPluginX(),
				getBitmapPluginY(),
				ms_->plugin_left_width,
				ms_->plugin_left_height);
			plugin_.setAlpha(ms_->plugin_left_alpha);
		}
		//else if (
		//	ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
		//	ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		//{
		//	plugin_.setPosition(
		//		PLUGIN_HOME_IN_X_OG_LEFT_,
		//		PLUGIN_HOME_IN_Y_OG_,
		//		PLUGIN_HOME_IN_W_OG_,
		//		PLUGIN_HOME_IN_H_OG_);
		//	plugin_.setAlpha(ms_->plugin_left_alpha);
		//}
		else
		{
			plugin_.setPosition(
				ms_->plugin_left_x,
				ms_->plugin_left_y,
				ms_->plugin_left_width,
				ms_->plugin_left_height);
			plugin_.setAlpha(ms_->plugin_left_alpha);
		}
	}

	plugin_.invalidate();
}

void Plugin::beginAnimation(int end_x, int end_y, int end_width, int end_height, int end_alpha, int duration)
{
	if (ms_ == nullptr) return;

	duration_ = duration == 0 ? 1 : duration;

	plugin_.startZoomAndMoveAnimation(end_x, end_y, end_width, end_height, duration);
}

void Plugin::saveMachineStatus() 
{
	if (!is_mirrored_)
	{
		ms_->plugin_right_x = plugin_.getX();
		ms_->plugin_right_y = plugin_.getY();
		ms_->plugin_right_width = plugin_.getWidth();
		ms_->plugin_right_height = plugin_.getHeight();
		ms_->plugin_right_alpha = plugin_.getAlpha();
		ms_->plugin_right_image_id_small = plugin_.getSmallBitmap().getId();
		ms_->plugin_right_image_id_large = plugin_.getLargeBitmap().getId();
	}
	else
	{
		ms_->plugin_left_x = plugin_.getX();
		ms_->plugin_left_y = plugin_.getY();
		ms_->plugin_left_width = plugin_.getWidth();
		ms_->plugin_left_height = plugin_.getHeight();
		ms_->plugin_left_alpha = plugin_.getAlpha();
		ms_->plugin_left_image_id_small = plugin_.getSmallBitmap().getId();
		ms_->plugin_left_image_id_large = plugin_.getLargeBitmap().getId();
	}
}

void Plugin::itemZoomAnimationEndedHandler(const ZoomAnimationImage& source)
{
	saveMachineStatus();
}

void Plugin::eventTriggerHandler(const int source)
{
	switch (source)
	{
	case 1:
		event1();
		break;
	//case 2:
	//	event2();
	//	break;
	//case 3:
	//	event3();
	//	break;
	//case 4:
	//	event4();
	//	break;
	//case 5:
	//	event5();
	//	break;
	//case 6:
	//	event6();
	//	break;
	//case 7:
	//	event7();
	//	break;
	//case 8:
	//	event8();
	//	break;
	//case 9:
	//	event9();
	//	break;
	//case 20:
	//	event20();
	//	break;
	case 30:
		event30();
		break;
	case 31:
		event31();
		break;
	case 32:
		event32();
		break;
	case 33:
		event33();
		break;
	case 34:
		event34();
		break;
	//case 35:
	//	event35();
	//	break;
	//case 36:
	//	event36();
	//	break;
	//case 39:
	//	event39(); //Dev
	//	break;
	}
}

void Plugin::event1()
{
	bool value_changed = false;

	if (!is_mirrored_)
	{
		if (ux_plugin_in_out_status_prev_ != ms_->ux_plugin_in_out_status_right ||
			ux_plugin_usability_status_prev_ != ms_->ux_plugin_usability_status_right)
		{
			//ms_->plugin_right_x = getBitmapPluginX();
   //         ms_->plugin_right_y = getBitmapPluginY();
   //         ms_->plugin_right_width = getBitmapPluginWidth();
   //         ms_->plugin_right_height = getBitmapPluginHeight();
			ms_->plugin_right_x = plugin_.getX();
			ms_->plugin_right_y = plugin_.getY();
			ms_->plugin_right_width = plugin_.getWidth();
			ms_->plugin_right_height = plugin_.getHeight();
			ms_->plugin_right_alpha = plugin_.getAlpha();
			ms_->plugin_right_image_id_small = plugin_.getSmallBitmap().getId();
			ms_->plugin_right_image_id_large = plugin_.getLargeBitmap().getId();

			value_changed = true;
		}
	}
	else
	{
		if (ux_plugin_in_out_status_prev_ != ms_->ux_plugin_in_out_status_left ||
			ux_plugin_usability_status_prev_ != ms_->ux_plugin_usability_status_left)
		{
			ms_->plugin_left_x = plugin_.getX();
			ms_->plugin_left_y = plugin_.getY();
			ms_->plugin_left_width = plugin_.getWidth();
			ms_->plugin_left_height = plugin_.getHeight();
			ms_->plugin_left_alpha = plugin_.getAlpha();
			ms_->plugin_left_image_id_small = plugin_.getSmallBitmap().getId();
			ms_->plugin_left_image_id_large = plugin_.getLargeBitmap().getId();

			value_changed = true;
		}
	}

	if (value_changed)
	{
		bool  is_out = false;
		bool is_out_prev = false;
		if (!is_mirrored_)
		{
			is_out = ms_->ux_plugin_in_out_status_right;
		}
		else
		{
			is_out = ms_->ux_plugin_in_out_status_left;
		}
		is_out_prev = ux_plugin_in_out_status_prev_;

		if (is_out != is_out_prev)
		{
			is_inoutexg_ = true;
		}
		else
		{
			is_inoutexg_ = false;
		}

		em_.addLoopChainEvent(30, 1, 31);
	}

	if (!is_mirrored_)
	{
		ux_plugin_in_out_status_prev_ = ms_->ux_plugin_in_out_status_right;
		ux_plugin_usability_status_prev_ = ms_->ux_plugin_usability_status_right;
	}
	else
	{
		ux_plugin_in_out_status_prev_ = ms_->ux_plugin_in_out_status_left;
		ux_plugin_usability_status_prev_ = ms_->ux_plugin_usability_status_left;
	}
}

void Plugin::event30()
{
	plugin_mask_.setVisible(true);
	plugin_mask_.setBitmaps(
		Bitmap(plugin_.getSmallBitmap().getId()),
		Bitmap(plugin_.getLargeBitmap().getId())
	);
	plugin_mask_.setPosition(
		plugin_.getX(),
		plugin_.getY(),
		plugin_.getWidth(),
		plugin_.getHeight());
	plugin_mask_.setAlpha(plugin_.getAlpha());

	plugin_mask_.invalidate();
}

void Plugin::event31()
{
	plugin_.setVisible(true);
	plugin_.setBitmaps(
		Bitmap(getBitmapPluginIdSmall()),
		Bitmap(getBitmapPluginIdLarge())
	);
	int xs = plugin_mask_.getX();
	if (is_inoutexg_)
	{
		xs += getBitmapPluginPositionShift();
	}
	int w = getBitmapPluginWidth();
	int y = getBitmapPluginHeight();
	plugin_.setPosition(
		xs,
		plugin_mask_.getY(),
		getBitmapPluginWidth(),
		getBitmapPluginHeight());
	plugin_.setAlpha(0);

	plugin_.invalidate();

	if (!is_mirrored_)
	{
		ms_->plugin_right_alpha = 0;
	}
	else
	{
		ms_->plugin_left_alpha = 0;
	}

	plugin_mask_alpha_ = plugin_mask_.getAlpha();

	em_.addLoopChainEvent(32, ANIMATION_PLUGIN_EXG_DURATION, 33);
}

void Plugin::event32()
{
	int ad = 255 / ANIMATION_PLUGIN_EXG_DURATION;
	if (ad == 0) ad = 1;

	if (!is_mirrored_)
	{
		if ((ms_->plugin_right_alpha + ad) <= alpha_)
		{
			ms_->plugin_right_alpha += ad;
			plugin_.setAlpha(ms_->plugin_right_alpha);
			plugin_.invalidate();
		}
	}
	else
	{
		if ((ms_->plugin_left_alpha + ad) <= alpha_)
		{
			ms_->plugin_left_alpha += ad;
			plugin_.setAlpha(ms_->plugin_left_alpha);
			plugin_.invalidate();
		}
	}

	if ((plugin_mask_alpha_ - ad) >= 0)
	{
		plugin_mask_alpha_ -= ad;
		plugin_mask_.setAlpha(plugin_mask_alpha_);
		plugin_mask_.invalidate();
	}
}

void Plugin::event33()
{
	plugin_mask_.setVisible(false);
	plugin_mask_.invalidate();
	
	saveMachineStatus();
}

void Plugin::event34()
{
}

int Plugin::getBitmapPluginIdSmall()
{
	if (!is_mirrored_)
	{
		if (ms_->ux_plugin_in_out_status_right == UXPlugInOutStatus::UX_PLUGIN_IN)
		{
			if (ms_->ux_plugin_usability_status_right == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_IN_RIGHT_BLUE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_IN_RIGHT_BLACK_ID;
			}
		}
		else
		{
			if (ms_->ux_plugin_usability_status_right == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_OUT_RIGHT_BLUE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_OUT_RIGHT_BLACK_ID;
			}
		}
	}
	else
	{
		if (ms_->ux_plugin_in_out_status_left == UXPlugInOutStatus::UX_PLUGIN_IN)
		{
			if (ms_->ux_plugin_usability_status_left == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_IN_LEFT_BLUE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_IN_LEFT_BLACK_ID;
			}
		}
		else
		{
			if (ms_->ux_plugin_usability_status_left == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_OUT_LEFT_BLUE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_OUT_LEFT_BLACK_ID;
			}
		}
	}
}

int Plugin::getBitmapPluginIdLarge()
{
	if (!is_mirrored_)
	{
		if (ms_->ux_plugin_in_out_status_right == UXPlugInOutStatus::UX_PLUGIN_IN)
		{
			if (ms_->ux_plugin_usability_status_right == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_IN_RIGHT_BLUE_LARGE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_IN_RIGHT_BLACK_LARGE_ID;
			}
		}
		else
		{
			if (ms_->ux_plugin_usability_status_right == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_OUT_RIGHT_BLUE_LARGE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_OUT_RIGHT_BLACK_LARGE_ID;
			}
		}
	}
	else
	{

		if (ms_->ux_plugin_in_out_status_left == UXPlugInOutStatus::UX_PLUGIN_IN)
		{
			if (ms_->ux_plugin_usability_status_left == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_IN_LEFT_BLUE_LARGE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_IN_LEFT_BLACK_LARGE_ID;
			}
		}
		else
		{
			if (ms_->ux_plugin_usability_status_left == UXPlugUsabilityStatus::UX_PLUGIN_BLUE)
			{
				return BITMAP_PLUGIN_OUT_LEFT_BLUE_LARGE_ID;
			}
			else
			{
				return BITMAP_PLUGIN_OUT_LEFT_BLACK_LARGE_ID;
			}
		}
	}
}

int Plugin::getBitmapPluginPositionShift()
{
	bool is_out = false;
	
	if (!is_mirrored_)
	{
		is_out = ms_->ux_plugin_in_out_status_right;
	}
	else
	{
		is_out = ms_->ux_plugin_in_out_status_left;
	}

	if (!is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			if (!is_mirrored_)
			{
				return -31 * 3;
			}
			else
			{
				return 981 + 31 * 3 - 387;
			}
		}
		else
		{
			if (!is_mirrored_)
			{
				return -31;
			}
			else
			{
				return 327 + 31 - 129;
			}
		}
	}
	else if (is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			if (!is_mirrored_) 
			{
				return 31 * 3;
			}
			else
			{
				return -981 - 31 * 3 + 387;
			}
		}
		else
		{
			if (!is_mirrored_)
			{
				return 31;
			}
			else
			{
				return -327 - 31 + 129;
			}
		}
	}

	return 31;
}

int16_t Plugin::getBitmapPluginX()
{
	bool is_out = false;

	if (!is_mirrored_)
	{
		is_out = ms_->ux_plugin_in_out_status_right;
	}
	else
	{
		is_out = ms_->ux_plugin_in_out_status_left;
	}

	if (!is_out)
	{
		if (!is_mirrored_) 
		{
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				return 868;
			}
			else if (
				ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
				ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current)
			{
				return 510;
			}
		}
		else
		{
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				return -487;
			}
			else if (
				ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
				ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current)
			{
				return -487 + 358;
			}
		}
	}
	else if (is_out)
	{
		if (!is_mirrored_)
		{
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				return 868 + PLUGIN_RIGHT_LARGE_X_SHIFT_;
			}
		}
		else
		{
			if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
			{
				return -487 - PLUGIN_LEFT_LARGE_X_SHIFT_;
			}
		}
	}

	return 0;
}

int16_t Plugin::getBitmapPluginY()
{
	if (ScreenNumber::SCREEN_INTRO == ms_->ux_screen_id_current)
	{
		return -254;
	}

	return 0;
}

int Plugin::getBitmapPluginWidth()
{
	bool is_out = false;

	if (!is_mirrored_)
	{
		is_out = ms_->ux_plugin_in_out_status_right;
	}
	else
	{
		is_out = ms_->ux_plugin_in_out_status_left;
	}

	if (!is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			return 387;
		}
		else
		{
			return 129;
		}
	}
	else if (is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			return 981;
		}
		else
		{
			return 327;
		}
	}

	return 327;
}

int Plugin::getBitmapPluginHeight()
{
	bool is_out = false;

	if (!is_mirrored_)
	{
		is_out = ms_->ux_plugin_in_out_status_right;
	}
	else
	{
		is_out = ms_->ux_plugin_in_out_status_left;
	}

	if (!is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			return 1779;
		}
		else
		{
			return 593;
		}
	}
	else if (is_out)
	{
		if (ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_1 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_5 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_6 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_7 == ms_->ux_screen_id_current ||
			ScreenNumber::SCREEN_PAYMENT == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_2 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_3_3 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_36 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_37 == ms_->ux_screen_id_current ||
			ScreenNumber::SCENARIO_2_38 == ms_->ux_screen_id_current)
		{
			return 1755;
		}
		else
		{
			return 585;
		}		
	}

	return 585;
}