#ifndef BASE_VIEW_HPP
#define BASE_VIEW_HPP

#ifdef __cplusplus
extern "C"
{
#endif 

#include "external.h"

#ifdef __cplusplus
}
#endif 

#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/Color.hpp>
#include <mvp/View.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/common/BaseViewInterface.hpp>
#include <gui/common/CommonConstant.hpp>
#include <gui/common/CommonFunction.h>
#include <gui/common/EventManager.hpp>
#include <gui/model/Model.hpp>
#include <gui/widgets/information/Information.hpp>
#include <gui/widgets/info/AbstractMessage.hpp>
#include <gui/widgets/info/MessageBlue.hpp> 
#include <gui/widgets/info/MessageRed.hpp> 
#include <gui/widgets/info/MessageYellow.hpp> 

using namespace touchgfx;

template <class T, class U>
class BaseView : public U, public BaseViewInterface
{
public:	
	BaseView()
		:
		count_filter_(0),
		message_ptr_c_(0),
		message_(nullptr)
	{		
		pole_day_width_ = Bitmap(BITMAP_POLE_DAY_ID).getWidth();
		pole_day_height_ = Bitmap(BITMAP_POLE_DAY_ID).getHeight();
	}

	virtual ~BaseView()
	{
		U::View<T>::~View();
	}

	void setMessageAction(void *open, void *close)
	{
		this->pv1_ = open;
		this->pv2_ = close;
	}
	T* getPresenter()
	{
		struct FriendView : public touchgfx::View<T>
		{
			using touchgfx::View<T>::presenter;
		};

		return static_cast<FriendView*>(this)->presenter;
	}
	virtual void setupScreen()
	{
		ms_ = View<T>::presenter->getMachineStatus();
		//ms_ = static_cast<View<T>*>(this)->presenter->getMachineStatus();
		//ms_ = static_cast<View<T>>(U)::View<T>::presenter->getMachineStatus();
		//ms_ = static_cast<touchgfx::View<T>*>(this)->presenter->getMachineStatus();
		//ms_ = getPresenter()->getMachineStatus();
	}

	virtual void afterSetupScreen()
	{
#ifdef SIMULATOR          
		//Element		
		version_.setPosition(580, 2, 202, 28);
		version_.setAlpha(255);
		version_.setColor(Color::getColorFromRGB(255, 0, 0));
		version_.setLinespacing(0);
		version_.setTypedText(TypedText(T_FOOTER_MONEY));
		char fv[] = VERSION_NUMBER;
		int tl = sizeof(fv) / sizeof(const char);
		char version_str[] = "v1.0.0.12345678";
		int tl2 = sizeof(version_str) / sizeof(const char);
		for (int i = 0; i <= 8; i++)
		{
			int v1 = tl - 9 + i;
			int v2 = tl2 - 9 + i;
			version_str[v2] = fv[v1];
		}
		int version_str_len = sizeof(version_str);
		version_buffer_[version_str_len - 1] = 0;
		Unicode::strncpy(version_buffer_, version_str, version_str_len);
		version_.setWildcard(version_buffer_);

		BaseView<T, U>::add(version_);
#endif
		
		//Element
		left_top_mask_.setPosition(0, 0, 120, 120);
		left_top_mask_.setAlpha(0);
		left_top_mask_.setVisible(false);
		left_top_mask_.setTouchable(false);
		BaseView<T, U>::add(left_top_mask_);

		//Element
		left_top_mask2_.setPosition(120, 0, 200, 120);
		left_top_mask2_.setAlpha(0);
		left_top_mask2_.setVisible(false);
		left_top_mask2_.setTouchable(false);
		BaseView<T, U>::add(left_top_mask2_);

		//Element
		right_top_mask_.setPosition(650, 0, 120, 120);
        right_top_mask_.setAlpha(0);
        right_top_mask_.setVisible(false);
        right_top_mask_.setTouchable(false);
		BaseView<T, U>::add(right_top_mask_);

		mask_back_bottom_.setPosition(50, 700, HAL::DISPLAY_WIDTH, 324);
		mask_back_bottom_.setAlpha(0);
		mask_back_bottom_.setVisible(false);
		mask_back_bottom_.setTouchable(false);
		BaseView<T, U>::add(mask_back_bottom_);

		//Element
		mask_full_view_.setPosition(0, 0, HAL::DISPLAY_WIDTH, HAL::DISPLAY_HEIGHT);
		mask_full_view_.setAlpha(0);
		mask_full_view_.setVisible(true);
		mask_full_view_.setTouchable(true);
		BaseView<T, U>::add(mask_full_view_);

		//Element
		BaseView<T, U>::add(em_);

        em_.setReject(47, true);
		em_.addAlwaysKeepEvent(44, 30);
		em_.addAlwaysKeepEvent(48, 1);		

		setMask(MaskList::FULL_MASK, false);
	}

