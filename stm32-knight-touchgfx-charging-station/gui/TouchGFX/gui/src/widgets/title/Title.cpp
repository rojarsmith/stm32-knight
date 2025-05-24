#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>
#include <gui/widgets/title/Title.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Title::Title()
	:	
	isInit_(true),
	isTwoLine_(true),
	isTwoLine_prev_(true),
	animation_duration_sub_(60),
	ms_(nullptr),	
	transition_in_animation_ended_callback_(nullptr),
	transition_out_animation_ended_callback_(nullptr),
	textarea_fade_animation_ended_callback_(this, &Title::textareaFadeAnimationEndedHandler)
{	
	animation_duration_in_ = cc_.ScreenTranInDuration;
	animation_duration_out_ = cc_.ScreenTranOutDuration;
}

Title::~Title()
{	
	title_.setAlpha(ms_->title_alpha);
	subtitle_.setAlpha(ms_->subtitle_alpha);
}

void Title::initialize(MachineStatus* status)
{
	ms_ = status;

	add(title_);
	add(subtitle_);
	add(title_prev_);
	add(subtitle_prev_);

	renderGraphic();

	isInit_ = false;
}

void Title::renderGraphic()
{
	title_.setAlpha(ms_->title_alpha);
	subtitle_.setAlpha(ms_->subtitle_alpha);

	title_.setPosition(0, 0, 480, 37); // 800x480
	subtitle_.setPosition(0, 37, 480, 37); // 800x480
	//title_.setPosition(0, 0, 768, 60);
	//subtitle_.setPosition(0, 60, 768, 60);


	if ((!isInit_ && ScreenNumber::SCREEN_HOME == ms_->ux_screen_id_current))
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S20_HEADER));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S20_TITLE));
	}
	else if (ScreenNumber::SCENARIO_2_30 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S0210_A_CHARGE_CARD));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S0210_A_CHARGE_CARD2));
	}
	else if (ScreenNumber::SCENARIO_2_31 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S0210_B_CREDIT_CARD));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S0210_B_CREDIT_CARD2));
	}
	else if (ScreenNumber::SCENARIO_2_32 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S0210_C_QR_CODE));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S0210_C_QR_CODE2));
	}
	else if (ScreenNumber::SCENARIO_2_33 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setY(30);
		title_.setTypedText(TypedText(T_S0212_TITLE));
		subtitle_.setVisible(false);
	}
	else if (ScreenNumber::SCENARIO_2_34 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setY(30);
		title_.setTypedText(TypedText(T_S0213_TITLE));
		subtitle_.setVisible(false);
	}
	else if (ScreenNumber::SCREEN_PAY_RFID == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S40_HEADER));
		subtitle_.setTypedText(TypedText(T_S40_TITLE));
	}
	else if (
		(isInit_ && ScreenNumber::SCENARIO_4_1 == ms_->ux_screen_id_next) ||
		(!isInit_ && UXCommandStatus::UX_COMMAND_OFF == ms_->ux_output_command_trigger && ScreenNumber::SCENARIO_4_1 == ms_->ux_screen_id_current))
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S0401_IDENTIFYING_CARD));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S0401_IDENTIFYING_CARD2));
	}
	else if (
		(isInit_ && ScreenNumber::SCENARIO_4_2 == ms_->ux_screen_id_next) ||
		(!isInit_ && ScreenNumber::SCENARIO_4_2 == ms_->ux_screen_id_current))
	{
		title_.setVisible(true);
		title_.setY(30);
		title_.setTypedText(TypedText(T_S0402_CARD_APPROVED));
		subtitle_.setVisible(false);
	}
	else if (ScreenNumber::SCENARIO_4_3 == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setY(30);
		title_.setTypedText(TypedText(T_S0403_SELECT_PLUG));
		subtitle_.setVisible(false);
	}
	else if (ScreenNumber::SCREEN_CONNECT == ms_->ux_screen_id_current)
	{
		title_.setVisible(true);
		title_.setTypedText(TypedText(T_S50_HEADER));
		subtitle_.setVisible(true);
		subtitle_.setTypedText(TypedText(T_S50_TITLE));
	}

	if (WeatherStyle::NIGHT == ms_->ux_weather)
	{
		title_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
		subtitle_.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
	}
	else
	{
		title_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
		subtitle_.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
	}

	title_.setLinespacing(0);
	title_.setFadeAnimationEndedAction(textarea_fade_animation_ended_callback_);
	title_.invalidate();

	subtitle_.setLinespacing(0);
	subtitle_.setFadeAnimationEndedAction(textarea_fade_animation_ended_callback_);
	subtitle_.invalidate();
}

