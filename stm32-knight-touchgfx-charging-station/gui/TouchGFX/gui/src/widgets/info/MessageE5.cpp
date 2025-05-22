#include <gui/widgets/info/MessageE5.hpp>

#include <touchgfx/Color.hpp>
#include <Bitmapdatabase.hpp>

MessageE5::MessageE5()	
	:
	box_fade_ended_callback_(this, &MessageE5::boxFadeEndedHandler),
	box_move_ended_callback_(this, &MessageE5::boxMoveEndedHandler),
	image_fade_ended_callback_(this, &MessageE5::imageFadeEndedHandler),
	image_move_ended_callback_(this, &MessageE5::imageMoveEndedHandler),
	tiledimage_move_ended_callback_(this, &MessageE5::tiledimageMoveEndedHandler),
    tiledimage_fade_ended_callback_(this, &MessageE5::tiledimageFadeEndedHandler)
{
	em_.setEventTriggerCallback(event_trigger_callback_);
}

MessageE5::~MessageE5()
{
	AbstractMessage::~AbstractMessage();
}

void MessageE5::initialize(MachineStatus *status, ContentType content)
{	
	decorate_.setBitmap(Bitmap(BITMAP_INFO_DECORATE_ERROR_ID));
	decorate_.setXY(0, 0);
	decorate_.setAlpha(0);
	add(decorate_);

	pprt_view_.setPosition(0, 20, 638, 838);

	background_.setColor(Color::getColorFromRGB(0xFF, 0x00, 0x1A));
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

void MessageE5::event2()
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

void MessageE5::event3()
{
	AbstractMessage::event3();
}

void MessageE5::event4()
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

void MessageE5::event5()
{
	AbstractMessage::event5();
}

void MessageE5::imageFadeEndedHandler(const FadeAnimator<Image>& image)
{
	animation_lock_--;
}

void MessageE5::boxFadeEndedHandler(const FadeAnimator<Box>& box)
{
	animation_lock_--;
}

void MessageE5::imageMoveEndedHandler(const MoveAnimator<FadeAnimator<Image>>& image)
{
	animation_lock_--;
}

void MessageE5::boxMoveEndedHandler(const MoveAnimator<FadeAnimator<Box>>& box)
{
	animation_lock_--;
}

void MessageE5::tiledimageMoveEndedHandler(const MoveAnimator<FadeAnimator<TiledImage>>& tiledimage)
{
	animation_lock_--;
}

void MessageE5::tiledimageFadeEndedHandler(const FadeAnimator<TiledImage>& tiledimage)
{
	animation_lock_--;
}