	virtual void afterTransition()
	{
	}

	virtual void tearDownScreen()
	{
		if (1 <= message_ptr_c_)
		{
			delete message_;
			message_ptr_c_--;
		}
	}

protected:
	int16_t count_filter_;
	int16_t count_filter_pop_;
	int16_t pole_day_width_;
	int16_t pole_day_height_;
	ScreenNumber id_;

	CommonConstant& cc_ = CommonConstant::getInstance();
	EventManager em_;
	MachineStatus *ms_;
	AbstractMessage *message_;
	int message_ptr_c_;
	
	Box left_top_mask_;
	Box left_top_mask2_;
	Box right_top_mask_;
	Box mask_back_bottom_;
	Box mask_full_view_;
	static const uint16_t TEXT_SIZE_14 = 14;
	TextAreaWithOneWildcard version_;
	Unicode::UnicodeChar version_buffer_[TEXT_SIZE_14];	

	void *pv1_;
	void *pv2_;

	virtual void updateMachineStatus(MachineStatus* status)
	{
	}

	virtual void updateGraphic()
	{
	}

	virtual void enablePopups() 
	{
	}


	enum MaskList
	{
		FULL_MASK,
		LANGUAGE_MASK,
		INFO_MASK
	};

	virtual void setMask(MaskList mask, bool enable)
	{
		switch (mask)
		{
		case MaskList::FULL_MASK:
			left_top_mask_.setVisible(enable);
			left_top_mask_.setTouchable(enable);
			left_top_mask2_.setVisible(enable);
			left_top_mask2_.setTouchable(enable);
			right_top_mask_.setVisible(enable);
			right_top_mask_.setTouchable(enable);
			mask_back_bottom_.setVisible(enable);
			mask_back_bottom_.setTouchable(enable);
			mask_full_view_.setVisible(enable);
			mask_full_view_.setTouchable(enable);
			break;
		case MaskList::LANGUAGE_MASK:
			left_top_mask_.setVisible(enable);
			left_top_mask_.setTouchable(enable);
			left_top_mask2_.setVisible(!enable);
			left_top_mask2_.setTouchable(!enable);
			right_top_mask_.setVisible(enable);
			right_top_mask_.setTouchable(enable);
			mask_back_bottom_.setVisible(enable);
			mask_back_bottom_.setTouchable(enable);
			mask_full_view_.setVisible(false);
			mask_full_view_.setTouchable(false);
			break;
		case MaskList::INFO_MASK:
			left_top_mask_.setVisible(!enable);
			left_top_mask_.setTouchable(!enable);
			left_top_mask2_.setVisible(enable);
			left_top_mask2_.setTouchable(enable);
			right_top_mask_.setVisible(enable);
			right_top_mask_.setTouchable(enable);
			mask_back_bottom_.setVisible(enable);
			mask_back_bottom_.setTouchable(enable);
			mask_full_view_.setVisible(false);
			mask_full_view_.setTouchable(false);
		default:
			break;
		}
	}

	virtual void changeScreen(ScreenNumber id)
	{		
		id_ = id;
		
		em_.addCountDownEvent(49, cc_.After2Tick);
	}

#pragma region Communication Command
	virtual void sendCommandReturn()
	{
		if (nullptr != ms_)
		{
			ms_->ux_screen_id_next = ms_->ux_screen_id_previous;						
			ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
			ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;
		}
	}

	virtual void sendCommand(ScreenNumber next)
	{
		if (nullptr != ms_)
		{			
			ms_->ux_screen_id_next = next;
			ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_ON;
			ms_->ux_screen_status = UXScreenStatus::UX_NOT_OPERABLE;
		}
	}

	virtual void completedCommand()
	{
		if (nullptr != ms_)
		{			
			ms_->ux_screen_id_previous = ms_->ux_screen_id_current;
			ms_->ux_screen_id_current = ms_->ux_screen_id_next;
			ms_->ux_screen_id_next = ScreenNumber::NULL_SCREEN;
			ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_END;
			ms_->ux_screen_status = UXScreenStatus::UX_OPERABLE;

			em_.addCountDownEvent(43, 1);
		}		
	}

	virtual void saveCommand()
	{		
		ms_->ux_screen_id_current_bk1 = ms_->ux_screen_id_current;
		ms_->ux_screen_id_previous_bk1 = ms_->ux_screen_id_previous;
		ms_->ux_screen_id_next_bk1 = ms_->ux_screen_id_next;
	}

	virtual void loadCommand()
	{
		ms_->ux_screen_id_current = ms_->ux_screen_id_current_bk1;
		ms_->ux_screen_id_previous = ms_->ux_screen_id_previous_bk1;
		ms_->ux_screen_id_next = ms_->ux_screen_id_next_bk1;
	}
#pragma endregion Communication Command