void Title::setInAnimationDuration(int duration)
{
	animation_duration_in_ = duration;
}

void Title::setOutAnimationDuration(int duration)
{
	animation_duration_out_ = duration;
}

void Title::setSubAnimationDuration(uint16_t duration)
{
	animation_duration_sub_ = duration;
}

void Title::setTitleXY(int x, int y)
{
	title_.setXY(x, y);
}

void Title::setSubTitleXY(int x, int y)
{
	subtitle_.setXY(x, y);
}

void Title::setTransitionInAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_in_animation_ended_callback_ = &callback;
}

void Title::setTransitionOutAnimationEndedCallback(GenericCallback<const int>& callback)
{
	transition_out_animation_ended_callback_ = &callback;
}

void Title::beginTransitionInAnimation()
{
	title_.startFadeAnimation(255, animation_duration_in_);
	subtitle_.startFadeAnimation(255, animation_duration_in_);
}

void Title::beginTransitionOutAnimation()
{
	title_.startFadeAnimation(0, animation_duration_out_);
	subtitle_.startFadeAnimation(0, animation_duration_out_);
}

void Title::beginTransitionNextInAnimation(ScreenNumber next)
{
	configElement(next);
	title_.startFadeAnimation(255, animation_duration_in_);
	subtitle_.startFadeAnimation(255, animation_duration_in_);
}

void Title::beginTransitionNextOutAnimation(ScreenNumber next)
{
	configElement(next);
	title_.startFadeAnimation(0, animation_duration_out_);
	subtitle_.startFadeAnimation(0, animation_duration_out_);
}

void Title::beginSubScreenTransitionAnimation(ScreenNumber next)
{
	title_.setPosition(0, 0, 480, 37);
	subtitle_.setPosition(0, 37, 480, 37);
	title_prev_.setPosition(0, 0, 480, 37);
	subtitle_prev_.setPosition(0, 37, 480, 37);
	//title_.setPosition(0, 0, 768, 60);
	//subtitle_.setPosition(0, 60, 768, 60);
	//title_prev_.setPosition(0, 0, 768, 60);
	//subtitle_prev_.setPosition(0, 60, 768, 60);

	title_prev_.setTypedText(title_.getTypedText());
	subtitle_prev_.setTypedText(subtitle_.getTypedText());

	configElement(next);
	//isTwoLine_prev_ = isTwoLine_;

	//switch (next)
	//{
	//case ScreenNumber::SCREEN_HOME:		
	//	isTwoLine_ = true;
	//	title_.setTypedText(TypedText(T_S20_HEADER));
	//	subtitle_.setTypedText(TypedText(T_S20_TITLE));
	//	break;
	//case ScreenNumber::SCENARIO_4_2:
	//	isTwoLine_ = false;
	//	title_.setTypedText(TypedText(T_S0402_CARD_APPROVED));		
	//	break;
	//case ScreenNumber::SCENARIO_4_3:
	//	isTwoLine_ = true;
	//	title_.setTypedText(TypedText(T_S0403_SELECT_PLUG));
	//	subtitle_.setTypedText(TypedText(T_S0403_SELECT_PLUG2));
	//	break;
	//case ScreenNumber::SCENARIO_5_2:
	//	isTwoLine_ = true;
	//	title_.setTypedText(TypedText(T_S0502_ESTABLISHING_CONNECTION));
	//	subtitle_.setTypedText(TypedText(T_S0502_ESTABLISHING_CONNECTION2));
	//	break;
	//case ScreenNumber::SCENARIO_5_3:
	//	isTwoLine_ = true;
	//	title_.setTypedText(TypedText(T_S0503_CONNECTION_ESTABLISHED));
	//	subtitle_.setTypedText(TypedText(T_S0503_CONNECTION_ESTABLISHED2));
	//	break;
	//default:
	//	break;
	//}	
	
	title_.setAlpha(0);
	title_.setLinespacing(0);
	subtitle_.setAlpha(0);
	subtitle_.setLinespacing(0);
	title_prev_.setAlpha(255);
	title_prev_.setLinespacing(0);
	subtitle_prev_.setAlpha(255);
	subtitle_prev_.setLinespacing(0);


	//if (!isTwoLine_)
	//{
	//	title_.setY(30);
	//	subtitle_.setVisible(false);
	//}
	//else
	//{
	//	title_.setY(0);
	//	subtitle_.setY(60);
	//	subtitle_.setVisible(true);
	//}
	//if (!isTwoLine_prev_)
	//{
	//	title_prev_.setY(30);
	//	subtitle_prev_.setVisible(false);
	//}
	//else
	//{
	//	title_prev_.setY(0);
	//	subtitle_prev_.setY(60);
	//	subtitle_prev_.setVisible(true);
	//}

	title_.invalidate();
	subtitle_.invalidate();
	title_prev_.invalidate();
	subtitle_prev_.invalidate();

	title_.startFadeAnimation(255, animation_duration_sub_);
	subtitle_.startFadeAnimation(255, animation_duration_sub_);
	title_prev_.startFadeAnimation(0, animation_duration_sub_);
	subtitle_prev_.startFadeAnimation(0, animation_duration_sub_);
}

