#include <gui/widgets/info/MessageRed.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

MessageRed::MessageRed()	
	:
	box_fade_ended_callback_(this, &MessageRed::boxFadeEndedHandler),
	box_move_ended_callback_(this, &MessageRed::boxMoveEndedHandler),
	image_fade_ended_callback_(this, &MessageRed::imageFadeEndedHandler),
	image_move_ended_callback_(this, &MessageRed::imageMoveEndedHandler),
	tiledimage_move_ended_callback_(this, &MessageRed::tiledimageMoveEndedHandler),
    tiledimage_fade_ended_callback_(this, &MessageRed::tiledimageFadeEndedHandler)
{
	em_.setEventTriggerCallback(event_trigger_callback_);
}

MessageRed::~MessageRed()
{
	AbstractMessage::~AbstractMessage();
}

void MessageRed::initialize(MachineStatus *status, ContentType content)
{	
	ms_ = status;

	decorate_.setBitmap(Bitmap(BITMAP_INFO_DECORATE_ERROR_ID));
	decorate_.setXY(0, 0);
	decorate_.setAlpha(0);
	add(decorate_);

	pprt_view_.setPosition(0, 20, 638, 838);

	background_.setColor(Color::getColorFromRGB(0xFF, 0x00, 0x00));
	background_.setPosition(0, -838, 638, 838);
	background_.setAlpha(0);
	pprt_view_.add(background_);

	background_decorate_.setBitmap(Bitmap(BITMAP_INFO_TILE_MASK_ID));
	background_decorate_.setPosition(0, -838, 638, 838);
	background_decorate_.setAlpha(0);
	pprt_view_.add(background_decorate_);

	add(pprt_view_);

	pprt_view_.invalidate();

	AbstractMessage::initialize(ms_, content);
}

void MessageRed::event2()
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

void MessageRed::event3()
{
	AbstractMessage::event3();
}

void MessageRed::event4()
{
	AbstractMessage::event4();

	animation_lock_ = 5;

	decorate_.setFadeAnimationEndedAction(image_fade_ended_callback_);
	decorate_.startFadeAnimation(0, animation_duration_);

	background_.setFadeAnimationEndedAction(box_fade_ended_callback_);
	background_.setMoveAnimationEndedAction(box_move_ended_callback_);
	background_.startFadeAnimation(0, animation_duration_);
	background_.startMoveAnimation(0, -838, animation_duration_);

	background_decorate_.setFadeAnimationEndedAction(tiledimage_fade_ended_callback_);
	background_decorate_.setMoveAnimationEndedAction(tiledimage_move_ended_callback_);
	background_decorate_.startFadeAnimation(0, animation_duration_);
	background_decorate_.startMoveAnimation(0, -838, animation_duration_);
}

void MessageRed::event5()
{
	AbstractMessage::event5();
}

void MessageRed::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void MessageRed::boxFadeEndedHandler(const FadeAnimator<Box>& box)
{
	animation_lock_--;
}

void MessageRed::imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image)
{
	animation_lock_--;
}

void MessageRed::boxMoveEndedHandler(const MoveAnimator<FadeAnimator<Box>>& box)
{
	animation_lock_--;
}

void MessageRed::tiledimageMoveEndedHandler(const MoveAnimator<FadeAnimator<TiledImage>>& tiledimage)
{
	animation_lock_--;
}

void MessageRed::tiledimageFadeEndedHandler(const FadeAnimator<TiledImage>& tiledimage)
{
	animation_lock_--;
}