	virtual void event43() final
	{
		ms_->ux_output_command_trigger = UXCommandStatus::UX_COMMAND_OFF;
	}

	virtual void event44() final
	{
		event47();
	}

	virtual void event45() final
	{
		if (!ms_->popup_opened && nullptr == message_ &&
			0 != ms_->ux_popup_number)
		{			
			em_.setReject(45, true);
			em_.setReject(47, false);

			setMask(MaskList::FULL_MASK, true);
			ms_->ux_popup_number_bk1 = ms_->ux_popup_number;

			switch (ms_->ux_popup_number)
			{
			case MessageNumber::MESSAGE_21:
			case MessageNumber::MESSAGE_22:
			case MessageNumber::MESSAGE_23:
			case MessageNumber::MESSAGE_25:
			case MessageNumber::MESSAGE_27:
			case MessageNumber::MESSAGE_28:
			case MessageNumber::MESSAGE_31:
			case MessageNumber::MESSAGE_32:
			case MessageNumber::MESSAGE_33:
			case MessageNumber::MESSAGE_44:
			case MessageNumber::MESSAGE_51:
			case MessageNumber::MESSAGE_54:
				if (0 == message_ptr_c_) 
				{
					message_ = new MessageBlue();
					message_ptr_c_++;
				}
				break;
			case MessageNumber::MESSAGE_24:
			case MessageNumber::MESSAGE_26:
				if (0 == message_ptr_c_)
				{
					message_ = new MessageYellow();
					message_ptr_c_++;
				}
				break;
			case MessageNumber::MESSAGE_E1:
			case MessageNumber::MESSAGE_E2:
			case MessageNumber::MESSAGE_E3:
			case MessageNumber::MESSAGE_E4:
			case MessageNumber::MESSAGE_E5:
			case MessageNumber::MESSAGE_E6:
			default:
				if (0 == message_ptr_c_)
				{
					message_ = new MessageRed();
					message_ptr_c_++;
				}
				break;
			}

			message_->setPosition(65, 140, 638, 838 + 20);
			message_->setAnimationDuration(ms_->ux_pop_tran_in_time);
			message_->setOpenCompletedCallback(*(GenericCallback<const int> *)pv1_);
			message_->setCloseCompletedCallback(*(GenericCallback<const int> *)pv2_);
			BaseView<T, U>::add(*message_);

			switch (ms_->ux_popup_number)
			{
			case MessageNumber::MESSAGE_21:
				sendCommand(ScreenNumber::SCENARIO_2_1);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0201);
				break;
			case MessageNumber::MESSAGE_22:
				sendCommand(ScreenNumber::SCENARIO_2_2);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0202);
				break;
			case MessageNumber::MESSAGE_23:
				sendCommand(ScreenNumber::SCENARIO_2_3);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0203);
				break;
			case MessageNumber::MESSAGE_24:
				sendCommand(ScreenNumber::SCENARIO_2_4);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0204);
				break;
			case MessageNumber::MESSAGE_25:
				sendCommand(ScreenNumber::SCENARIO_2_5);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0205);
				break;
			case MessageNumber::MESSAGE_26:
				sendCommand(ScreenNumber::SCENARIO_2_6);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0206);
				break;
			case MessageNumber::MESSAGE_27:
				sendCommand(ScreenNumber::SCENARIO_2_7);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0207);
				break;
			case MessageNumber::MESSAGE_28:
				sendCommand(ScreenNumber::SCENARIO_2_8);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0208);
				break;
			case MessageNumber::MESSAGE_31:
				sendCommand(ScreenNumber::SCENARIO_2_36);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0301);
				break;
			case MessageNumber::MESSAGE_32:
				sendCommand(ScreenNumber::SCENARIO_2_37);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0301);
				break;
			case MessageNumber::MESSAGE_33:
				sendCommand(ScreenNumber::SCENARIO_2_38);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0301);
				break;
			case MessageNumber::MESSAGE_44:
				sendCommand(ScreenNumber::SCENARIO_4_4);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0404);
				break;
			case MessageNumber::MESSAGE_51:
				sendCommand(ScreenNumber::SCENARIO_5_1);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0501);
				break;
			case MessageNumber::MESSAGE_54:
				sendCommand(ScreenNumber::SCENARIO_5_4);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_0504);
				break;			
			case MessageNumber::MESSAGE_E2:
				sendCommand(ScreenNumber::SCENARIO_9_2);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E2);
				break;
			case MessageNumber::MESSAGE_E3:
				sendCommand(ScreenNumber::SCENARIO_9_3);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E3);
				break;
			case MessageNumber::MESSAGE_E4:
				sendCommand(ScreenNumber::SCENARIO_9_4);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E4);
				break;
			case MessageNumber::MESSAGE_E5:
				sendCommand(ScreenNumber::SCENARIO_9_5);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E5);
				break;
			case MessageNumber::MESSAGE_E6:
				sendCommand(ScreenNumber::SCENARIO_9_6);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E6);
				break;
			case MessageNumber::MESSAGE_E1:
			default:
				sendCommand(ScreenNumber::SCENARIO_9_1);
				message_->initialize(ms_, AbstractMessage::ContentType::CONTENT_E1);
				break;			
			}

			ms_->ux_return_value = ReturnValue::RETURN_NONE;
									
			message_->open(ANIMATION_MESSAGE_IN_DURATION);
		}
	}

	virtual void event46() final
	{
		if (ms_->popup_opened && nullptr != message_)
		{
			ms_->ux_popup_number = ms_->ux_popup_number_bk1;
			sendCommandReturn();
			message_->close(ms_->ux_pop_tran_out_time);			
		}
	}

	virtual void event47() final
	{
		if (!ms_->popup_opened && nullptr != message_)
		{
			em_.setReject(45, false);
			em_.setReject(47, true);

			BaseView<T, U>::remove(*message_);
			
			if (1 <= message_ptr_c_)
			{				
				delete message_;
				message_ptr_c_--;
			}
			message_ = nullptr;
			
			setMask(MaskList::FULL_MASK, false);
			ms_->ux_popup_trigger_ = false;
		}
	}

	virtual void event48() final
	{
		if (1 <= count_filter_)
		{
			count_filter_--;
		}

		if (1 <= count_filter_pop_)
		{
			count_filter_pop_--;
		}

		if (ms_->ux_change_screen_prev != ms_->ux_change_screen)
		{
			if (ScreenNumber::SCREEN_HOME == ms_->ux_change_screen)
			{
				sendCommand(ScreenNumber::SCREEN_HOME);
				changeScreen((ScreenNumber)ms_->ux_change_screen);
			}
			else if (ScreenNumber::SCREEN_PAYMENT == ms_->ux_change_screen)
			{
				sendCommand(ScreenNumber::SCENARIO_2_30);
				changeScreen((ScreenNumber)ms_->ux_change_screen);
			}
			else if (ScreenNumber::SCREEN_PAY_RFID == ms_->ux_change_screen)
			{
				sendCommand(ScreenNumber::SCENARIO_4_1);
				changeScreen((ScreenNumber)ms_->ux_change_screen);
			}
			else if (ScreenNumber::SCREEN_STANDBY == ms_->ux_change_screen)
			{
				sendCommand(ScreenNumber::SCREEN_STANDBY);
				changeScreen((ScreenNumber)ms_->ux_change_screen);
			}
			else if (ScreenNumber::SCREEN_INTRO == ms_->ux_change_screen)
			{
				sendCommand(ScreenNumber::SCREEN_INTRO);
				changeScreen((ScreenNumber)ms_->ux_change_screen);
			}
		}

		if (ms_->ux_close_popup_prev != ms_->ux_close_popup &&
			1 == ms_->ux_close_popup &&
			1 <= message_ptr_c_)
		{
			em_.addOneTimeEvent(46);
		}
	}

	virtual void event49() final
	{
		static_cast<FrontendApplication*>(Application::getInstance())->gotoScreen(id_);		
	}