void Title::beginTransitionInAnimationFast()
{	
	title_.startFadeAnimation(255, animation_duration_in_ / 2);
	subtitle_.startFadeAnimation(255, animation_duration_in_ / 2);
}

void Title::beginTransitionOutAnimationFast()
{	
	title_.startFadeAnimation(0, animation_duration_out_ / 2);
	subtitle_.startFadeAnimation(0, animation_duration_out_ / 2);
}

void Title::configElement(ScreenNumber id)
{
	isTwoLine_prev_ = isTwoLine_;

	switch (id)
	{
	case ScreenNumber::SCREEN_HOME:
		isTwoLine_ = true;
		title_.setTypedText(TypedText(T_S20_HEADER));
		subtitle_.setTypedText(TypedText(T_S20_TITLE));
		break;
	case ScreenNumber::SCENARIO_4_2:
		isTwoLine_ = false;
		title_.setTypedText(TypedText(T_S0402_CARD_APPROVED));
		break;
	case ScreenNumber::SCENARIO_4_3:
		isTwoLine_ = true;
		title_.setTypedText(TypedText(T_S0403_SELECT_PLUG));
		subtitle_.setTypedText(TypedText(T_S0403_SELECT_PLUG2));
		break;
	case ScreenNumber::SCENARIO_5_2:
		isTwoLine_ = true;
		title_.setTypedText(TypedText(T_S0502_ESTABLISHING_CONNECTION));
		subtitle_.setTypedText(TypedText(T_S0502_ESTABLISHING_CONNECTION2));
		break;
	case ScreenNumber::SCENARIO_5_3:
		isTwoLine_ = true;
		title_.setTypedText(TypedText(T_S0503_CONNECTION_ESTABLISHED));
		subtitle_.setTypedText(TypedText(T_S0503_CONNECTION_ESTABLISHED2));
		break;
	default:
		break;
	}

	if (!isTwoLine_)
	{
		title_.setY(18);
		//title_.setY(30);
		subtitle_.setVisible(false);
	}
	else
	{
		title_.setY(0);
		subtitle_.setY(37);
		//subtitle_.setY(60);
		subtitle_.setVisible(true);
	}
	if (!isTwoLine_prev_)
	{
		title_prev_.setY(18);
		//title_prev_.setY(30);
		subtitle_prev_.setVisible(false);
	}
	else
	{
		title_prev_.setY(0);
		subtitle_prev_.setY(37);
		//subtitle_prev_.setY(60);
		subtitle_prev_.setVisible(true);
	}
}

void Title::saveContainerStatus()
{
	ms_->title_alpha = title_.getAlpha();
	ms_->subtitle_alpha = subtitle_.getAlpha();
}

void Title::textareaFadeAnimationEndedHandler(const FadeAnimator<TextArea>& source)
{
	saveContainerStatus();
}