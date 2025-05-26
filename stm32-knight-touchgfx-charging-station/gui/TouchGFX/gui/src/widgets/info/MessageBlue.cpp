#include <gui/widgets/info/MessageBlue.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

MessageBlue::MessageBlue()
	:
	box_fade_ended_callback_(this, &MessageBlue::boxFadeEndedHandler),
	box_move_ended_callback_(this, &MessageBlue::boxMoveEndedHandler),
	image_fade_ended_callback_(this, &MessageBlue::imageFadeEndedHandler),
	image_move_ended_callback_(this, &MessageBlue::imageMoveEndedHandler),
	tiledimage_move_ended_callback_(this, &MessageBlue::tiledimageMoveEndedHandler),
    tiledimage_fade_ended_callback_(this, &MessageBlue::tiledimageFadeEndedHandler)
{
	em_.setEventTriggerCallback(event_trigger_callback_);
}

MessageBlue::~MessageBlue()
{
	AbstractMessage::~AbstractMessage();
}

void MessageBlue::initialize(MachineStatus *status, ContentType content)
{
	ms_ = status;

	decorate_.setBitmap(Bitmap(BITMAP_INFO_DECORATE_NORMAL_ID));
	decorate_.setXY(0, 0);
	decorate_.setAlpha(0);
	add(decorate_);

	pprt_view_.setPosition(0, 13, 398, 523);
	//pprt_view_.setPosition(0, 20, 638, 838);

	//background_.setColor(Color::getColorFromRGB(0xFF, 0xCD, 0x00));
	background_.setColor(Color::getColorFromRGB(0x4C, 0xC7, 0xEE));
	background_.setPosition(0, -523, 398, 523);
	//background_.setPosition(0, -838, 638, 838);
	background_.setAlpha(0);
	pprt_view_.add(background_);

	background_decorate_.setBitmap(Bitmap(BITMAP_INFO_TILE_MASK_ID));
	background_decorate_.setPosition(0, -523, 398, 523);
	//background_decorate_.setPosition(0, -838, 638, 838);
	background_decorate_.setAlpha(0);
	//pprt_view_.add(background_decorate_);

	add(pprt_view_);

	pprt_view_.invalidate();

	AbstractMessage::initialize(ms_, content);
}

void MessageBlue::event2()
{
	AbstractMessage::event2();

	animation_lock_ = 5;

	decorate_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	decorate_.startFadeAnimation(255, animation_duration_);

	background_.setFadeAnimationEndedAction(box_fade_ended_callback_);
	background_.setMoveAnimationEndedAction(box_move_ended_callback_);
	background_.startFadeAnimation(255, animation_duration_);
	background_.startMoveAnimation(0, 0, animation_duration_);

	background_decorate_.setFadeAnimationEndedAction(tiledimage_fade_ended_callback_);
	background_decorate_.setMoveAnimationEndedAction(tiledimage_move_ended_callback_);
	background_decorate_.startFadeAnimation(255, animation_duration_);
	background_decorate_.startMoveAnimation(0, 0, animation_duration_);
}

void MessageBlue::event3()
{
	AbstractMessage::event3();
}

void MessageBlue::event4()
{
	AbstractMessage::event4();

	animation_lock_ = 5;

	decorate_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	decorate_.startFadeAnimation(0, animation_duration_);

	background_.setFadeAnimationEndedAction(box_fade_ended_callback_);
	background_.setMoveAnimationEndedAction(box_move_ended_callback_);
	background_.startFadeAnimation(0, animation_duration_);
	background_.startMoveAnimation(0, -523, animation_duration_);
	//background_.startMoveAnimation(0, -838, animation_duration_);

	background_decorate_.setFadeAnimationEndedAction(tiledimage_fade_ended_callback_);
	background_decorate_.setMoveAnimationEndedAction(tiledimage_move_ended_callback_);
	background_decorate_.startFadeAnimation(0, animation_duration_);
	background_decorate_.startMoveAnimation(0, -523, animation_duration_);
	//background_decorate_.startMoveAnimation(0, -838, animation_duration_);
}

void MessageBlue::event5()
{
	AbstractMessage::event5();
}

void MessageBlue::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void MessageBlue::boxFadeEndedHandler(const FadeAnimator<Box>& box)
{
	animation_lock_--;
}

void MessageBlue::imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image)
{
	animation_lock_--;
}

void MessageBlue::boxMoveEndedHandler(const MoveAnimator<FadeAnimator<Box>>& box)
{
	animation_lock_--;
}

void MessageBlue::tiledimageMoveEndedHandler(const MoveAnimator<FadeAnimator<TiledImage>>& tiledimage)
{
	animation_lock_--;
}

void MessageBlue::tiledimageFadeEndedHandler(const FadeAnimator<TiledImage>& tiledimage)
{
	animation_lock_--;
}