#pragma region Style Resource
	const uint16_t getPoleBitmapSmall()
	{
		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			return BITMAP_POLE_NIGHT_SMALL_ID;
		}

		return BITMAP_POLE_DAY_SMALL_ID;
	}

	const uint16_t getPoleBitmapLarge()
	{
		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			return BITMAP_POLE_NIGHT_ID;
		}

		return BITMAP_POLE_DAY_ID;
	}

	const uint8_t getDayBlockNightWhiteR()
	{
		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			return 255;
		}

		return 0;
	}

	const uint8_t getDayBlockNightWhiteG()
	{
		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			return 255;
		}

		return 0;
	}

	const uint8_t getDayBlockNightWhiteB()
	{
		if (WeatherStyle::NIGHT == ms_->ux_weather)
		{
			return 255;
		}

		return 0;
	}

	const uint8_t getSocketRightAlpha()
	{
		if (ms_->operation_charge_socket_selected == ChargeSocketSelected::CHARGE_SOCKET_RIGHT)
		{
			return cc_.SocketAlphaGeneral;
		}

		return cc_.SocketAlphaHomeBegin;
	}

	const uint8_t getSocketLeftAlpha()
	{
		if (ms_->operation_charge_socket_selected == ChargeSocketSelected::CHARGE_SOCKET_LEFT)
		{
			return cc_.SocketAlphaGeneral;
		}

		return cc_.SocketAlphaHomeBegin;
	}
#pragma endregion Style Resource
};
#endif